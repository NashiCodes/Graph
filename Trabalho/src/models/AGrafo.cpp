#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "AGrafo.h"

void AGrafo::montaGrafo() {
    try {
        if (this->getInput() == nullptr) {
            cout << "Arquivo de entrada não encontrado!" << endl;
            return;
        }
        if (!this->getPart()) //essa nova Variavel permite saber se é a parte 1 ou 2 do trabalho, true = parte 1,
            // false = parte 2
            this->instanciasParte2(); //Leitura do arquivo e montagem do grafo completo
        else
            this->instanciasParte1();

    } catch (exception &e) {
        cout << "Erro ao ler o arquivo!" << endl;
        cout << e.what() << endl;
    }

}

void AGrafo::instanciasParte1() {

    int idNoOrigem, idNoDestino, pesoAresta = 0, pesoNo = 0, ordem;
    *this->getInput() >> ordem;
    if (ordem == 0) {
        cout << "Ordem inválida!" << endl;
        return;
    }
    this->setOrdem(ordem);
    while (!this->getInput()->eof()) {
        *this->getInput() >> idNoOrigem;
        *this->getInput() >> idNoDestino;
        if (this->isPonderado())
            *this->getInput() >> pesoAresta;
        if (this->isVerticePonderado())
            *this->getInput() >> pesoNo;

        this->criaNo(idNoOrigem, pesoNo);
        this->criaNo(idNoDestino, pesoNo);
        this->criarAresta(idNoOrigem, idNoDestino, pesoAresta);

        if (this->getInput()->eof()) {
            break;
        }
    }
    cout << "Fim do arquivo!" << endl;
    cout << "Tamanho do grafo: " << this->NOS->size() << endl;
    cout << "Numero de arestas: " << this->ARESTAS->size() << endl;
}

void AGrafo::instanciasParte2() {
    string linha;
    int nmDimensao, nmCapacidade;
    lePropriedades(nmDimensao, nmCapacidade);

    while (getline(*this->getInput(), linha) && !this->getInput()->eof()) {
        if (std::equal(linha.begin(), linha.end(), "NODE_COORD_SECTION ")) continue;
        if (std::equal(linha.begin(), linha.end(), "DEMAND_SECTION ")) {
            this->leDemandas();
            break;
        }
        int x, y, id;
        istringstream iss(linha);
        iss >> id >> x >> y;
        No *no = new No(id, 0);
        no->X = x;
        no->Y = y;
        this->inserirNo(no);

        montarArestas(no);
    }
    //Os couts abaixo são apenas para testes
    //Remover depois

    cout << "Ordem do Grafo: " << this->getOrdem() << endl;
    cout << "Capacidade dos Caminhões: " << this->getCaminhoes()->at(0)->capacidade << endl;
    cout << "Numero de arestas: " << this->getNumArestas() << endl;
    cout << "Numero de vertices: " << this->getNos()->size() << endl << endl;
    for (auto no: *this->getNos()) {
        cout << endl;
        cout << "No: " << no.second->getID() << " X: " << no.second->X << " Y: " << no.second->Y << endl;
        cout << "Demanda: " << no.second->getPeso() << endl;
        cout << "Grau de entrada: " << no.second->getGrauEntrada() << endl;
        cout << "Grau de saida: " << no.second->getGrauSaida() << endl;
    }
}


void AGrafo::setOrdem(int ordem) {
    if (ordem < 0 || (this->Ordem != 0 && ordem != (int) this->NOS->size())) {
        cout << "Nova ordem inválida!" << endl;
        return;
    }
    Ordem = ordem;
}


void AGrafo::setNumArestas(int numArestas) {
    if (numArestas < 0 || (this->NumArestas != 0 && numArestas != (int) this->ARESTAS->size())) {
        cout << "Número de arestas inválido!" << endl;
        return;
    }
    NumArestas = numArestas;
}

void AGrafo::criaNo(int idNo, int pesoNo) {
    if (this->existeNo(idNo)) return;

    auto *no = new No(idNo, pesoNo);
    this->NOS->insert(pair<int, No *>(idNo, no));
}

void AGrafo::criarAresta(int idNoOrigem, int idNoDestino, int pesoAresta) {
    if (!this->existeNo(idNoOrigem) || !this->existeNo(idNoDestino)) {
        cout << "Nó de origem ou destino não encontrado!" << endl;
        return;
    }

    auto *noOrigem = this->NOS->at(idNoOrigem);
    auto *noDestino = this->NOS->at(idNoDestino);
    auto idAresta = this->idsLiberados->empty() ? this->getNumArestas() : *this->idsLiberados->begin();
    this->idsLiberados->erase(idAresta);
    auto aresta = new Aresta(noOrigem, noDestino, idAresta, pesoAresta);

    noOrigem->setAresta(idNoDestino, aresta);
    noOrigem->setGrauSaida(noOrigem->getGrauSaida() + 1);
    noDestino->setGrauEntrada(noDestino->getGrauEntrada() + 1);

    if (!this->isDirecionado()) {
        noDestino->setAresta(idNoOrigem, aresta);
        noDestino->setGrauSaida(noDestino->getGrauSaida() + 1);
        noOrigem->setGrauEntrada(noOrigem->getGrauEntrada() + 1);
    }

    this->ARESTAS->insert(pair<int, Aresta *>(aresta->getID(), aresta));
    this->setNumArestas(this->getNumArestas() + 1);
}

