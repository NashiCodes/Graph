#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <set>
#include <map>
#include <list>
#include "AGrafo.h"
#include "Agrafo.cpp"

using namespace std;

class Grafo : public AGrafo {
public:


    Grafo(bool APonderada, bool VPonderado, bool ehDirecionado, ifstream *entrada, ofstream *Saida) : AGrafo() {
        setPonderado(APonderada);
        setVerticePonderado(VPonderado);
        setDirecionado(ehDirecionado);
        this->Input = entrada;
        this->setOutput(Saida);
        this->montaGrafo();
    }


    void PrintListaAdjacencia();

    set<No *> *fechoTransitivoDireto(int idNo);

    set<No *> *fechoTransitivoIndireto(int idNo);

    void dijkstra(int _Origem_, int _Destino_);

    void auxDijkstra(No *no, map<int, int> *dist, set<int> *vistos, set<No *> *FTD);

    int minDistance(map<int, int> *dist, set<int> *vistos, set<No *> *FTD) const;

    void imprimeDijkstra(map<int, int> *dist, int idOrigem, int idDestino);

    void Floyd(int idNoOrigem, int idNoDestino); // Mapa de nós de um grafo

    void finalizaFloyd(map<int, map<int, int>> *dist, int idOrigem, int idoDestino);

    void floydA0(map<int, map<int, int>> *dist);

    void Prim(int idNoOrigem);

    vector<pair<int, Aresta *>> organizaArestaPeso(No &nosVisitados);

//    void AGMPrim(int idNoOrigem);

    void AGMKruskal();

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
