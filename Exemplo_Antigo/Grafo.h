#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include "No.h"
#include "Aresta.h"

using namespace std;

class No;
class Aresta;
class VectorEdgeSearch;

typedef vector<No*> NodeVector;

class Grafo {
public:

    //--- Construtor e Destrutor ---
    Grafo(bool isDigrafo);
    virtual ~Grafo();

    //--- Seters ---
    void setOrdemMaisUm();
    void setOrdemMenosUm();

    //--- Funcoes do No ---
    bool procurarNoPeloNome(int nome);
    No *insereNo(int nome, int peso, bool update);
    bool removeNo(int nome);
    void removeNoComGrauZero();

    //--- Funcoes de Aresta ---
    bool inserirAresta(int noFonteNome, int noDestinoNome, int pesoAresta);
    bool inserirAresta(No *noFonte, No *noDestino, int pesoAresta);
    int removeArestas(No *no, No *noDestino, bool removeAll, bool considerWeight, int peso);
    void removerAsArestasDoNo(No *no);
    Aresta* getArestaAux();

    //--- Caracteristica do Grafo ---
    int getNumAresta();
    No *getNoRaiz();
    No *getNoAux();
    No *getNoAuxAnterior();
    int getOrdem();
    int getGrauEntrada();
    int getGrauSaida();
    string getGrau();
    int getCardinalidade();
    bool isTrivial();
    bool isNULL();
    bool isDigraph();
    bool isCompleto();
    bool isBipartido();
    bool isBipartidoUm(No *n, bool b);
    bool isBipartidoDois(No *n, bool b);
    bool isConexo();
    string isEuleriano();
    string isHamiltoniano();
    string kRegularidade();
    string kConectividade();
    string sequenciaGrau();
    string informacoesNos();
    string estruturaGrafoEmMemoria();
    bool isMultigrafo1();
    bool isMultigrafoLaco();

    //--- Busca em Profundidade ---
    void updateSearchInfo();
    string arvoreBuscaProfundidade(int noNome);
    void buscaPronfudidade(No *no, int nivel, int connetedComponent);

    //--- Busca em Largura ---
    string arvoreBuscaLargura(int noNome);
    void buscaLargura(No *no, int nivel, int connetedComponent);

    //--- Algoritmo de Menor Caminho ---
    string caminhoMaisCurtoDijkstra(int noA, int noB);
    string menorCaminhoFloyd();
    string menorCaminhoFloyd(int noA, int noB);
    string dadosObtidosFloyd();
    int** constroiFloyd(int tam, int** dist);
    int** listaAdjacencia(int tam, int** dist);

    //--- Arvore Geradora Minima ---
    string agmPRIM(int noNome);
    string agmKRUSKAL();
    VectorEdgeSearch* criaAGM(int noInicio);

    //--- Outros Algoritmos ---
    bool getNoDeArticulacao(int noNome);
    NodeVector getTodasNosArticulacao();
    bool isPonte(int noFonteNome, int noDestinoNome);
    NodeVector getTodasPontes();
    string isAdjacente(int nodeA, int nodeB);
    string fechoTransitivoDiretoDeUmNo(int noNome);
    void fechoTransitivoDireto(No *no, int connetedComponent);
    string fechoTransitivoIndiretoDeUmNo(int noNome);
    NodeVector getVizinhaca(int noNome, bool isClosed);
    Grafo *getGrafoComplementar();
    Grafo* getCopy();
    string subrgrafoInduzidoPelaVizinhacaFechada(int noNome);
    static Grafo *generateGraphInducedByANodeSet(NodeVector nodeVector, bool isDigraph);
    int getComponentesConexas();
    string DAGOrdenacaoTopologica();
    NodeVector nodeVectorDaSequenciaGrau();
    NodeVector mergeSortANodeVector(NodeVector vector);
    NodeVector mergeSortAllNodes();
    void mergeSort(int left, int right);
    void merge(int left, int middle, int right);


private:

    int ordem;
    int numAresta;
    bool digrafo;
    bool searchInfoUpdated;
    int componenteConexa;

    No *noRaiz;
    No *noAux;
    No *noAuxAnterior;
    NodeVector auxVector;

    Aresta *arestaAux;
    Aresta *arestaAuxAnterior;
    stringstream auxSS;
};


#endif // GRAPH_H
