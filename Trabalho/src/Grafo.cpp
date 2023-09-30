//
// Created by Nashi on 29/09/2023.
//

#include "Grafo.h"

void Grafo::inserirNo(int idNo) {
    if (this->NOS.find(idNo) != this->NOS.end()) {
        throw invalid_argument("No ja existe!");
    } else {
        try {
            auto *no = new No(idNo);
            this->NOS[idNo] = no;
        } catch (exception &e) {
            cout << "Erro ao criar no!" << endl;
            throw e;
        }
    }
}

void Grafo::criarAresta(int idNoOrigem, int idNoDestino) {
    if (this->NOS.find(idNoOrigem) == this->NOS.end() || this->NOS.find(idNoDestino) == this->NOS.end()) {
        throw invalid_argument("No nao existe!");
    } else {
        try {
            auto *aresta = new Aresta(this->NOS[idNoDestino]);
            this->NOS[idNoOrigem]->setAresta(idNoDestino, aresta);
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
        } catch (exception &e) {
            cout << "Erro ao criar aresta!" << endl;
            throw e;
        }
    }
}

void Grafo::printNos() {

}

void Grafo::printArestas() {
}

void Grafo::printListaAdjacencia() {
    for (auto &no : this->NOS) {
        cout<< "| " << no.first << " | -> ";
        for (auto &aresta : no.second->getArestas()) {
            if (!isPonderado())
            cout << "| " << aresta.first << " | -> ";
            else
                cout << "|" << aresta.first << "|(" << aresta.second->getPeso() << ")| -> ";
        }
        cout << endl;
    }
}
