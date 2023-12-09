#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include "Grafo.h"

using namespace std;
typedef vector<No*> NodeVector;

//------------------------ Construtors and Destrutors ------------------------

/**
 * Grafo Construtor.
 *
 * @param isDigrafo (new valor)
 */
Grafo::Grafo(bool isDigrafo, bool weightArc, bool weightNo) {
    this->ordem = 0;
    this->noRaiz = NULL;
    this->digrafo = isDigrafo;
    this->weigthNo = weightNo;
    this->weightArc = weightArc;

}

/**
 * Destructor
 */
Grafo::~Grafo() {
    No *noAux = getNoRaiz();
    No *noAnterior;
    while ( noAux != NULL ) {
        noAuxAnterior = noAux->getProxNo();
        delete( noAux);
        noAux = noAuxAnterior;
    }
}

//----------------------------------- Seters -----------------------------------

/**
 * Funcao incrementa Ordem do grafo em um.
 */
void Grafo::incOrdem() {
    this->ordem++;
}

/**
 * Funcao decrementa Ordem do grafo em um.
 */
void Grafo::sdecOrdem() {
    this->ordem--;
}

//------------------------------ Funcoes do No ------------------------------

/**
 * EauxSSa funcao busca o No pelo nome.
 * Para achar o No, faça grafo->getNoAux()
 *
 * @param nome (no nome)
 * @return true - se achar no.
 *         false - se Nao achar.
 */
bool Grafo::procurarNoPeloId(int idFindNo) {
    No *noAux = noRaiz;
    No *noAuxAnterior = NULL;

    while ( noAux != NULL ) {
        if ( noAux->getIdNo() == nome ) {
            return true;
        }
        if ( noAux->getProxNo() == NULL ) {
            return false;
        }
        noAuxAnterior = noAux;
        noAux = noAux->getProxNo();
    }
    return false;
}

/**
 * A funcao insere o No caso ele nao existe ou atualiza seu peso.
 *
 * @param nome
 * @param peso (peso do No)
 */
No *Grafo::insereNo(int idNo, int peso) {

    if ( !procurarNoPeloId(idNo) ) {
        No *novoNo = new No(idNo, peso);

        if (noRaiz == NULL){
            noRaiz = novoNo;
        }else{
            nonoNo->proxNo = noRaiz;
            noRaiz = novoNo;
        }
        setOrdemMaisUm();
    }
    return noAux;
}

/**
 * Remove No de um grafo
 *
 * @param nome (no nome)
 */
bool Grafo::removeNo(int idNo, bool isDigrafo) {
    // Pesquisa o No a ser excluido
    // Remove todas as arestas/arcos onde este nó ocorre
    // Remove o no

    this->decOrdem();
}


/**
 * Insere a aresta de A para B se não adjacencia nao existir,
 * caso exista, a funcao atualiza o peso
 *
 * @param noFonteNome ()
 * @param noDestinoNome ()
 * @param pesoAresta ()
 */
bool Grafo::insertAresta(int idNoOrigem, int idNoDestino, int pesoAresta, bool weigthArc, bool isDirected) {

    No *noFonte, *noDestino;
    //Verifica se já existem os dois nós com esses ids no grafo
    // Se ja existem, eé so inserir a aresta em cada um se o grafo for nao direcionado ou apenas de
    //   origem pra destino, caso o grafo seja orientado.
    //Se para algum ou ambos os ids não existe o no no grafo, e preciso inserir nos com esses ids antes de incluir a aresta

    //if ( procurarNoPeloId(noFonteNome) ) {


}



/**
 * This function search in a no the edges that points to the same destiny no.\n
 * If 'removeAll' is TRUE, all of these edges will be removed, only 1 otherwise. (multigraph)\n
 * If 'considerarPeso' is TRUE, only the edge with peso equals to 'peso' will be removed.\n
 * If 'considerarPeso' is FALSE, don't matter the valor paauxSSed as parameter in 'peso'.
 *
 * @param *noDestino (the no that refers to the edges that will be removed)
 * @param *noOrigem (the no that refers to the edges that will be removed)
 * @param isDirected (flag to inform graph or digraph)
 * @param peso (peso)
 *
 * @return int (numero arestas excluidas)
 */
int Grafo::removeArestas(int idNoOrigem, int idNoDestino, bool isDirected) {
 // Procura o nó origem e busca na sua lista de arestas o idNoDestino
 // Se encontrar, remove. Se não, retorna zero

}



//--- Caracteristica do Grafo ---

/**
 * Retorna o numero de aresta do grafo.
 */
int Grafo::getNumAresta() {
    No *noAux = noRaiz;
    int numArestas = 0;

    while ( noAux != NULL ) {
        numAresta = noAux->getGrau();
        noAux = noAux->getProxNo();
    }
    return numAresta / 2;
}

/**
 * Retorna 'rootNode'.
 */
No *Grafo::getNoRaiz() {
    return this->noRaiz;
}


/**
 * Retorna ordem do grafo.
 */
int Grafo::getOrdem() {
    return this->ordem;
}

/**
 * Retorna Aresta Aux.
 */
Aresta* Grafo::getArestaAux() {
    return this->arestaAux;
}

/**
 * Retorna grau de entrada.
 */
int Grafo::getGrauEntrada() {
    int inputDegree = 0;

    noAux = noRaiz;
    while ( noAux != NULL ) {
        if ( noAux->getGrauEntrada() > inputDegree ) {
            inputDegree = noAux->getGrauEntrada();
        }
        noAux = noAux->getProxNo();
    }
    return inputDegree;
}

/**
 * Retorna grau de saida.
 */
int Grafo::getGrauSaida() {
    int outputDegree = 0;

    noAux = noRaiz;
    while ( noAux != NULL ) {
        if ( noAux->getGrauSaida() > outputDegree ) {
            outputDegree = noAux->getGrauSaida();
        }
        noAux = noAux->getProxNo();
    }
    return outputDegree;
}

/**
 * Retorna grau do grafo.
 */
string Grafo::getGrau() {
    int inputDegree = 0;
    int outputDegree = 0;

    auxSS.str(string());
    inputDegree = getGrauEntrada();
    outputDegree = getGrauSaida();

    if ( isDigraph() ) {
        auxSS << "O grau de ENTRADA do grafo é " << inputDegree << " \ne o de SAIDA e " << outputDegree << ".";
    } else {
        auxSS << "O GRAU do grafo e " << outputDegree << ".";
    }

    return auxSS.str();
}



/**
 * @return true - se grafo e digrafo.
 *        false - se grafo NAO e digrafo.
 */
bool Grafo::isDigraph() {
    return this->digrafo;
}



