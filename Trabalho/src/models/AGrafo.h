#ifndef GRAFOS_AGRAFOS_H
#define GRAFOS_AGRAFOS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include "No.h"
#include "Aresta.h"

using namespace std;

class AGrafo {

protected:
    int Ordem;
    int NumArestas;
    bool EhPonderado;
    bool EhDirecionado;
    unordered_map<int, No *> NOS;
    AGrafo() : Ordem(0), NumArestas(0), EhPonderado(false), EhDirecionado(false) {};

    explicit AGrafo(int ordem) : Ordem(ordem), NumArestas(0), EhPonderado(false), EhDirecionado(false) {};

    AGrafo(int ordem, bool ehPonderado, bool ehDirecionado) :
            Ordem(ordem),
            NumArestas(0),
            EhPonderado(ehPonderado), EhDirecionado(ehDirecionado) {};

    ~AGrafo() {
        for (auto &no : NOS) {
            delete no.second;
        }
    }

public:
    int getOrdem() const {
        return Ordem;
    }

    void setOrdem(int ordem) {
        if (ordem < 0 || ordem != NOS.size()) {
            throw invalid_argument("Nova ordem inválida!");
        } else {
            Ordem = ordem;
        }
    }

    int getNumArestas() const {
        return NumArestas;
    }

    void setNumArestas(int numArestas) {
        if (numArestas < 0) {
            throw invalid_argument("Número de arestas inválido!");
        } else {
            NumArestas = numArestas;
        }
    }

    bool isPonderado() const {
        return EhPonderado;
    }

    void setPonderado(bool ehPonderado) {
        EhPonderado = ehPonderado;
    }

    bool isDirecionado() const {
        return EhDirecionado;
    }

    void setDirecionado(bool ehDirecionado) {
        EhDirecionado = ehDirecionado;
    }

    const unordered_map<int, No *> &getNos() const {
        return NOS;
    }

    void setNos(const unordered_map<int, No *> &nos) {
        NOS = nos;
    }
};


#endif //GRAFOS_AGRAFOS_H
