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


    Grafo(bool ehPonderado, bool ehDirecionado, ifstream *entrada, ofstream *Saida) : AGrafo() {
        setPonderado(ehPonderado);
        setDirecionado(ehDirecionado);
        this->Input = entrada;
        this->setOutput(Saida);

        string linha;
        try {
            getline(*entrada, linha);
            this->setOrdem(stoi(linha));
        } catch (exception &e) {
            cout << "Erro ao ler a ordem do grafo!" << endl;
            cout << e.what() << endl;
        }
        this->montaGrafo();
    };

    void PrintListaAdjacencia();

    [[maybe_unused]] set<int> *getFTD(int idNo);

    [[maybe_unused]] void fechoTransitivoDireto(int idNo);

    [[maybe_unused]] void fechoTransitivoIndireto(int idNo);

//    void Dijkstra(int idNoOrigem, int idNoDestino);
//
//    void Floyd(int idNoOrigem, int idNoDestino);
//
//    void AGMPrim(int idNoOrigem);
//
//    void AGMKruskal();
//
//    void DeepSearch(int idNo);
//
//    void ordenacaoTopologica();
//
//    void parametrosGrafo();
//
//    void articulacao();

private:
    void auxFTD(No *no, int level, set<No *> *visitados);

    void auxFTI(No *no, int level, set<No *> *nosVisitados, set<No *> *nosIncidentes);

    set<No *> *incidentes(No *no);

};


#endif //GRAFO_H
