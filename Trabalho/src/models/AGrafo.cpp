#include "AGrafo.h"

void AGrafo::montaGrafo()  {
    string linha;
    try {
        int i = 0;
        while (!this->getInput()->eof()) {
            if (i >= 10000) break;
            getline(*this->getInput(), linha);
            if (linha.empty()) {
                break;
            }

            auto id = linha.substr(0, linha.find(' '));
            linha.erase(0, linha.find(' ') + 1);
            auto idDestino = linha.substr(0, linha.find(' '));
            try {
                this->CriaNo(stoi(id));
                this->CriaNo(stoi(idDestino));
            } catch (exception &e) {
                cout << "Erro ao inserir nó!" << endl;
                cout << e.what() << endl;
            }

            if (this->isPonderado()) {
                linha.erase(0, linha.find(' ') + 1);
                this->CriarAresta(stoi(id), stoi(idDestino), stoi(linha));
            } else {
                this->CriarAresta(stoi(id), stoi(idDestino));
            }
            i++;
        }
    } catch (exception &e) {
        cout << "Erro ao ler o arquivo!" << endl;
        cout << e.what() << endl;
    }
}
int AGrafo::getOrdem() const {
    return Ordem;
}

void AGrafo::setOrdem(int ordem) {
    if (ordem < 0 || (this->Ordem != 0 && ordem != this->NOS->size())) {
        cout << "Nova ordem inválida!" << endl;
        return;
    }
    Ordem = ordem;
}

int AGrafo::getNumArestas() const {
    return NumArestas;
}

void AGrafo::setNumArestas(int numArestas) {
    if (numArestas < 0 || (this->NumArestas != 0 && numArestas != this->ARESTAS->size())) {
        cout << "Número de arestas inválido!" << endl;
        return;
    }
    NumArestas = numArestas;
}

bool AGrafo::isPonderado() const {
    return EhPonderado;
}

void AGrafo::setPonderado(bool ehPonderado) {
    EhPonderado = ehPonderado;
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

void AGrafo::CriaNo(int idNo) {
    if (this->existeNo(idNo)) return;

    auto *no = new No(idNo);
    this->NOS->insert(pair<int, No *>(idNo, no));
}

void AGrafo::CriarAresta(int idNoOrigem, int idNoDestino, int pesoAresta) {
    if (!this->existeNo(idNoOrigem) || !this->existeNo(idNoDestino)) {
        cout << "Nó de origem ou destino não encontrado!" << endl;
        return;
    }

    auto *noOrigem = this->NOS->at(idNoOrigem);
    auto *noDestino = this->NOS->at(idNoDestino);
    auto aresta = new Aresta(noOrigem, noDestino, this->getNumArestas(), pesoAresta);

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

void AGrafo::CriarAresta(int idNoOrigem, int idNoDestino) {
    if (!this->existeNo(idNoOrigem) || !this->existeNo(idNoDestino)) {
        cout << "Nó de origem ou destino não encontrado!" << endl;
        return;
    }

    auto *noOrigem = this->NOS->at(idNoOrigem);
    auto *noDestino = this->NOS->at(idNoDestino);
    auto aresta = new Aresta(noOrigem, noDestino, this->getNumArestas());

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

void AGrafo::InserirNo(int idNo) {
    if (this->existeNo(idNo)) {
        cout << "Nó já existe!" << endl;
        return;
    }
    this->CriaNo(idNo);
    this->setOrdem(this->getOrdem() + 1);
}

ifstream *AGrafo::getInput() const {
    return Input;
}




