#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <set>
#include <map>
#include "AGrafo.h"
#include "Agrafo.cpp"

using namespace std;

class Grafo : public AGrafo {
public:


    Grafo(bool APonderada, bool VPonderado ,bool ehDirecionado, ifstream *entrada, ofstream *Saida) : AGrafo() {
        setPonderado(APonderada);
        setVerticePonderado(VPonderado);
        setDirecionado(ehDirecionado);
        this->Input = entrada;
        this->setOutput(Saida);
        this->montaGrafo();
    };

    void PrintListaAdjacencia();

     void fechoTransitivoDireto(int idNo);

     void fechoTransitivoIndireto(int idNo);

    float dijkstra(int id1, int id2);

    void Floyd(int idNoOrigem, int idNoDestino); // Mapa de nós de um grafo

    void finalizaFloyd(map<int, map<int, int>> *dist, int idOrigem, int idoDestino);

    void floydA0(map<int, map<int, int>> *dist);

//    void AGMPrim(int idNoOrigem);

//    void AGMKruskal();

//    void DeepSearch(int idNo);

//    void ordenacaoTopologica();

//    void parametrosGrafo();

//    void articulacao();

    long localClusteringCoefficient(int idNo);

private:
    void auxFTD(No *no, set<No *> *visitados);

    void auxFTI(No *no, set<No *> *nosVisitados, set<No *> *nosIncidentes);

    set<No *> *incidentes(No *no);

};


#endif //GRAFO_H
