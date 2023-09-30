#ifndef GRAFOS_AGRAFOS_H
#define GRAFOS_AGRAFOS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include "No.h"
#include "Aresta.h"

using namespace std;

class AGrafo {

protected:
    int Ordem;
    int NumArestas;
    bool EhPonderado;
    bool EhDirecionado;
    map<int, No *> NOS;
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
    [[nodiscard]] int getOrdem() const {
        return Ordem;
    }

    void setOrdem(int ordem) {
        if (ordem < 0 || (this->Ordem != 0 && ordem != this->NOS.size())) {
            throw invalid_argument("Nova ordem inválida!");
        } else {
            Ordem = ordem;
        }
    }

    [[nodiscard]] int getNumArestas() const {
        return NumArestas;
    }

    void setNumArestas(int numArestas) {
        if (numArestas < 0) {
            throw invalid_argument("Número de arestas inválido!");
        } else {
            NumArestas = numArestas;
        }
    }

    [[nodiscard]] bool isPonderado() const {
        return EhPonderado;
    }

    void setPonderado(bool ehPonderado) {
        EhPonderado = ehPonderado;
    }

    [[nodiscard]] bool isDirecionado() const {
        return EhDirecionado;
    }

    void setDirecionado(bool ehDirecionado) {
        EhDirecionado = ehDirecionado;
    }
};


#endif //GRAFOS_AGRAFOS_H
