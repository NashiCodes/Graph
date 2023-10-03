#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include "models/No.h"
#include "models/Aresta.h"
#include "models/AGrafo.h"

using namespace std;

class Grafo : public AGrafo {
public:
    Grafo() : AGrafo() {};

    explicit Grafo(int ordem) : AGrafo(ordem) {};

    Grafo(int ordem, bool ehPonderado, bool ehDirecionado) : AGrafo(ordem, ehPonderado, ehDirecionado) {};

    void criaNo(int idNo);

    void inserirNo(int idNo);

    void criarAresta(int idNoOrigem, int idNoDestino);

    void criarAresta(int idNoOrigem, int idNoDestino, int peso);

    void printArestas();

    void printListaAdjacencia();
};


#endif //GRAFO_H
