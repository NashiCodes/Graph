#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <queue>
#include "Grafo.h"
#include "VectorEdgeSearch.h"

#define INFINITO 999999
using namespace std;
typedef vector<No*> NodeVector;
typedef EdgeSearchInfo EdgeInfo;

//------------------------ Construtors and Destrutors ------------------------

/**
 * Grafo Construtor.
 *
 * @param isDigrafo (new valor)
 */
Grafo::Grafo(bool isDigrafo) {
    this->ordem = 0;
    this->searchInfoUpdated = false;
    this->componenteConexa = -1;
    this->noRaiz = NULL;
    this->noAux = NULL;
    this->noAuxAnterior = NULL;
    this->arestaAuxAnterior = NULL;
    this->digrafo = isDigrafo;
}

/**
 * Destructor
 */
Grafo::~Grafo() {
    noAux = getNoRaiz();
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
void Grafo::setOrdemMaisUm() {
    this->ordem++;
}

/**
 * Funcao decrementa Ordem do grafo em um.
 */
void Grafo::setOrdemMenosUm() {
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
bool Grafo::procurarNoPeloNome(int nome) {
    noAux = noRaiz;
    noAuxAnterior = NULL;

    while ( noAux != NULL ) {
        if ( noAux->getNome() == nome ) {
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
 * @param update (em caso de reinsercao, atualiza o peso)
 */
No *Grafo::insereNo(int nome, int peso, bool update) {
    if ( !procurarNoPeloNome(nome) ) {
        // User o SearchInfo para fazer AGM
        searchInfoUpdated = false;

        No *no = new No(nome, peso);

        if ( noAux != NULL ) {
            noAux->setProxNo(no);
            noAux = no;
        } else {
            noRaiz = no;
            noAux = no;
        }
        setOrdemMaisUm();
    } else {
        if ( update ) {
            noAux->setPeso(peso);
        }
    }
    return noAux;
}

/**
 * Remove No de um grafo
 *
 * @param nome (no nome)
 */
bool Grafo::removeNo(int nome) {
    // Pesquisa o No a ser excluido
    if ( procurarNoPeloNome(nome) ) {
        // User o SearchInfo para fazer AGM
        searchInfoUpdated = false;

        No *toBeRemoved = noAux;

        // Configura o Auxiliar
        if ( noAux == noRaiz ) {
            noRaiz = noRaiz->getProxNo();
        } else {
            noAuxAnterior->setProxNo(noAux->getProxNo());
        }

        noAux = noRaiz;

        // Removing each edge with noDestino equal to no found in searchNodeByName(nome)
        while ( noAux != NULL ) {
            removeArestas(noAux, toBeRemoved, false, false, -1);
            noAux = noAux->getProxNo();
        }
        // Remove todas as arestas do toBeRemoved !!!
        removerAsArestasDoNo(toBeRemoved);

        setOrdemMenosUm();
        toBeRemoved->~No();
        return true;
    }
    return false;
}

/**
 * Remove todos o nos com grau igual a 0(zero)
 */
void Grafo::removeNoComGrauZero() {
    noAux = noRaiz;
    No *aux;
    while ( noAux != NULL ) {
        if ( noAux->getPeso() == 0 ) {
            aux = noAux;
            noAux = noAux->getProxNo();
            removeNo(aux->getNome());
        } else {
            noAux = noAux->getProxNo();
        }
    }
}

/**
 * Insere a aresta de A para B se não adjacencia nao existir,
 * caso exista, a funcao atualiza o peso
 *
 * @param noFonteNome ()
 * @param noDestinoNome ()
 * @param pesoAresta ()
 */
bool Grafo::inserirAresta(int noFonteNome, int noDestinoNome, int pesoAresta) {
    // User o SearchInfo para fazer AGM
    searchInfoUpdated = false;

    No *noFonte, *noDestino;
    if ( procurarNoPeloNome(noFonteNome) ) {
        noFonte = noAux;
    } else {
        noFonte = insereNo(noFonteNome, 0, true);
    }

    if ( procurarNoPeloNome(noDestinoNome) ) {
        noDestino = noAux;
    } else {
        noDestino = insereNo(noDestinoNome, 0, true);
    }

    return inserirAresta(noFonte, noDestino, pesoAresta);
}

/**
 * Insere a aresta de A para B se não adjacencia nao existir,
 * caso exista, a funcao atualiza o peso
 *
 * @param noFonte ()
 * @param noDestino ()
 * @param pesoAresta ()
 */
bool Grafo::inserirAresta(No *noFonte, No *noDestino, int pesoAresta) {

    // User o SearchInfo para fazer AGM
    searchInfoUpdated = false;

    bool wasUpdated = false;
    arestaAux = noFonte->getPrimeiraAresta();
    while ( arestaAux != NULL ) {
        if ( arestaAux->getNoDestino()->getNome() == noDestino->getNome() ) {
            arestaAux->setPeso(pesoAresta);
            wasUpdated = true;
            break;
        }
        arestaAux = arestaAux->getProxAresta();
    }

    if ( !isDigraph() ) {
        arestaAux = noDestino->getPrimeiraAresta();
        while ( arestaAux != NULL ) {
            if ( arestaAux->getNoDestino()->getNome() == noFonte->getNome() ) {
                arestaAux->setPeso(pesoAresta);
                wasUpdated = true;
                break;
            }
            arestaAux = arestaAux->getProxAresta();
        }
    }

    if ( wasUpdated ) {
        return false;
    }

    Aresta *newEdge1 = new Aresta(noDestino, NULL, pesoAresta);
    if ( noFonte->getPrimeiraAresta() == NULL ) {
        noFonte->setPrimeiraAresta(newEdge1);
    } else {
        noFonte->getUltimaAresta()->setProxAresta(newEdge1);
    }
    noFonte->setUltimaAresta(newEdge1);

    if ( isDigraph() ) {
        noFonte->setIncrementaGrauSaida();
        noDestino->setIncrementaGrauEntrada();
    } else {
        noFonte->setIncrementaGrau();
        noDestino->setIncrementaGrau();

        Aresta *newEdge2 = new Aresta(noFonte, NULL, pesoAresta);
        if ( noDestino->getPrimeiraAresta() == NULL ) {
            noDestino->setPrimeiraAresta(newEdge2);
        } else {
            noDestino->getUltimaAresta()->setProxAresta(newEdge2);
        }
        noDestino->setUltimaAresta(newEdge2);
    }

    return true;
}

/**
 * This function search in a no the edges that points to the same destiny no.\n
 * If 'removeAll' is TRUE, all of these edges will be removed, only 1 otherwise. (multigraph)\n
 * If 'considerarPeso' is TRUE, only the edge with peso equals to 'peso' will be removed.\n
 * If 'considerarPeso' is FALSE, don't matter the valor paauxSSed as parameter in 'peso'.
 *
 * @param *no
 * @param *noDestino (the no that refers to the edges that will be removed)
 * @param removeAll (flag to enable the removal of all edges that refers to the destiny no)
 * @param considerarPeso (true - verificar peso para fazer exclusao)
 * @param peso (peso)
 *
 * @return int (numero denos excluido)
 */
int Grafo::removeArestas(No *no, No *noDestino, bool removeAll, bool considerarPeso, int peso) {

    // User o SearchInfo para fazer AGM
    searchInfoUpdated = false;

    Aresta *aux = no->getPrimeiraAresta();
    Aresta *auxPrevious = NULL;
    int count = 0;

    while ( aux != NULL ) {
        if ( aux->getNoDestino() == noDestino
                && ((considerarPeso && aux->getNoDestino()->getPeso() == peso)
                || !considerarPeso) ) {

            // If you have covered the entire list of edges.
            if ( no->getUltimaAresta() == aux ) {
                no->setUltimaAresta(auxPrevious);
            }

            // In first iteration auxPrevious == NULL
            if ( auxPrevious == NULL ) {
                no->setPrimeiraAresta(aux->getProxAresta());
                aux->~Aresta();
                auxPrevious = no->getPrimeiraAresta();
                if ( no->getPrimeiraAresta() != NULL ) {
                    aux = no->getPrimeiraAresta()->getProxAresta();
                } else {
                    aux = NULL;
                }
            } else {
                auxPrevious->setProxAresta(aux->getProxAresta());
                aux->~Aresta();
                aux = auxPrevious->getProxAresta();
            }

            if ( isDigraph() ) {
                no->setDecrementaGrauSaida();
                noDestino->setDecrementaGrauEntrada();
            } else {
                no->setDecrementarGrau();
            }

            if ( !removeAll ) {
                return 1;
            }
            count++;
        } else {
            auxPrevious = aux;
            aux = aux->getProxAresta();
        }
    }

    if ( auxPrevious != NULL && auxPrevious->getNoDestino() == noDestino ) {
        auxPrevious->~Aresta();
        count++;
    }

    return count;
}

/**
 * Remove todas as aresta de um no
 *
 * @param *no
 */
void Grafo::removerAsArestasDoNo(No *no) {
    arestaAux = no->getPrimeiraAresta();
    while ( arestaAux != NULL ) {
        removeArestas(no, arestaAux->getNoDestino(), true, false, -1);
        arestaAux = arestaAux->getProxAresta();
    }
}



//--- Caracteristica do Grafo ---

/**
 * Retorna o numero de aresta do grafo.
 */
int Grafo::getNumAresta() {
    noAux = noRaiz;
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
 * Retorna 'auxNode'.
 */
No *Grafo::getNoAux() {
    return this->noAux;
}

/**
 * Retorna 'auxPreviousNode'.
 */
No *Grafo::getNoAuxAnterior() {
    return this->noAuxAnterior;
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
 * Retorna o numero de arestas do grafo.
 */
int Grafo::getCardinalidade() {
    int quantidade = 0;

    noAux = noRaiz;
    while ( noAux != NULL ) {
        quantidade += noAux->getPeso();
        noAux = noAux->getProxNo();
    }

    if ( !isDigraph() ) {
        return quantidade / 2;
    }
    return quantidade;
}

/**
 * @return true - se grafo é trivial.
 *        false - se grafo não e trivial.
 */
bool Grafo::isTrivial() {
    if ( noRaiz != NULL &&
            noRaiz->getProxNo() == NULL &&
            noRaiz->getPrimeiraAresta() == NULL ) {
        return true;
    }
    return false;
}

/**
 * @return true - se grafo e NULL.
 *         false - se grafo NAO e NULL.
 */
bool Grafo::isNULL() {
    if ( noRaiz == NULL ) {
        return true;
    }
    return false;
}

/**
 * @return true - se grafo e digrafo.
 *        false - se grafo NAO e digrafo.
 */
bool Grafo::isDigraph() {
    return this->digrafo;
}

/**
 * @return true - se grafo é multigrafo.
 *        false - se grafo NAO é multigrafo.
 */
bool Grafo::isMultigrafo1() {
    noAux = noRaiz;
    Aresta *arestaAux2;
    while ( noAux != NULL ) {
        arestaAux = noAux->getPrimeiraAresta();
        arestaAux2 = arestaAux->getProxAresta();
        while ( arestaAux != NULL ) {
            while ( arestaAux2 != NULL ) {
                if ( arestaAux->getNoDestino()->getNome() == arestaAux2->getProxAresta()->getNoDestino()->getNome() )
                    return true;
                else
                    arestaAux2 = arestaAux2->getProxAresta();
            }
            arestaAux = arestaAux->getProxAresta();
        }
        noAux = noAux->getProxNo();
    }
    return false;
}

/**
 * @return true - se grafo é multigrafo.
 *        false - se grafo NAO é multigrafo.
 */
bool Grafo::isMultigrafoLaco() {
    noAux = noRaiz;
    Aresta *arestaAux2;
    while ( noAux != NULL ) {
        arestaAux = noAux->getPrimeiraAresta();
        arestaAux2 = arestaAux->getProxAresta();
        while ( arestaAux != NULL ) {
            if ( arestaAux->getNoDestino()->getNome() == noAux->getNome() ) //verifica se existe laço
                return true;
            while ( arestaAux2 != NULL ) {
                if ( arestaAux->getNoDestino()->getNome() == arestaAux2->getProxAresta()->getNoDestino()->getNome() )
                    return true;
                else
                    arestaAux2 = arestaAux2->getProxAresta();
            }
            arestaAux = arestaAux->getProxAresta();
        }
        noAux = noAux->getProxNo();
    }
    return false;
}

/**
 * @return true - se grafo e completo.
 *        false - se grafo NAO e completo.
 */
bool Grafo::isCompleto() {
    if ( ordem == 0 ) {
        return false;
    }

    noAux = noRaiz;
    int maiorGrau = getOrdem() - 1;

    while ( noAux != NULL ) {
        if ( noAux->getGrau() != maiorGrau ) {
            return false;
        }
        noAux = noAux->getProxNo();
    }
    return true;
}

/**
 * @return true - se grafo é bipartido.
 *        false - se grafo NAO é bipartido.
 */
bool Grafo::isBipartido() {
    if ( !this->isConexo() ) {
        return false;
    }
    bool b = 1;
    noAux = noRaiz;
    return isBipartidoUm(noAux, b);
}

bool Grafo::isBipartidoUm(No *n, bool b) {
    n->setGroup(1);
    arestaAux = n->getPrimeiraAresta();
    while ( arestaAux != NULL ) {
        if ( arestaAux->getNoDestino()->getGroup() == 1 ) return false;
        if ( arestaAux->getNoDestino()->getGroup() == 0 ) b = (b && isBipartidoDois(n, b));
        arestaAux = arestaAux->getProxAresta();
    }
    return b;
}

bool Grafo::isBipartidoDois(No *n, bool b) {
    n->setGroup(2);
    arestaAux = n->getPrimeiraAresta();
    while ( arestaAux != NULL ) {
        if ( arestaAux->getNoDestino()->getGroup() == 2 ) return false;
        if ( arestaAux->getNoDestino()->getGroup() == 0 ) b = (b && isBipartidoUm(n, b));
        arestaAux = arestaAux->getProxAresta();
    }
    return b;
}

/**
 * @return true - se grafo e conexo.
 *         false - se grafo NAO e conexo.
 */
bool Grafo::isConexo() {

    if ( noRaiz == NULL ) {
        return true;
    }
    updateSearchInfo();

    noAux = noRaiz;
    while ( noAux != NULL ) {
        if ( noAux->getSearchInfo()->getConnectedComponent() != 1 ) {
            return false;
        }
        noAux = noAux->getProxNo();
    }
    return true;
}

/**
 * @return String - retorna se grafo é k-regular, e qual valor de k
 */
string Grafo::kRegularidade() {
    if ( noRaiz == NULL ) {
        return "O grafo tem 0 nos, entao nao e k-regular";
    }
    int kRegularity = noRaiz->getGrau();
    noAux = noRaiz->getProxNo();

    while ( noAux != NULL ) {
        if ( noAux->getGrau() != kRegularity ) {
            return "O grafo não é k-regular";
        }
        noAux = noAux->getProxNo();
    }

    auxSS.str(string());
    auxSS << "O grafo é " << kRegularity << "-regular.";
    return auxSS.str();
}

/**
 * @return string - falando se grafo e euleriano
 */
string Grafo::isEuleriano() {

    auxSS.str(string());

    bool twoOdds = false;
    noAux = noRaiz;
    while ( noAux != NULL ) {
        if ( noAux->getPeso() % 2 == 1 ) {
            if ( !twoOdds ) {
                twoOdds == true;
            } else {
                break;
            }

        }
        noAux = noAux->getProxNo();
    }


    if ( !twoOdds && isConexo() ) {
        auxSS << "O grafo e Euleriano.";
    } else {
        auxSS << "O grafo NAO e euleriano.";
    }
    return auxSS.str();
}

/**
 * @return string - falando se grafo e hamiltoniano
 */
string Grafo::isHamiltoniano() {
    // IMPLEMENTAR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    return "IMPLEMENTAR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
}

/**
 * @return string - retorna k-conectividade
 */
string Grafo::kConectividade() {

    arvoreBuscaProfundidade(1);

    auxSS.str(string());
    auxSS << "\n K-Connectivity";

    if ( componenteConexa > 1 ) {
        auxSS << "\n O grafo nao e conectado";
    } else {
        nodeVectorDaSequenciaGrau();
        mergeSortAllNodes();

        auxSS << " O grafo e " << auxVector[0]->getPeso() << "-conectado";
    }

    return auxSS.str();
}

/**
 * @return string - retorna sequencia grau
 */
string Grafo::sequenciaGrau() {

    list<int> inputDegreeList;
    list<int> outputDegreeList;
    list<int>::iterator it;

    noAux = noRaiz;
    while ( noAux != NULL ) {
        inputDegreeList.push_back(noAux->getGrauEntrada());
        outputDegreeList.push_back(noAux->getGrauSaida());
        noAux = noAux->getProxNo();
    }
    inputDegreeList.sort(greater<int>());
    outputDegreeList.sort(greater<int>());

    auxSS.str(string());
    if ( isDigraph() ) {
        auxSS << "ENTRADA ";
    }
    auxSS << "SEQUENCIA DE GRAU: \n<";
    for ( it = inputDegreeList.begin(); it != inputDegreeList.end(); ) {
        auxSS << *it;
        if ( ++it != inputDegreeList.end() ) {
            auxSS << ", ";
        }
    }
    auxSS << ">\n\n";

    if ( isDigraph() ) {
        auxSS << "SEQUENCIA GRAU DE SAIDA: \n<";
        for ( it = outputDegreeList.begin(); it != outputDegreeList.end(); ) {
            auxSS << *it;
            if ( ++it != outputDegreeList.end() ) {
                auxSS << ", ";
            }
        }
        auxSS << ">";
    }

    return auxSS.str();
}

/**
 * @return string - retorna informacoes do No.
 */
string Grafo::informacoesNos() {
    noAux = noRaiz;
    stringstream auxSS, auxSSInput, auxSSOutput, auxSSAll;

    if ( isDigraph() ) {
        auxSSInput << "Lista (nao ordenada) do grau de entrada: {";
        auxSSOutput << "Lista (nao ordenada) do grau de saida: {";
    } else {
        auxSS << "Lista (nao ordenada) de graus: {";
    }

    while ( noAux != NULL ) {
        if ( isDigraph() ) {
            auxSSAll << "[" << noAux->getNome() << "] (grau ENTRADA: " << noAux->getGrauEntrada() << ")" << " (grau ENTRADA: " << noAux->getGrauSaida() << ") " << "(peso: " << noAux->getPeso() << ")" << "\n";
            auxSSInput << noAux->getGrauEntrada();
            auxSSOutput << noAux->getGrauSaida();
            if ( noAux->getProxNo() != NULL ) {
                auxSSInput << ", ";
                auxSSOutput << ", ";
            }
        } else {
            auxSSAll << "[" << noAux->getNome() << "] (grau: " << noAux->getGrau() << ") " << "(peso: " << noAux->getPeso() << ")" << "\n";
            auxSS << noAux->getPeso();
            if ( noAux->getProxNo() != NULL ) {
                auxSS << ", ";
            }
        }

        noAux = noAux->getProxNo();
    }

    if ( isDigraph() ) {
        auxSSInput << "}\n";
        auxSSOutput << "}\n";
        auxSSAll << "\n" << auxSSInput.str();
        auxSSAll << "\n" << auxSSOutput.str();
    } else {
        auxSS << "}\n";
        auxSSAll << "\n" << auxSS.str();
    }

    return auxSSAll.str();
}

/**
 * @return string - retorna estrutura do grafo na memoria.
 */
string Grafo::estruturaGrafoEmMemoria() {
    noAux = noRaiz;
    auxSS.str(string());

    while ( noAux != NULL ) {
        auxSS << "\n[" << noAux->getNome() << "] -> ";

        arestaAux = noAux->getPrimeiraAresta();
        if ( arestaAux != NULL ) {
            auxSS << "(" << arestaAux->getNoDestino()->getNome() << ") -> ";
            arestaAux = arestaAux->getProxAresta();
            while ( arestaAux != NULL ) {
                auxSS << "(" << arestaAux->getNoDestino()->getNome() << ") -> ";
                arestaAux = arestaAux->getProxAresta();
            }
        }

        noAux = noAux->getProxNo();
    }

    return auxSS.str();
}

int Grafo::getComponentesConexas() {
    updateSearchInfo();
    return this->componenteConexa;
}


//------------------------ Busca em Profundidade -----------------------

/**
 * Chama busca em profundidade se um No ou Aresta foi inserido ou removido
 */
void Grafo::updateSearchInfo() {
    if ( !searchInfoUpdated ) {
        arvoreBuscaProfundidade(noRaiz->getNome());
    }
}

/**
 * Usa busca em profundidade
 *
 * @param noNome ()
 * @return string - arvore com resultado de cada biparticao
 */
string Grafo::arvoreBuscaProfundidade(int noNome) {

    if ( !procurarNoPeloNome(noNome) ) {
        return "";
    }

    searchInfoUpdated = true;
    No *no = noAux;

    // Resetando SearchInfo
    noAux = noRaiz;
    while ( noAux != NULL ) {
        noAux->setSearchInfo(new SearchInfo());
        noAux = noAux->getProxNo();
    }

    auxSS.str(string());

    // Comeca no nivel 0 e componenteConexa 1
    componenteConexa = 1;
    auxSS << "Busca em Profundidade";
    auxSS << "\n\nComponente Conexa " << componenteConexa;
    buscaPronfudidade(no, 0, componenteConexa);
    // Comeca no nivel 0 e componenteConexa 2

    noAux = noRaiz;
    while ( noAux != NULL ) {
        if ( !noAux->getSearchInfo()->isVisited() ) {
            auxSS << "\n\nComponente Conexa " << ++componenteConexa;
            buscaPronfudidade(noAux, 0, componenteConexa);
        }
        noAux = noAux->getProxNo();
    }

    return auxSS.str();
}

/**
 * Recursao da busca em profundidade
 */
void Grafo::buscaPronfudidade(No *no, int level, int componenteConexa) {
    no->getSearchInfo()->setVisited(true);
    no->getSearchInfo()->setLevel(level);
    no->getSearchInfo()->setConnectedComponent(componenteConexa);

    auxSS << "\nNO: " << no->getNome() << " \tNIVEL: " << no->getSearchInfo()->getLevel();
    if ( no->getSearchInfo()->getNodeFather() != NULL ) {
        auxSS << " \tNO_PAI: " << no->getSearchInfo()->getNodeFather()->getNome();
    }

    Aresta *edge = no->getPrimeiraAresta();
    while ( edge != NULL ) {
        if ( !edge->getNoDestino()->getSearchInfo()->isVisited() ) {
            edge->getNoDestino()->getSearchInfo()->setNodeFather(no);
            buscaPronfudidade(edge->getNoDestino(), level + 1, componenteConexa);
        }
        edge = edge->getProxAresta();
    }
}



//----------------------- Busca em Largura ----------------------

/**
 * Usa busca em largura
 *
 * @param noNome ()
 * @return string - arvore com resultado de cada biparticao
 */
string Grafo::arvoreBuscaLargura(int noNome) {
    if ( !procurarNoPeloNome(noNome) ) {
        return "";
    }

    searchInfoUpdated = true;
    No *no = noAux;

    // Resetando SearchInfo
    noAux = noRaiz;
    while ( noAux != NULL ) {
        noAux->setSearchInfo(new SearchInfo());
        noAux = noAux->getProxNo();
    }

    auxSS.str(string());

    // Componente Conexa 1
    componenteConexa = 1;
    auxSS << "Busca em Largura";
    auxSS << "\n\nComponente Conexa" << componenteConexa;
    buscaLargura(no, 0, componenteConexa);

    // Outras Componentes Conexas
    noAux = noRaiz;
    while ( noAux != NULL ) {
        if ( !noAux->getSearchInfo()->isVisited() ) {
            auxSS << "\n\nCComponente Conexa" << ++componenteConexa;
            buscaLargura(noAux, 0, componenteConexa);
        }
        noAux = noAux->getProxNo();
    }

    return auxSS.str();
}

/**
 * Recursao ad busca em largura
 *
 * @param no ()
 * @param level ()
 * @param connetedComponent ()
 */
void Grafo::buscaLargura(No *rootNode, int level, int connetedComponent) {
    searchInfoUpdated = true;
    queue<No*> nodeQueue;
    nodeQueue.push(rootNode);
    No *aux;
    auxSS << "\nNO FONTE: " << rootNode->getNome();

    // Root Node
    rootNode->getSearchInfo()->setVisited(true);
    rootNode->getSearchInfo()->setLevel(level);
    rootNode->getSearchInfo()->setConnectedComponent(connetedComponent);
    rootNode->getSearchInfo()->setNodeFather(NULL);

    while ( !nodeQueue.empty() ) {
        aux = nodeQueue.front();
        nodeQueue.pop();

        arestaAux = aux->getPrimeiraAresta();
        while ( arestaAux != NULL ) {
            if ( !arestaAux->getNoDestino()->getSearchInfo()->isVisited() ) {
                nodeQueue.push(arestaAux->getNoDestino());
                arestaAux->getNoDestino()->getSearchInfo()->setVisited(true);
                arestaAux->getNoDestino()->getSearchInfo()->setLevel(aux->getSearchInfo()->getLevel() + 1);
                arestaAux->getNoDestino()->getSearchInfo()->setConnectedComponent(connetedComponent);
                arestaAux->getNoDestino()->getSearchInfo()->setNodeFather(aux);

                auxSS << "\nNO: " << arestaAux->getNoDestino()->getNome();
                auxSS << " \tNIVEL: " << aux->getSearchInfo()->getLevel() + 1;
                auxSS << " \tNO_PAI: " << aux->getNome();
            }
            arestaAux = arestaAux->getProxAresta();
        }
    }



    //    auxSS << "\nNAME: " << no->getName() << " LEVEL: " << no->getSearchInfo()->getLevel();
    //    if (no->getSearchInfo()->getNodeFather() != NULL) {
    //        auxSS << " FATHER: " << no->getSearchInfo()->getNodeFather()->getName();
    //    }
    //
    //    Edge *edge = no->getPrimeiraAresta();
    //    while (edge != NULL) {
    //        if (!edge->getDestinyNode()->getSearchInfo()->isVisited()) {
    //            edge->getDestinyNode()->getSearchInfo()->setNodeFather(no);
    //            depthFirstSearch(edge->getDestinyNode(), level + 1, connetedComponent);
    //        }
    //        edge = edge->getNextEdge();
    //    }
}



//-------------------------- Menor caminho --------------------------

/**
 * Menor caminho entre dois no usando Dijkstra
 *
 * @param nodeA ()
 * @param nodeB ()
 *
 * @return string - menor caminho
 */
string Grafo::caminhoMaisCurtoDijkstra(int noA, int noB) {
    //set connected component
    arvoreBuscaLargura(noA);

    auxSS.str(string());
    auxSS << "Menor caminho Dijkstra\n\n";

    bool sourceFound = procurarNoPeloNome(noA);
    No *auxSourceNode = noAux;

    sourceFound = procurarNoPeloNome(noB);
    No *auxSourceNode2 = noAux;

    if ( auxSourceNode->getSearchInfo()->getConnectedComponent() != auxSourceNode2->getSearchInfo()->getConnectedComponent() ) {
        return "Os nos nao fazem parte da mesma componente conexa";
    }


    VectorEdgeSearch* vectorEdge = new VectorEdgeSearch(auxSourceNode, this);
    VectorEdgeSearch* solution = new VectorEdgeSearch();

    EdgeInfo* auxEdgeSearch = vectorEdge->getMinimal(noA);
    solution->insertEdgeSearch(auxEdgeSearch);
    solution->setPeso(auxEdgeSearch, noA);

    //find the solution
    while ( vectorEdge->getSize() > 0 ) {
        auxEdgeSearch = vectorEdge->getMinimalConnectedToSolution();
        solution->insertEdgeSearch(auxEdgeSearch);
        solution->setPeso(auxEdgeSearch);
        vectorEdge->relaxVector();
    }

    auxSS << "A caminho mais curto entre " << noA << " e " << noB
            << " custa " << auxSourceNode2->getSearchInfo()->getShortestPath()
            << endl;

    auxSS << solution->printVetorShortestPath();
    auxSS << solution->printVetor();

    return auxSS.str();
}

/**
 * Menor caminho para todos os nos usando Floyd
 *
 * @return string - menor caminho
 */
string Grafo::menorCaminhoFloyd() {
    int tam = getOrdem();
    noAux = noRaiz;
    int** dist; //matriz com distancias menores de um no ao outro
    dist = constroiFloyd(tam, dist);

    for ( int q = 0; q < tam; q++ ) {
        auxSS << "[ ";
        for ( int l = 0; l < tam; l++ ) {
            if ( dist[q][l] != INFINITO )
                auxSS << "    " << dist[q][l] << " | ";
            else {
                auxSS << dist[q][l] << " | ";
            }
            if ( l == tam - 1 )
                auxSS << "]\n";
        }
    }
    return auxSS.str();
}

/**
 * Menor caminho para todos os nos usando Floyd
 *
 * @return string - menor caminho
 */
string Grafo::menorCaminhoFloyd(int noA, int noB) {
    int tam = getOrdem();

    auxSS.str(string());
    auxSS << "Menor caminho Floyd\n\n";

    noAux = noRaiz;
    int** dist; //matriz com distancias menores de um no ao outro
    dist = constroiFloyd(tam, dist);

    auxSS << "A caminho mais curto entre " << noA << " e " << noB
            << " custa " << dist[noA - 1][noB - 1]
            << endl;


    for ( int q = 0; q < tam; q++ ) {
        auxSS << "[ ";
        for ( int l = 0; l < tam; l++ ) {
            if ( dist[q][l] != INFINITO )
                auxSS << "    " << dist[q][l] << " | ";
            else {
                auxSS << dist[q][l] << " | ";
            }
            if ( l == tam - 1 )
                auxSS << "]\n";
        }
    }
    return auxSS.str();
}

int** Grafo::listaAdjacencia(int tam, int** dist) {
    dist = new int* [tam];
    for ( int i = 0; i < tam; i++ ) {
        dist[i] = new int [tam];

        for ( int k = 0; k < tam; k++ ) {
            if ( i == k ) {
                dist[i][k] = 0;
            } else {
                dist[i][k] = INFINITO;
            }
        }

    }
    return dist;
}

/**
 * A funcao tem como objetivo utilizar a matriz e posteriormente fazer o uso do algoritmo de Floyd
 *
 * @param int tam - tamanho da matriz
 * @param int infinito - valor constante para infinito
 * @param int** dist - matriz
 *
 * @return string - menor caminho
 */
int** Grafo::constroiFloyd(int tam, int** dist) {
    dist = listaAdjacencia(tam, dist);
    auxSS << "\n";
    while ( noAux != NULL )//atribuo todos os valores de nÃ³s adj
    {
        arestaAux = noAux->getPrimeiraAresta();
        while ( arestaAux != NULL ) {
            int nameVizinho = (arestaAux->getNoDestino()->getNome()) - 1;
            int origem = (noAux->getNome()) - 1;
            dist[origem][nameVizinho] = arestaAux->getPeso();
            arestaAux = arestaAux->getProxAresta();
        }
        noAux = noAux->getProxNo();
    }

    for ( int k = 0; k < tam; k++ ) {
        for ( int i = 0; i < tam; i++ ) {
            if ( i != k ) {
                for ( int j = 0; j < tam; j++ ) {
                    if ( dist[i][k] != INFINITO && dist[k][j] != INFINITO ) {
                        if ( dist[i][j] > dist[i][k] + dist[k][j] || dist[i][j] == INFINITO )
                            dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    return dist;
}

string Grafo::dadosObtidosFloyd() {

    int tam = getOrdem();

    auxSS.str(string());
    auxSS << "Dados obtidos com o Algoritmo de Floyd \n";


    int** dist; //matriz com distancias menores de um no ao outro
    dist = constroiFloyd(tam, dist);

    int excentricidade[tam] = {0};
    int raio = 0;
    int diametro = 0;
    vector<int> periferia;

    for ( int i = 0; i < tam; i++ ) {
        for ( int j = 0; j < tam; j++ ) {

            int indice = dist[i][j];
            if ( indice > 0 && indice < INFINITO ) {

                if ( excentricidade[i] < indice )
                    excentricidade[i] = indice;

                if ( diametro < indice )
                    diametro = indice;

                if ( raio > indice )
                    raio = indice;

            }

        }
    }
    auxSS << "\nexcentricidade: " << excentricidade;
    auxSS << "\ndiametro: " << diametro;
    auxSS << "\nraio" << raio;
    auxSS << "\nFloyd:\n";
    for ( int i = 0; i < tam; i++ ) {
        auxSS << "\n";
        for ( int j = 0; j < tam; j++ ) {
            auxSS << " " << dist[i][j] << " ";
        }
    }


    return auxSS.str();
}

//------------------- Arvore Geradora Minima ------------------

/**
 *
 */
string Grafo::agmPRIM(int noNome) {

    //set connected component
    string auxString = arvoreBuscaLargura(noNome);

    auxSS.str(string());
    auxSS << "Arvore Geradora Minima usando PRIM\n\n";

    VectorEdgeSearch* solucao = criaAGM(noNome);

    auxSS << solucao->printVetor();

    return auxSS.str();
}

/**
 *
 */
string Grafo::agmKRUSKAL() {
    //set connected component
    string auxString = arvoreBuscaLargura(1);

    auxSS.str(string());
    auxSS << "Arvore Geradora Minima usando Kruskal\n\n";

    VectorEdgeSearch* solucao = criaAGM(0);

    auxSS << solucao->printVetor();

    return auxSS.str();
}

VectorEdgeSearch* Grafo::criaAGM(int noInicio) {

    if ( noInicio = 0 ) {
        bool sourceFound = procurarNoPeloNome(1);
    } else {
        bool sourceFound = procurarNoPeloNome(noInicio);
    }
    No *auxSourceNode = noAux;

    // Resetar SearchInfo
    noAux = noRaiz;
    while ( noAux != NULL ) {
        noAux->getSearchInfo()->setVisited(false);
        noAux = noAux->getProxNo();
    }

    VectorEdgeSearch* vectorEdge = new VectorEdgeSearch(auxSourceNode, this);
    VectorEdgeSearch* retorno = new VectorEdgeSearch();

    EdgeInfo* auxEdgeSearch;
    if ( noInicio == 0 ) {
        auxEdgeSearch = vectorEdge->getMinimal();
    } else {
        auxEdgeSearch = vectorEdge->getMinimal(noInicio);
    }

    auxEdgeSearch->setBoth(true);
    retorno->insertEdgeSearch(auxEdgeSearch);

    if ( noInicio == 0 ) {
        while ( vectorEdge->getSize() > 0 ) {
            auxEdgeSearch = vectorEdge->getMinimal();
            retorno->insertEdgeSearch(auxEdgeSearch);
            vectorEdge->relaxVector();
            retorno->relaxSolution();
        }
    } else {
        while ( vectorEdge->getSize() > 0 ) {
            auxEdgeSearch = vectorEdge->getMinimalConnectedToSolution();
            retorno->insertEdgeSearch(auxEdgeSearch);
            vectorEdge->relaxVector();
        }
    }

    return retorno;
}




//------------------------------ Outros Algoritmos ------------------------------

/**
 * Diz se um No e de articulacao
 *
 * @param noNome
 *
 * @return string
 */
bool Grafo::getNoDeArticulacao(int noNome) {
    Grafo *copia = getCopy();

    copia->removeNo(noNome);

    if ( getComponentesConexas() < copia->getComponentesConexas() ) {
        delete copia;
        return true;
    }

    delete copia;
    return false;
}

/**
 * Acha todos os nos de articulacao do Grafo
 *
 * @return NodeVector - Vetor com nos de articulacao
 */
NodeVector Grafo::getTodasNosArticulacao() {
    NodeVector vectorAux;
    vectorAux.resize(getOrdem(), NULL);
    No* insercao = noRaiz;

    while ( insercao != NULL ) {
        if ( getNoDeArticulacao(insercao->getNome()) ) {
            vectorAux.push_back(insercao);
        }
        insercao = insercao->getProxNo();
    }

    return vectorAux;
}

/**
 * Diz se uma Aresta e ponte
 *
 * @param noFonteNome ()
 * @param noDestinoNome ()
 *
 * @return string
 */
bool Grafo::isPonte(int noFonteNome, int noDestinoNome) {

    auxSS.str(string());
    Grafo *copia = getCopy();

    bool sourceFound = copia->procurarNoPeloNome(noFonteNome);
    No *auxSourceNode = copia->getNoAux();

    bool destinyFound = copia->procurarNoPeloNome(noDestinoNome);
    No *auxDestinyNode = copia->getNoAux();

    copia->removeArestas(auxSourceNode, auxDestinyNode, false, false, -1);
    if ( !copia->isDigraph() ) {
        copia->removeArestas(auxDestinyNode, auxSourceNode, false, false, -1);
    }
    string busca = arvoreBuscaLargura(auxSourceNode->getNome());

    if ( getComponentesConexas() < copia->getComponentesConexas() ) {
        delete copia;
        return true;
    }

    delete copia;
    return false;
}

/**
 * Retorna Todos as aresta Ponte em Array
 * O primeiro no esta na posicao 2n
 * O segundo esta na posicao 2n + 1
 *
 * @return NodeVector - Array de nos que contem pontes.
 */
NodeVector Grafo::getTodasPontes() {
    NodeVector vectorAux;
    vectorAux.resize(getNumAresta(), NULL);
    No* insercao = noRaiz;

    while ( insercao != NULL ) {

        Aresta* auxiliarAresta = insercao->getPrimeiraAresta();

        while ( auxiliarAresta != NULL ) {
            if ( isPonte(insercao->getNome(), auxiliarAresta->getNoDestino()->getNome()) ) {
                vectorAux.push_back(insercao);
                vectorAux.push_back(auxiliarAresta->getNoDestino());
            }

            auxiliarAresta = auxiliarAresta->getProxAresta();
        }


        insercao = insercao->getProxNo();
    }

    return vectorAux;
}

/**
 * If the the nodes A and B exists and A is different of B (in case of a non-multigraph)
 * this function will returns a confirmation (Os nos A and B are [not] adjacent)
 * or will indicates when a no focuses in another no (in case of digraph).
 * If at least 1 of these nodes don't exists, this function will return a error
 * meauxSSage.
 *
 * @param nodeNameA ()
 * @param nodeNameB ()
 */
string Grafo::isAdjacente(int nodeNameA, int nodeNameB) {
    bool nodeAFound, nodeBFound;
    No *auxNodeA, *auxNodeB;

    if ( nodeNameA == nodeNameB ) {
        return "Esse grafo nao e um multigrafo, portanto nao permite self-looping.";
    } else {
        if ( procurarNoPeloNome(nodeNameB) ) {
            auxNodeB = noAux;
            nodeBFound = true;
        } else {
            nodeBFound = false;
        }
    }

    if ( procurarNoPeloNome(nodeNameA) ) {
        auxNodeA = noAux;
        nodeAFound = true;
        if ( nodeNameA == nodeNameB ) {
            nodeBFound = true;
        }
    } else {
        nodeAFound = false;
        if ( nodeNameA == nodeNameB ) {
            nodeBFound = false;
        }
    }

    auxSS.str(string());
    if ( !nodeAFound && !nodeBFound ) {
        auxSS << "Os nos " << nodeNameA << " e " << nodeNameB << " nao existem.";
        return auxSS.str();
    } else if ( !nodeAFound ) {
        auxSS << "O no " << nodeNameA << " nao existe.";
        return auxSS.str();
    } else if ( !nodeBFound ) {
        auxSS << "O no " << nodeNameB << " nao existe.";
        return auxSS.str();
    }

    arestaAux = auxNodeA->getPrimeiraAresta();
    while ( arestaAux != NULL ) {
        if ( arestaAux->getNoDestino()->getNome() == nodeNameB ) {
            if ( isDigraph() ) {
                auxSS << "O no " << nodeNameA << " aponta para o No " << nodeNameB << ". \n";
                break;
            } else {
                auxSS << "Os nos " << nodeNameA << " e " << nodeNameB << " sao adjacentes.";
                return auxSS.str();
            }
        }
        arestaAux = arestaAux->getProxAresta();
    }

    arestaAux = auxNodeB->getPrimeiraAresta();
    while ( arestaAux != NULL ) {
        if ( arestaAux->getNoDestino()->getNome() == nodeNameA ) {
            auxSS << "O no " << nodeNameB << " aponta para o No " << nodeNameA << ".";
            break;
        }
        arestaAux = arestaAux->getProxAresta();
    }
    if ( auxSS.str() == "" ) {
        auxSS << "Os nos " << nodeNameA << " e o no " << nodeNameB << " nao sao adjacentes.";
    }

    return auxSS.str();
}

/**
 * ?????????????????????????????
 *
 * @param noNome ()
 * @param isClosed ()
 */
string Grafo::fechoTransitivoDiretoDeUmNo(int noNome) {

    if ( !procurarNoPeloNome(noNome) ) {
        return "";
    }

    searchInfoUpdated = true;
    No *no = noAux;

    // Resetar SearchInfo
    noAux = noRaiz;
    while ( noAux != NULL ) {
        noAux->setSearchInfo(new SearchInfo());
        noAux = noAux->getProxNo();
    }

    auxSS.str(string());

    componenteConexa = 1;
    auxSS << "Fecho Transitivo direto de um No";
    auxSS << "\n\nNo Raiz : " << noNome;
    fechoTransitivoDireto(no, componenteConexa);


    return auxSS.str();
}

void Grafo::fechoTransitivoDireto(No *no, int connetedComponent) {
    no->getSearchInfo()->setVisited(true);
    no->getSearchInfo()->setConnectedComponent(connetedComponent);

    auxSS << "\nNO: " << no->getNome();

    Aresta *edge = no->getPrimeiraAresta();
    while ( edge != NULL ) {
        if ( !edge->getNoDestino()->getSearchInfo()->isVisited() ) {
            fechoTransitivoDireto(edge->getNoDestino(), connetedComponent);
        }
        edge = edge->getProxAresta();
    }
}

/**
 * ?????????????????????????????
 *
 * @param noNome ()
 * @param isClosed ()
 */
string Grafo::fechoTransitivoIndiretoDeUmNo(int noNome) {

    int tam = getOrdem();
    int infinito = 999999;
    noAux = noRaiz;
    int dist[tam][tam]; //matriz com distancias menores de um no ao outro
    for ( int i = 0; i < tam; i++ ) {
        for ( int k = 0; k < tam; k++ ) {
            if ( i == k ) {
                dist[i][k] = 0;
            } else {
                dist[i][k] = infinito;
            }
        }

    }
    auxSS << "\n";
    while ( noAux != NULL )//atribuo todos os valores de nós adj
    {
        arestaAux = noAux->getPrimeiraAresta();
        while ( arestaAux != NULL ) {
            int nameVizinho = (arestaAux->getNoDestino()->getNome()) - 1;
            int origem = (noAux->getNome()) - 1;
            dist[origem][nameVizinho] = arestaAux->getPeso();
            arestaAux = arestaAux->getProxAresta();
        }
        noAux = noAux->getProxNo();
    }

    for ( int k = 0; k < tam; k++ ) {
        for ( int i = 0; i < tam; i++ ) {
            if ( i != k ) {
                for ( int j = 0; j < tam; j++ ) {
                    if ( dist[i][k] != infinito && dist[k][j] != infinito ) {
                        if ( dist[i][j] > dist[i][k] + dist[k][j] || dist[i][j] == infinito )
                            dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
    int no = noNome - 1;
    auxSS << "{";
    for ( int q = 0; q < tam; q++ ) {
        if ( dist[q][no] != infinito ) {
            auxSS << " " << q + 1 << " " << "-";
        }

    }
    auxSS << "}";
    return auxSS.str();
}

/**
 * @param noNome (nome of the reference no)
 * @param isClosed (true to close neighborhood and false to open neighborhood)
 *
 * @return NodeVector - vizinhaca aberta/fechada ed um No
 */
NodeVector Grafo::getVizinhaca(int noNome, bool isClosed) {
    NodeVector nodeVector;

    if ( procurarNoPeloNome(noNome) ) {
        int i;
        if ( isClosed ) {
            nodeVector.resize(noAux->getPeso() + 1);
            nodeVector[0] = noAux;
            i = 1;
        } else {
            nodeVector.resize(noAux->getPeso());
            i = 0;
        }

        arestaAux = noAux->getPrimeiraAresta();
        while ( arestaAux != NULL ) {
            nodeVector[i] = arestaAux->getNoDestino();
            arestaAux = arestaAux->getProxAresta();
            i++;
        }
    } else {
        noAux = NULL;
    }

    return nodeVector;
}

/**
 * @return graph - grafo complementar
 */
Grafo *Grafo::getGrafoComplementar() {
    Grafo *graph = new Grafo(digrafo);
    return graph;
}

/**
 * @return graph - copia do grafo
 */
Grafo* Grafo::getCopy() {
    cout << "\nFazendo Copia do grafo...";

    Grafo *graph = new Grafo(digrafo);

    noAux = noRaiz->getProxNo();

    while ( noAux != NULL ) {
        arestaAux = noAux->getPrimeiraAresta();
        while ( arestaAux != NULL ) {
            graph->inserirAresta(noAux->getNome(),
                    arestaAux->getNoDestino()->getNome(), arestaAux->getPeso());

            arestaAux = arestaAux->getProxAresta();
        }
        noAux = noAux->getProxNo();
    }

    return graph;
}

/**
 * @param noNome (no that will considered to the closed neighborhood)
 *
 * @return - subgrafo com fecho transitivo indireto do no
 */
string Grafo::subrgrafoInduzidoPelaVizinhacaFechada(int noNome) {
    auxSS.str(string());

    if ( procurarNoPeloNome(noNome) ) {
        int i, j;
        int nodeDegree = noAux->getPeso();
        if ( nodeDegree > 0 ) {
            nodeDegree++;
            i = 1;

            No * nodeList[nodeDegree];
            nodeList[0] = noAux;

            arestaAux = noAux->getPrimeiraAresta();
            while ( arestaAux != NULL ) {
                nodeList[i] = arestaAux->getNoDestino();
                arestaAux = arestaAux->getProxAresta();
                i++;
            }

            for ( i = 0; i < nodeDegree; i++ ) {
                auxSS << "[" << nodeList[i]->getNome() << "] -> ";

                arestaAux = nodeList[i]->getPrimeiraAresta();
                while ( arestaAux != NULL ) {
                    for ( j = 0; j < nodeDegree; j++ ) {

                        if ( arestaAux->getNoDestino() == nodeList[j] ) {
                            auxSS << "(" << nodeList[j]->getNome() << ") -> ";
                        }
                    }
                    arestaAux = arestaAux->getProxAresta();
                }

                auxSS << "\n";
            }
        } else {
            auxSS << "O no " << noNome << " NAO tem nos adjacentes.";
        }
    } else {
        auxSS << "O no " << noNome << " NAO existe.";
    }

    return auxSS.str();
}

/**
 * @param nodeVector ()
 * @param isDigraph ()
 *
 * @return Grafo - Grafo induzido pela lista de Nos
 */
Grafo *Grafo::generateGraphInducedByANodeSet(NodeVector nodeVector, bool isDigraph) {

    Grafo *graph = new Grafo(isDigraph);
    Aresta *auxEdge;
    No *insertedNode;

    for ( int i = 0; i < nodeVector.size(); i++ ) {
        insertedNode = graph->insereNo(nodeVector[i]->getNome(), nodeVector[i]->getPeso(), true);

        auxEdge = nodeVector[i]->getPrimeiraAresta();
        while ( auxEdge != NULL ) {
            for ( int j = 0; j < nodeVector.size(); j++ ) {
                if ( auxEdge->getNoDestino() == nodeVector[j] ) {
                    graph->inserirAresta(nodeVector[i]->getNome(), nodeVector[j]->getNome(), nodeVector[j]->getPeso());
                }
            }
            auxEdge = auxEdge->getProxAresta();
        }
    }

    return graph;
}

/**
 * ????????????????????????????????????
 */
string Grafo::DAGOrdenacaoTopologica() {
    auxSS.str(string());
    int tam = getOrdem();
    noAux = noRaiz;
    queue<No*> filaGrauZero;
    queue<No*> filaSolucao;
    while ( noAux != NULL ) {
        if ( noAux->getGrauEntrada() == 0 ) {
            filaGrauZero.push(noAux);
        }
        noAux = noAux->getProxNo();
    }

    while ( !filaGrauZero.empty() ) {
        noAuxAnterior = filaGrauZero.front();
        filaGrauZero.pop();
        filaSolucao.push(noAuxAnterior);
        arestaAux = noAuxAnterior->getPrimeiraAresta();
        while ( arestaAux != NULL ) {
            noAux = arestaAux->getNoDestino();
            noAux->setDecrementaGrauEntrada();
            //auxEdge->getDestinyNode()->setInputDegreeMinusOne();
            if ( noAux->getGrauEntrada() <= 0 ) {
                filaGrauZero.push(noAux);
            }
            arestaAux = arestaAux->getProxAresta();
        }
    }
    if ( filaSolucao.size() != tam ) {
        auxSS << "existe um ciclo";
    } else {
        while ( !filaSolucao.empty() ) {
            auxSS << filaSolucao.front()->getNome() << " - ";
            filaSolucao.pop();
        }
    }
    return auxSS.str();
}

/**
 *
 * @return NodeVector - Grau d todos os nos ordenados de forma decrescente
 */
NodeVector Grafo::nodeVectorDaSequenciaGrau() {
    NodeVector vector;
    vector.resize(getOrdem());

    int i = 0;
    noAux = noRaiz;
    while ( noAux != NULL ) {
        vector[i] = noAux;
        noAux = noAux->getProxNo();
        i++;
    }

    return vector;
}

/**
 * Ordena o Vetor NodeVector
 *
 * @return NodeVector - Vetor ordenado de nos
 */
NodeVector Grafo::mergeSortAllNodes() {
    auxVector.resize(getOrdem());
    auxVector = nodeVectorDaSequenciaGrau();
    mergeSort(0, getOrdem() - 1);

    for ( int i = 0, j = auxVector.size() - 1; i < j; i++, j-- ) {
        noAux = auxVector[i];
        auxVector[i] = auxVector[j];
        auxVector[j] = noAux;
    }

    return auxVector;
}

/**
 * Ordena o Vetor NodeVector
 *
 * @return NodeVector - Vetor ordenado de nos
 */
NodeVector Grafo::mergeSortANodeVector(NodeVector vector) {
    auxVector.resize(vector.size());
    auxVector = vector;
    mergeSort(0, getOrdem() - 1);

    for ( int i = 0, j = auxVector.size() - 1; i < j; i++, j-- ) {
        noAux = auxVector[i];
        auxVector[i] = auxVector[j];
        auxVector[j] = noAux;
    }

    return auxVector;
}

/**
 * 'left' is for left index and 'right' is right index of the sub-array of vector
 * to be sorted.
 *
 * @param left - index
 * @param right - index
 */
void Grafo::mergeSort(int left, int right) {

    if ( right > left ) {

        // 1 - Find the middle point to divide the array into two halves.
        int middle = (int) (left + right) / 2;
        // 2 - Call mergeSort for first half.
        mergeSort(left, middle);

        // 3 - Call mergeSort for second half
        mergeSort(middle + 1, right);

        // 4 - Merge the two halves sorted in step 2 and 3
        merge(left, middle, right);
    }
}

/**
 * Merge ou junta dois subarrays (left+right)
 * Primeiro subarray e auxVector[left..middle].
 * Segundo subarray e auxVector[middle+1..right].
 *
 * @param
 * @return
 */
void Grafo::merge(int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    /* cria array temporario */
    NodeVector vectorLeft, vectorRight;
    vectorLeft.resize(n1);
    vectorRight.resize(n2);

    /* copia dados do vectorLeft[] e vectorRight[] */
    for ( i = 0; i < n1; i++ ) {
        vectorLeft[i] = auxVector[left + i];
    }
    for ( j = 0; j < n2; j++ ) {
        vectorRight[j] = auxVector[middle + 1 + j];
    }

    /* Junta (meger) os arrays em auxVector[left..right]*/
    i = 0; // Index inicial do primeiro subarray
    j = 0; // Index inicial do segundo subarray
    k = left; // Index inicial do subarray do 'Merge'
    while ( i < n1 && j < n2 ) {
        if ( vectorLeft[i]->getPeso() <= vectorRight[j]->getPeso() ) {
            auxVector[k] = vectorLeft[i];
            i++;
        } else {
            auxVector[k] = vectorRight[j];
            j++;
        }
        k++;
    }

    /* Copia elementos restantes do vectorLeft[], se existir*/
    while ( i < n1 ) {
        auxVector[k] = vectorLeft[i];
        i++;
        k++;
    }

    /* Copia elementos restando do vectorRight[], se existir */
    while ( j < n2 ) {
        auxVector[k] = vectorRight[j];
        j++;
        k++;
    }
}
