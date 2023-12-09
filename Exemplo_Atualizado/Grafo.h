#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "No.h"
#include "Aresta.h"

using namespace std;

class No;
class Aresta;

class Grafo {
public:

    //--- Construtor e Destrutor ---
    Grafo(): ordem(0), numAresta(0), digrafo(false), weigthNo(false), weightArc(false), noRaiz(nullptr) {};
    Grafo(bool isDigrafo): ordem(0), numAresta(0), digrafo(isDigrafo), weigthNo(false), weightArc(false), noRaiz(nullptr) {};
    virtual ~Grafo();

    //--- Seters ---
    void incOrdem();
    void decOrdem();

    //--- Funcoes do No ---
    bool procurarNoPeloId(int idFindNo);
    No *insereNo(int idNo, int pesoNo);
    bool removeNo(int idNo, bool isDigrafo);

    //--- Funcoes de Aresta ---
    bool insertAresta(int idNoOrigem, int idNoDestino, int pesoAresta, bool weigthArc, bool isDirected);
    bool removeAresta(int idNoOrigem, int idNoDestino, bool isDirected);


    //--- Caracteristica do Grafo ---
    int getNumAresta();
    No *getNoRaiz();
    int getOrdem();
    int getGrauEntrada();
    int getGrauSaida();



private:

    int ordem;
    int numAresta;
    bool digrafo;
    bool weigthNo;
    bool weightArc;

    No *noRaiz;

};


#endif // GRAPH_H
