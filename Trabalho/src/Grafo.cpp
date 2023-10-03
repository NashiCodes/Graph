//
// Created by Nashi on 29/09/2023.
//

#include "Grafo.h"

void Grafo::inserirNo(int idNo) {
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
        this->criaNo(idNo);
    }
}

void Grafo::criaNo(int idNo) {
    if (this->NOS.find(idNo) != this->NOS.end()) return;
    try {
        auto *no = new No(idNo);
        this->NOS[idNo] = no;
    } catch (exception &e) {
        cout << "Erro ao criar no!" << endl;
        throw e;
    }
}

void Grafo::criarAresta(int idNoOrigem, int idNoDestino) {
    if (this->NOS.find(idNoOrigem) == this->NOS.end() || this->NOS.find(idNoDestino) == this->NOS.end()) {
        throw invalid_argument("No nao existe!");
    } else {
        try {
            auto *aresta = new Aresta(this->NOS[idNoDestino]);
            this->NOS[idNoOrigem]->setAresta(idNoDestino, aresta);
            if (!isDirecionado()) {
                auto *aresta2 = new Aresta(this->NOS[idNoOrigem]);
                this->NOS[idNoDestino]->setAresta(idNoOrigem, aresta2);
            }
        } catch (exception &e) {
            cout << "Erro ao criar aresta!" << endl;
            throw e;
        }
    }
}

void Grafo::criarAresta(int idNoOrigem, int idNoDestino, int peso) {
    if (this->NOS.find(idNoOrigem) == this->NOS.end() || this->NOS.find(idNoDestino) == this->NOS.end()) {
        throw invalid_argument("No nao existe!");
    } else {
        try {
            auto *aresta = new Aresta(this->NOS[idNoDestino], peso);
            this->NOS[idNoOrigem]->setAresta(idNoDestino, aresta);
            if (!isDirecionado()) {
                auto *aresta2 = new Aresta(this->NOS[idNoOrigem], peso);
                this->NOS[idNoDestino]->setAresta(idNoOrigem, aresta2);
            }

        } catch (exception &e) {
            cout << "Erro ao criar aresta!" << endl;
            throw e;
        }
    }
}

void Grafo::printArestas() {
    cout << "Arestas: " << endl;
    for (auto &no: this->NOS) {
        for (auto &aresta: no.second->getArestas()) {
            if (isDirecionado())
                cout << no.first << " -> " << aresta.first << endl;
            else {
                No *noDestino = aresta.second->getNoDestino();
                if (!noDestino->isVisitado())
                    cout << no.first << " <-> " << aresta.first << endl;
            }
        }
    }
}

void Grafo::printListaAdjacencia() {
    cout << "Lista de Adjacência: " << endl;
    for (auto &no: this->NOS) {
        cout << "| " << no.first << " | : ";
        for (auto &aresta: no.second->getArestas()) {
            if (!isPonderado())
                cout << "-> |" << aresta.first << "| ";
            else
                cout << "|" << aresta.first << "|(" << aresta.second->getPeso() << ")| -> ";
        }
        cout << endl;
    }
}
