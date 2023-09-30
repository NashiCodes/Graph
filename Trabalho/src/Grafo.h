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

    void inserirNo(int idNo);

    void criarAresta(int idNoOrigem, int idNoDestino);
    void criarAresta(int idNoOrigem, int idNoDestino, int peso);
    void inserirAresta(Aresta *aresta);

    void removeNo(int idNo);
    void removeAresta(int idNoOrigem, int idNoDestino);

    void criarListaAdjacencia();
    void criarMatrizAdjacencia();

    void printNos();
    void printArestas();
    void printListaAdjacencia();
    void printMatrizAdjacencia();

    void printGrauNo(int idNo);
    void printGrauGrafo();
    void printGrauEntradaNo(int idNo);
    void printGrauEntradaGrafo();
    void printGrauSaidaNo(int idNo);
    void printGrauSaidaGrafo();

    void printOrdem();
    void printNumArestas();
    void printEhPonderado();
    void printEhDirecionado();

    void printNo(int idNo);
    void printAresta(int idNoOrigem, int idNoDestino);
};


#endif //GRAFO_H
