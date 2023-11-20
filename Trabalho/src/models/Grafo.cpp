#include "Grafo.h"
#include <climits>
#include <algorithm>

#define INF 9999

using namespace std;

/**
 * @brief Imprime a lista de adjacência do grafo
 * @return void
*/
void Grafo::PrintListaAdjacencia() {
    cout << "Lista de Adjacência: " << endl;
    for (auto &no: *this->NOS) {
        cout << "| " << no.first << " | : ";
        for (auto &aresta: no.second->getArestas()) {
            if (this->isPonderado())
                cout << "|" << aresta.first << "|(" << aresta.second->getPeso() << "), ";
            else
                cout << "|" << aresta.first << "|, ";

            cout << endl;
        }
        cout << endl;
    }
}

/**
 * @brief Imprime o fecho transitivo direto do grafo
 * @param idNo: Identificador do nó
 * @return void
*/
void Grafo::fechoTransitivoDireto(int idNo) {
    if (!this->isDirecionado() || !this->existeNo(idNo)) return;

    auto *no = this->NOS->at(idNo);
    cout << "Fecho Transitivo Direto: " << endl;
    cout << "Nó: " << no->getID() << endl << "[ ";
    auto *nosVisitados = new set<No *>();
    auxFTD(no, nosVisitados);

    for (auto &noVisitado: *nosVisitados) {
        cout << noVisitado->getID() << ", ";
    }
    cout << "]" << endl;
}

/**
 * @brief Função auxiliar para o fecho transitivo direto
 * @param no: Nó
 * @param level: Nível
 * @param nosVisitados: Nós visitados
 * @return void
*/
void Grafo::auxFTD(No *no, set<No *> *nosVisitados) {
    if (no == nullptr) return;

    if (nosVisitados->find(no) != nosVisitados->end())return;

    nosVisitados->insert(no);

    for (auto &aresta: no->getArestas()) {
        auto arestaDestino = aresta.second;
        auto noDestino = arestaDestino->getDestino();
        auxFTD(noDestino, nosVisitados);
    }
}

/**
 * @brief Imprime o fecho transitivo indireto do grafo
 * @param idNo: Identificador do nó
 * @return void
*/
void Grafo::fechoTransitivoIndireto(int idNo) {
    if (!this->isDirecionado() || !this->existeNo(idNo)) return;

    auto *no = this->NOS->at(idNo);
    cout << "Fecho Transitivo Indireto: " << endl;
    cout << "Nó: " << no->getID() << endl << "[ ";
    auto *nosVisitados = new set<No *>();
    set<No *> *nosIncidentes = incidentes(no);
    auxFTI(no, nosVisitados, nosIncidentes);

    for (auto &noVisitado: *nosVisitados) {
        cout << noVisitado->getID() << ", ";
    }
    cout << "]" << endl;
}

/**
 * @brief Função auxiliar para o fecho transitivo indireto
 * @param no: Nó
 * @param level: Nível
 * @param nosVisitados: Nós visitados
 * @param nosIncidentes: Nós incidentes
 * @return void
*/
void Grafo::auxFTI(No *no, set<No *> *nosVisitados, set<No *> *nosIncidentes) {
    if (no == nullptr) return;

    if (nosVisitados->find(no) != nosVisitados->end()) return;

    nosVisitados->insert(no);

    for (auto &noIncidente: *nosIncidentes) {
        set<No *> *auxNosIncidentes = incidentes(noIncidente);
        auxFTI(noIncidente, nosVisitados, auxNosIncidentes);
    }
}

/**
 * @brief Retorna os nós que incidem em um nó
 * @param no: Nó
 * @return set<No *>
*/
set<No *> *Grafo::incidentes(No *no) {
    auto *nosIncidentes = new set<No *>();
    for (auto &arestas: *this->ARESTAS) {
        if (arestas.second->getDestino() == no) {
//            int idno = arestas.second->getNoOrigem();
        }
    }
    return nosIncidentes;
}

long Grafo::localClusteringCoefficient(int idNo) {
    if (!this->existeNo(idNo)) return -1;

    auto *no = this->NOS->at(idNo);
    auto *nosVizinhos = new set<No *>();
    for (auto &aresta: no->getArestas()) {
        nosVizinhos->insert(aresta.second->getDestino());
    }

    long numArestas = 0;
    for (auto &noVizinho: *nosVizinhos) {
        for (auto &aresta: noVizinho->getArestas()) {
            if (nosVizinhos->find(aresta.second->getDestino()) != nosVizinhos->end()) {
                numArestas++;
            }
        }
    }

    long numVizinhos = (long) nosVizinhos->size();
    if (numVizinhos <= 1) return 0;

    return numArestas / (numVizinhos * (numVizinhos - 1));
}

