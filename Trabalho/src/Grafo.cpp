#include "Grafo.h"

void Grafo::InserirNo(int idNo) {
    if (this->NOS.find(idNo) != this->NOS.end()) {
        cout << "Não foi possível criar o nó, pois ele já existe!" << endl;
        cout << "Deseja visualizar o nó? (s/n)" << endl;
        char opcao;
        cin >> opcao;
        if (opcao == 's') {
            auto *no = this->NOS[idNo];
            no->printarNo(this->isPonderado(), this->isDirecionado());
        }
    } else {
        this->CriaNo(idNo);
    }
}

void Grafo::CriaNo(int idNo) {
    if (this->NOS.find(idNo) != this->NOS.end()) return;
    try {
        auto *no = new No(idNo);
        this->NOS[idNo] = no;
    } catch (exception &e) {
        cout << "Erro ao criar no!" << endl;
        throw e;
    }
}

void Grafo::CriarAresta(int idNoOrigem, int idNoDestino) {
    if (this->NOS.find(idNoOrigem) == this->NOS.end() || this->NOS.find(idNoDestino) == this->NOS.end()) {
        throw invalid_argument("No nao existe!");
    } else {
        try {
            auto *NoOrigem = this->NOS[idNoOrigem];
            auto *NoDestino = this->NOS[idNoDestino];
            auto *aresta = new Aresta(this->NOS[idNoOrigem], this->NOS[idNoDestino], ++this->NumArestas);

            NoOrigem->setAresta(idNoDestino, aresta);
            NoOrigem->setGrauSaida(NoOrigem->getGrauSaida() + 1);
            NoDestino->setGrauEntrada(NoDestino->getGrauEntrada() + 1);

            if (!isDirecionado()) {
                NoDestino->setAresta(idNoOrigem, aresta);
                NoDestino->setGrauSaida(NoDestino->getGrauSaida() + 1);
                NoOrigem->setGrauEntrada(NoOrigem->getGrauEntrada() + 1);
            }
            this->ARESTAS[aresta->getID()] = aresta;
        } catch (exception &e) {
            cout << "Erro ao criar aresta!" << endl;
            throw e;
        }
    }
}

void Grafo::CriarAresta(int idNoOrigem, int idNoDestino, int peso) {
    if (this->NOS.find(idNoOrigem) == this->NOS.end() || this->NOS.find(idNoDestino) == this->NOS.end()) {
        throw invalid_argument("No nao existe!");
    } else {
        try {
            auto *NoOrigem = this->NOS[idNoOrigem];
            auto *NoDestino = this->NOS[idNoDestino];
            auto *aresta = new Aresta(this->NOS[idNoOrigem], this->NOS[idNoDestino], this->NumArestas + 1, peso);
            NoOrigem->setAresta(idNoDestino, aresta);
            NoOrigem->setGrauSaida(NoOrigem->getGrauSaida() + 1);
            NoDestino->setGrauEntrada(NoDestino->getGrauEntrada() + 1);
            this->NumArestas++;
            if (!isDirecionado()) {
                NoDestino->setAresta(idNoOrigem, aresta);
                NoDestino->setGrauSaida(NoDestino->getGrauSaida() + 1);
                NoOrigem->setGrauEntrada(NoOrigem->getGrauEntrada() + 1);
            }
            this->ARESTAS[aresta->getID()] = aresta;
        } catch (exception &e) {
            cout << "Erro ao criar aresta!" << endl;
            throw e;
        }
    }
}


void Grafo::PrintListaAdjacencia() {
    cout << "Lista de Adjacência: " << endl;
    for (auto &no: this->NOS) {
        cout << "| " << no.first << " | : ";
        for (auto &aresta: no.second->getArestas()) {
            if (this->isPonderado())
                cout << "|" << aresta.first << "|(" << aresta.second->getPeso() << "), ";
            else
                cout << "|" << aresta.first << "|, ";

            cout << endl;
        }
        cout << endl;
    }
}

void Grafo::fechoTransitivoDireto(int idNo) {
    if (!this->isDirecionado()) {
        cout << "Grafo não direcionado!" << endl;
        return;
    }
    if (this->NOS.find(idNo) == this->NOS.end()) {
        cout << "Nó não existe!" << endl;
        return;
    }
    auto *no = this->NOS[idNo];
    cout << "Fecho Transitivo Direto: " << endl;
    cout << "Nó: " << no->getID() << endl;
    auto *nosVisitados = new set<No *>();
    auxFTD(no, 0, nosVisitados);

}

void Grafo::auxFTD(No *no, int level, set<No *> *nosVisitados) {
    if (no == nullptr) return;
    if (nosVisitados->find(no) != nosVisitados->end()) return;
    nosVisitados->insert(no);

    for (auto &aresta: no->getArestas()) {
        auto arestaDestino = aresta.second;
        auto noDestino = arestaDestino->getNoDestino();
        for (int i = 0; i < level; i++) {
            cout << "---";
        }
        cout << ">" << noDestino->getID() << endl;
        nosVisitados->insert(noDestino);
        auxFTD(noDestino, level + 1, nosVisitados);
    }
}

void Grafo::fechoTransitivoIndireto(int idNo) {
    if (!this->isDirecionado()) {
        cout << "Grafo não direcionado!" << endl;
        return;
    }
    if (this->NOS.find(idNo) == this->NOS.end()) {
        cout << "Nó não existe!" << endl;
        return;
    }
    auto *no = this->NOS[idNo];
    cout << "Fecho Transitivo Indireto: " << endl;
    cout << "Nó: " << no->getID() << endl;
    auto *nosVisitados = new set<No *>();
    set<No *> *nosIncidentes = incidentes(no);
    auxFTI(no, 0, nosVisitados, nosIncidentes);

}

void Grafo::auxFTI(No *no, int level, set<No *> *nosVisitados, set<No *> *nosIncidentes) {
    if (no == nullptr) return;
    if (nosVisitados->find(no) != nosVisitados->end()) return;
    nosVisitados->insert(no);

    for (auto &noIncidente: *nosIncidentes) {
        for (int i = 0; i < level; i++) {
            cout << "---";
        }
        cout << ">" << noIncidente->getID() << endl;
        nosVisitados->insert(noIncidente);
        set<No *> *auxNosIncidentes = incidentes(noIncidente);
        auxFTI(noIncidente, level + 1, nosVisitados, auxNosIncidentes);
    }
}

set<No *> *Grafo::incidentes(No *no) {
    auto *nosIncidentes = new set<No *>();
    for(auto &arestas : this->ARESTAS){
        if(arestas.second->getNoDestino() == no){
            nosIncidentes->insert(arestas.second->getNoOrigem());
        }
    }
    return nosIncidentes;
}