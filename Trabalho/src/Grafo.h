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

    void CriaNo(int idNo);

    void InserirNo(int idNo);

    void CriarAresta(int idNoOrigem, int idNoDestino);

    void CriarAresta(int idNoOrigem, int idNoDestino, int peso);

    void PrintListaAdjacencia();

    void fechoTransitivoDireto(int idNo);

    void fechoTransitivoIndireto(int idNo);

    void Dijkstra(int idNoOrigem, int idNoDestino);

    void Floyd(int idNoOrigem, int idNoDestino);

    void AGMPrim(int idNoOrigem);

    void AGMKruskal();

    void DeepSearch(int idNo);

    void ordenacaoTopologica();

    void parametrosGrafo();

    void articulacao();

private:
    void auxFTD(No *no, int level, set<No *> *visitados);

    void auxFTI(No *no, int level, set<No *> *nosVisitados, set<No *> *nosIncidentes);

    set<No *> *incidentes(No *no);

};


#endif //GRAFO_H