/// @brief
/// @param id1
/// @param id2
/// @return
float Grafo::dijkstra(int id1, int id2) {
    if (!this->existeNo(id1)) return -1;
    if (!this->existeNo(id2)) return -1;
    float infinito = (float) INT_MAX / 2;
    auto *no1 = this->NOS->at(id1);
    auto *no2 = this->NOS->at(id2);
    for (auto &aresta: no1->getArestas()) {
        cout << aresta.second->getPeso() << endl;
    }
    return 1;

}


/// @brief Caminho mínimo entre dois nós (Floyd)
/// @param idNoOrigem: Identificador do nó de origem
/// @param idNoDestino: Identificador do nó de destino
/// @return void
void Grafo::Floyd(int idNoOrigem, int idNoDestino) {
    if (!this->existeNo(idNoOrigem)) return;
    if (!this->existeNo(idNoDestino)) return;

    // Inicializa a matriz de distâncias
    auto *dist = new map<int, map<int, int>>();

    // Inicializa a matriz de distâncias A0
    this->floydA0(dist);

    // Executa o algoritmo de Floyd
    // Para cada nó k
    // sendo k o nó intermediário
    for (auto &k: *this->NOS) {
        // Para cada nó i
        // sendo i o nó de origem
        for (auto &i: *this->NOS) {
            // Para cada nó j
            // sendo j o nó de destino
            for (auto &j: *this->NOS) {
                // Se a distância de i até j for maior que a distância de i até k + a distância de k até j
                if ((*dist)[i.first][j.first] > (*dist)[i.first][k.first] + (*dist)[k.first][j.first]) {
                    // A distância de i até j passa a ser a distância de i até k + a distância de k até j
                    (*dist)[i.first][j.first] = (*dist)[i.first][k.first] + (*dist)[k.first][j.first];

                    // Se o grafo não for direcionado, a distância de j até i também passa a ser a distância de j até k + a distância de k até i
                    if(!this->isDirecionado())
                        (*dist)[j.first][i.first] = (*dist)[i.first][k.first] + (*dist)[k.first][j.first];
                }
            }
        }
    }

    // Finaliza a execução do algoritmo de Floyd e imprime o resultado
    this->finalizaFloyd(dist, idNoOrigem, idNoDestino);

    // Libera a memória
    delete dist;
}


/// @brief Finaliza a execução do algoritmo de Floyd e imprime o resultado
/// @param dist: Mapa de distâncias
/// @param idOrigem: Identificador do nó de origem
/// @param idoDestino: Identificador do nó de destino
/// @return void
void Grafo::finalizaFloyd(map<int, map<int, int>> *dist, int idOrigem, int idoDestino) {
    cout << "Caminho mínimo entre " << idOrigem << " e " << idoDestino << ": " << (*dist)[idOrigem][idoDestino]
         << endl;
    int opcao;

    cout << "Deseja imprimir a matriz ?" << endl;
    cout << "1 - Sim" << endl;
    cout << "2 - Não" << endl;
    cin >> opcao;

    if (opcao == 1) {
        cout << endl << "Matriz de distâncias: " << endl;
        for (auto &no: *this->NOS) {
            for (auto &no2: *this->NOS) {
                cout << "[ " << (*dist)[no.first][no2.first] << " ]";
            }
            cout << endl;
        }
        cout << endl;
    }


    cout << "Deseja salvar a matriz ?" << endl;
    cout << "1 - Sim" << endl;
    cout << "2 - Não" << endl;
    cin >> opcao;

    if (opcao == 1) {

        if (!this->getOutput()->is_open()) {
            cout << "Erro ao abrir os arquivos!" << endl;
            return;
        }
        for (auto &no: *this->NOS) {
            for (auto &no2: *this->NOS) {
                *this->getOutput() << "[ " << (*dist)[no.first][no2.first] << " ]";
            }
            *this->getOutput() << endl;
        }
    }

    cout << "Matriz Salva com Sucesso!" << endl;
    cout << endl;
}


/// @brief Inicializa a matriz de distâncias A0
/// @param dist: Mapa de distâncias
/// @return void
void Grafo::floydA0(map<int, map<int, int>> *dist) {
    auto arestas = this->ARESTAS;

    // Inicializa a matriz de distâncias
    for (auto &no: *this->NOS) {
        (*dist)[no.first] = map<int, int>();
        for (auto &no2: *this->NOS) {
            if (no.first == no2.first)
                // Distância de um nó para ele mesmo é 0
                (*dist)[no.first][no2.first] = 0;
            else
                // Distância de um nó para outro é infinito
                (*dist)[no.first][no2.first] = INF;
        }
    }

    // Preenche a matriz de distâncias com os valores de peso das arestas
    for (auto &aresta: *arestas) {
        // Preenche o valor de peso da aresta no sentido correto
        (*dist)[aresta.second->getIdOrigem()][aresta.second->getIdDestino()] = aresta.second->getPeso();
        // Se o grafo não for direcionado, preenche o valor de peso da aresta no sentido contrário
        if (!this->isDirecionado())
            (*dist)[aresta.second->getIdDestino()][aresta.second->getIdOrigem()] = aresta.second->getPeso();
    }
}
