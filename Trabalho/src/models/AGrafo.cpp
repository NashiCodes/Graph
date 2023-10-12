#include "AGrafo.h"

void AGrafo::montaGrafo() {
    int ordem;
    try {
        *this->getInput() >> ordem;
        if (ordem == 0) {
            cout << "Ordem inválida!" << endl;
            return;
        }
//        this->setOrdem(ordem);
        this->setOrdem(50);

        this->lerInstancias(this->isPonderado(), this->isDirecionado(), this->isVerticePonderado());

    } catch (exception &e) {
        cout << "Erro ao ler o arquivo!" << endl;
        cout << e.what() << endl;
    }
}

void AGrafo::lerInstancias(bool ponderado, bool direcionado, bool verticePonderado) {
    int idNoOrigem, idNoDestino, pesoAresta = 0, pesoNo = 0;

    while ((int)this->ARESTAS->size() < this->getOrdem()) {
        *this->getInput() >> idNoOrigem;
        *this->getInput() >> idNoDestino;
        if (ponderado)
            *this->getInput() >> pesoAresta;
        if (verticePonderado)
            *this->getInput() >> pesoNo;

        this->CriaNo(idNoOrigem, pesoNo);
        this->CriaNo(idNoDestino, pesoNo);
        this->CriarAresta(idNoOrigem, idNoDestino, pesoAresta);

        if (this->getInput()->eof()) {
            break;
        }
    }
    cout << "Fim do arquivo!" << endl;
    cout << "Tamanho do grafo: " << this->NOS->size() << endl;
    cout << "Numero de arestas: " << this->ARESTAS->size() << endl;
}


int AGrafo::getOrdem() const {
    return Ordem;
}

void AGrafo::setOrdem(int ordem) {
    if (ordem < 0 || (this->Ordem != 0 && ordem != (int)this->NOS->size())) {
        cout << "Nova ordem inválida!" << endl;
        return;
    }
    Ordem = ordem;
}

int AGrafo::getNumArestas() const {
    return NumArestas;
}

void AGrafo::setNumArestas(int numArestas) {
    if (numArestas < 0 || (this->NumArestas != 0 && numArestas != (int)this->ARESTAS->size())) {
        cout << "Número de arestas inválido!" << endl;
        return;
    }
    NumArestas = numArestas;
}

bool AGrafo::isPonderado() const {
    return ArestaPonderada;
}

void AGrafo::setPonderado(bool ehPonderado) {
    ArestaPonderada = ehPonderado;
}

bool AGrafo::isDirecionado() const {
    return EhDirecionado;
}

void AGrafo::setDirecionado(bool ehDirecionado) {
    EhDirecionado = ehDirecionado;
}

ofstream *AGrafo::getOutput() const {
    return Output;
}

void AGrafo::setOutput(ofstream *output) {
    AGrafo::Output = output;
}

const map<int, No *> *AGrafo::getNos() const {
    return NOS;
}

const map<int, Aresta *> *AGrafo::getArestas() const {
    return ARESTAS;
}

bool AGrafo::existeNo(int idNo) {
    return this->NOS->find(idNo) != this->NOS->end();
}

void AGrafo::CriaNo(int idNo, int pesoNo) {
    if (this->existeNo(idNo)) return;

    auto *no = new No(idNo, pesoNo);
    this->NOS->insert(pair<int, No *>(idNo, no));
}

void AGrafo::CriarAresta(int idNoOrigem, int idNoDestino, int pesoAresta) {
    if (!this->existeNo(idNoOrigem) || !this->existeNo(idNoDestino)) {
        cout << "Nó de origem ou destino não encontrado!" << endl;
        return;
    }

    auto *noOrigem = this->NOS->at(idNoOrigem);
    auto *noDestino = this->NOS->at(idNoDestino);
    auto idAresta = this->idsLiberados->empty() ? this->getNumArestas() : *this->idsLiberados->begin();
    this->idsLiberados->erase(idAresta);
    auto aresta = new Aresta( noDestino, idAresta, pesoAresta);

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


void AGrafo::imprimeGraus(int idNo) {
    if (!this->existeNo(idNo)) {
        cout << "Nó não encontrado!" << endl;
        return;
    }

    auto *no = this->NOS->at(idNo);
    if (this->isDirecionado()) {
        cout << "Grau de entrada: " << no->getGrauEntrada() << endl;
        cout << "Grau de saída: " << no->getGrauSaida() << endl;
    } else {
        cout << "Grau: " << no->getGrauSaida() << endl;
    }

    if (this->getOutput()->is_open() && this->getOutput()->good()) {
        if (this->isDirecionado()) {
            *this->getOutput() << "Grau de entrada: " << no->getGrauEntrada() << endl;
            *this->getOutput() << "Grau de saída: " << no->getGrauSaida() << endl;
        } else {
            *this->getOutput() << "Grau: " << no->getGrauSaida() << endl;
        }
    }
}

void AGrafo::InserirNo(int idNo, int pesoNo) {
    if (this->existeNo(idNo)) {
        cout << "Nó já existe!" << endl;
        return;
    }
    this->CriaNo(idNo, pesoNo);
    this->setOrdem(this->getOrdem() + 1);
}

ifstream *AGrafo::getInput() const {
    return Input;
}

void AGrafo::setVerticePonderado(bool ehPonderado) {
    VerticePonderado = ehPonderado;
}

bool AGrafo::isVerticePonderado() const {
    return VerticePonderado;
}

void AGrafo::RemoverNo(int idNo) {
    if(!this->existeNo(idNo)) {
        cout << "Nó não existe!" << endl;
        return;
    }

    auto *no = this->NOS->at(idNo);

    for(auto &aresta: no->getArestas()) {
        this->NOS->at(aresta.first)->RemoveAresta(idNo, this->isDirecionado());
    }
    this->NOS->erase(idNo);
    delete no;
}

void AGrafo::RemoverAresta(int idNoOrigem, int idNoDestino) {
    if(!this->existeNo(idNoOrigem) || !this->existeNo(idNoDestino)) {
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