void AGrafo::inserirNo(int idNo, int pesoNo) {
    if (this->existeNo(idNo)) {
        if (this->getPart())
            cout << "Nó já existe!" << endl;
        return;
    }
    this->criaNo(idNo, pesoNo);
    this->setOrdem(this->getOrdem() + 1);
}

void AGrafo::removerNo(int idNo) {
    if (!this->existeNo(idNo)) {
        cout << "Nó não existe!" << endl;
        return;
    }

    auto *no = this->NOS->at(idNo);

    for (auto &aresta: no->getArestas()) {
        this->NOS->at(aresta.first)->RemoveAresta(idNo, this->isDirecionado());
    }
    this->NOS->erase(idNo);
    delete no;
}

void AGrafo::removerAresta(int idNoOrigem, int idNoDestino) {
    if (!this->existeNo(idNoOrigem) || !this->existeNo(idNoDestino)) {
        cout << "Nó de origem ou destino não existe!" << endl;
        return;
    }

    auto *noOrigem = this->NOS->at(idNoOrigem);
    auto *noDestino = this->NOS->at(idNoDestino);
    auto *aresta = noOrigem->getAresta(idNoDestino);

    noOrigem->RemoveAresta(idNoDestino, this->isDirecionado());
    noDestino->RemoveAresta(idNoOrigem, this->isDirecionado());

    this->ARESTAS->erase(aresta->getID());
    this->idsLiberados->insert(aresta->getID());
    delete aresta;
}

void AGrafo::inserirNo(No *no) {
    if (no == nullptr) {
        cout << "Nó inválido!" << endl;
        return;
    }
    if (this->existeNo(no->getID())) {
        cout << "Nó já existe!" << endl;
        return;
    }
    this->NOS->insert(pair<int, No *>(no->getID(), no));
    this->setOrdem(this->getOrdem() + 1);
}

void AGrafo::lePropriedades(int &nmDimensao, int &nmCapacidade) const {
    string linha;
    string strtruck = "No of trucks: ";
    string dimensao = "DIMENSION : ";
    string capaciadede = "CAPACITY : ";
    int nmCaminhoes = 0;

    while (getline(*this->getInput(), linha) && !std::equal(linha.begin(), linha.end(), "NODE_COORD_SECTION ")) {
        string substr;
        if (linha.find(strtruck) != string::npos) {
            substr = linha.substr(linha.find(strtruck) + strtruck.size());
            substr = substr.substr(0, substr.find(','));
            nmCaminhoes = stoi(substr);
        }
        if (linha.find(dimensao) != string::npos) {
            substr = linha.substr(linha.find(dimensao) + dimensao.size());
            nmDimensao = stoi(substr);
        }
        if (linha.find(capaciadede) != string::npos) {
            substr = linha.substr(linha.find(capaciadede) + capaciadede.size());
            nmCapacidade = stoi(substr);
        }
    }

    while (nmCaminhoes > 0) {
        this->getCaminhoes()->push_back(new caminhao(nmCapacidade));
        nmCaminhoes--;
    }

}

void AGrafo::leDemandas() const {
    int id, demanda;
    string linha;
    while (getline(*this->getInput(), linha) && !this->getInput()->eof()) {
        if (std::equal(linha.begin(), linha.end(), "DEMAND_SECTION ")) continue;
        if (std::equal(linha.begin(), linha.end(), "DEPOT_SECTION ")) break;

        istringstream iss(linha);
        iss >> id >> demanda;
        No *no = this->getNos()->at(id);
        no->setPeso(demanda);
    }
}

void AGrafo::montarArestas(No *no) {
    for (const auto &par: *this->getNos()) {
        No *noDestino = par.second;
        if (no->getID() == noDestino->getID()) continue;

        int cateto1 = no->X > noDestino->X ? no->X - noDestino->X : noDestino->X - no->X;
        int cateto2 = no->Y > noDestino->Y ? no->Y - noDestino->Y : noDestino->Y - no->Y;
        int peso = (int) round(sqrt(pow(cateto1, 2) + pow(cateto2, 2)));

        this->criarAresta(no->getID(), noDestino->getID(), peso);
    }
}
