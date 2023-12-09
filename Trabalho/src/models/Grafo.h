#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <set>
#include <map>
#include <list>
#include <vector>
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

    Grafo(bool APonderada, bool VPonderado, bool ehDirecionado) : AGrafo() {
        this->Input = nullptr;
        this->setOutput(nullptr);
        setPonderado(APonderada);
        setVerticePonderado(VPonderado);
        setDirecionado(ehDirecionado);
    }


    void printListaAdjacencia();

    set<No *> *fechoTransitivoDireto(int idNo);

    void fechoTransitivoIndireto(int idNo);

    void salvaFecho(set<No *> *fecho, const string &tipo);

    void dijkstra(int origem, int destino);

    void Floyd(int idNoOrigem, int idNoDestino); // Mapa de nós de um grafo

    set<No *> *getVerticeInduzido();

    void Prim(set<No *> *verticeInduzido);

//    void AGMPrim(int idNoOrigem);

    void Kruskal(set<No *> *verticeInduzido);

//    void DeepSearch(int idNo);

//    void ordenacaoTopologica();

//    void parametrosGrafo();

//    void articulacao();

    long localClusteringCoefficient(int idNo);

    list<No *> algoritimoGuloso(const Grafo &grafo);

private:
    void auxFtd(No *no, set<No *> *nosVisitados);

    void auxFti(No *no, set<No *> *nosVisitados, set<No *> *nosIncidentes);

    set<No *> *incidentes(No *no);

    void auxDijkstra(map<int, int> *dist, set<int> *vistos, set<No *> *FTD);

    static int minDistance(map<int, int> *dist, set<int> *vistos, set<No *> *FTD);

    void imprimeDijkstra(map<int, int> *dist, int idOrigem, int idDestino);

    void floydA0(map<int, map<int, int>> *dist);

    void finalizaFloyd(map<int, map<int, int>> *dist, int idOrigem, int idoDestino);

    void menuGvi(set<No *> *verticeInduzido, set<int> *nosPossiveis);

    void insereGvi(set<No *> *verticeInduzido, set<int> *nosPossiveis);

    void removeGvi(set<No *> *verticeInduzido, set<int> *nosPossiveis);

    static void imprimeNosPossiveis(set<int> *nosPossiveis) {
        cout << "Nos possiveis: ";
        for (auto &it: *nosPossiveis) {
            cout << it << " ";
        }
        cout << endl;

    }

    static void imprimeVerticeInduzido(set<No *> *verticeInduzido) {
        cout << "Vertice induzido: ";
        for (auto &it: *verticeInduzido) {
            cout << it->getID() << " ";
        }
        cout << endl;
    }

    vector<Aresta *> *OrdenaArestas(set<No *> *verticeInduzido);

    void salvaAGM(Grafo *AGM, int noRaiz, const string &algoritmo);

    void auxSalvaAGM(Grafo *AGMPrim, No *pNo, set<No *> *pSet);

    Grafo *auxKruskal(set<No *> *verticeInduzido, vector<Aresta *> *arestasOrdenadas,
                      map<int, set<No *> *> *conjuntosDisjuntos);

    static void buscaArestaKruskal(vector<Aresta *> *arestasOrdenadas, map<int, set<No *> *> *conjuntosDisjuntos,
                                   No *&Origem, No *&Destino, Aresta *&aresta);

    static map<int, set<No *> *> *inicializaConjuntos(set<No *> *verticeInduzido);

    static void atualizaConjuntos(map<int, set<No *> *> *conjuntosDisjuntos, No *Origem, No *Destino);

    list<No *> ordenaLista(Grafo &grafo);

    double calcularDistancia(const No *no1, const No *no2);

    pair<list<list<int>>, int> algoritimoGuloso();

    list<No *> proximos();

    list <No> proximos(No);

    list<No *> proximos(No *);

    list<list<int>> algoritimoGulosoRandomizado();

    pair<list<list<int>>, int> algoritimoGulosoRandomizado(double alpha);

    pair<list<list<int>>, int> algoritimoGulosoRandomizadoAdaptativo();
};


#endif //GRAFO_H
