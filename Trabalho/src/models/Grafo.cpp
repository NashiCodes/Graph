#include "Grafo.h"
#include <climits>
#include <algorithm>
#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
//#define INF 99999999
using namespace std;

/**
 * @brief Imprime a lista de adjacência do grafo
 * @return void
*/
void Grafo::printListaAdjacencia() {
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
set<No *> *Grafo::fechoTransitivoDireto(int idNo) {
    if (!this->isDirecionado() || !this->existeNo(idNo)) return nullptr;

    auto *no = this->NOS->at(idNo);
    cout << "Fecho Transitivo Direto: " << endl;
    cout << "Nó: " << no->getID() << endl << "[ ";
    auto *nosVisitados = new set<No *>();
    auxFtd(no, nosVisitados);

    return nosVisitados;
}

/**
 * @brief Função auxiliar para o fecho transitivo direto
 * @param no: Nó
 * @param level: Nível
 * @param nosVisitados: Nós visitados
 * @return void
*/
void Grafo::auxFtd(No *no, set<No *> *nosVisitados) {
    if (no == nullptr) return;

    if (nosVisitados->find(no) != nosVisitados->end())return;

    nosVisitados->insert(no);

    for (auto &aresta: no->getArestas()) {
        auto arestaDestino = aresta.second;
        auto noDestino = arestaDestino->getDestino();
        auxFtd(noDestino, nosVisitados);
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
    auxFti(no, nosVisitados, nosIncidentes);

    this->salvaFecho(nosVisitados, "Indireto");

    delete nosIncidentes;
    delete nosVisitados;
}

/**
 * @brief Função auxiliar para o fecho transitivo indireto
 * @param no: Nó
 * @param level: Nível
 * @param nosVisitados: Nós visitados
 * @param nosIncidentes: Nós incidentes
 * @return void
*/
void Grafo::auxFti(No *no, set<No *> *nosVisitados, set<No *> *nosIncidentes) {
    if (no == nullptr) return;

    if (nosVisitados->find(no) != nosVisitados->end()) return;

    nosVisitados->insert(no);

    for (auto &noIncidente: *nosIncidentes) {
        set<No *> *auxNosIncidentes = incidentes(noIncidente);
        auxFti(noIncidente, nosVisitados, auxNosIncidentes);
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
            nosIncidentes->insert(arestas.second->getOrigem());
        }
    }
    return nosIncidentes;
}

void Grafo::salvaFecho(set<No *> *fecho, const string &tipo) {
    if (!this->getOutput()->is_open()) {
        cout << "Erro ao abrir os arquivos!" << endl;
        return;
    }

    *this->getOutput() << "Fecho Transitivo " << tipo << endl;
    for (auto &no: *fecho) {
        *this->getOutput() << no->getID() << ", ";
    }
    *this->getOutput() << endl;
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
/// @param _Origem_
/// @param _Destino_
/// @return
void Grafo::dijkstra(int origem, int destino) {
    try {
        if (!this->existeNo(origem)) throw invalid_argument("Nó de origem não existe");
        if (!this->existeNo(destino)) throw invalid_argument("Nó de destino não existe");
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
        return;
    }

    auto *FTD = fechoTransitivoDireto(origem);
    auto *Origem = this->NOS->at(origem);
    auto *Destino = this->NOS->at(destino);

    try {
        if (FTD->find(Destino) == FTD->end()) throw invalid_argument("Não existe caminho entre os nós");
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
        return;
    }

    auto infinito = INT_MAX / 2;
    auto *dist = new map<int, int>();
    auto *vistos = new set<int>();

    (*dist)[origem] = 0;

    for (auto *no: *FTD) {
        (*dist)[no->getID()] = infinito;

        if (Origem->getArestas().find(no->getID()) != Origem->getArestas().end())
            (*dist)[no->getID()] = Origem->getAresta(no->getID())->getPeso();
    }

    this->auxDijkstra(dist, vistos, FTD);
    this->imprimeDijkstra(dist, origem, destino);

    delete FTD;
    delete dist;
    delete vistos;
}

void Grafo::auxDijkstra(map<int, int> *dist, set<int> *vistos, set<No *> *FTD) {
    int minIdx = Grafo::minDistance(dist, vistos, FTD);

    vistos->insert(minIdx);
    FTD->erase(this->NOS->at(minIdx));

    for (auto &aresta: this->NOS->at(minIdx)->getArestas()) {
        if (vistos->find(aresta.second->getDestino()->getID()) == vistos->end()) {
            (*dist)[aresta.second->getDestino()->getID()] = min((*dist)[aresta.second->getDestino()->getID()],
                                                                (*dist)[minIdx] + aresta.second->getPeso());
        }
    }
}

int Grafo::minDistance(map<int, int> *dist, set<int> *vistos, set<No *> *FTD) {
    int min = INT_MAX, min_index;

    for (auto *no: *FTD) {
        if (vistos->find(no->getID()) == vistos->end() && (*dist)[no->getID()] <= min) {
            min = (*dist)[no->getID()];
            min_index = no->getID();
        }
    }

    return min_index;
}

void Grafo::imprimeDijkstra(map<int, int> *dist, int idOrigem, int idDestino) {
    cout << "O caminho mínimo entre " << idOrigem << " e " << idDestino << " é: " << (*dist)[idDestino] << endl;

    int opcao;

    cout << "Deseja imprimir todos os caminhos minimos do nó " << idOrigem << " ?" << endl;
    cout << "1 - Sim" << endl;
    cout << "2 - Não" << endl;
    cin >> opcao;

    if (opcao == 1) {
        cout << endl << "Caminhos mínimos: " << endl;
        for (auto no: *dist) {
            cout << "Caminho mínimo entre " << idOrigem << " e " << no.first << ": " << (*dist)[no.first] << endl;
        }
        cout << endl;
    }

    cout << "Deseja salvar o caminho mínimo entre " << idOrigem << " e " << idDestino << " ?" << endl;
    cout << "1 - Sim" << endl;
    cout << "2 - Não" << endl;
    cin >> opcao;

    if (opcao == 1) {
        if (!this->getOutput()->is_open()) {
            cout << "Erro ao abrir os arquivos!" << endl;
        }
        *this->getOutput() << "O caminho mínimo entre " << idOrigem << " e " << idDestino << " é: "
                           << (*dist)[idDestino] << endl;
    }

    cout << "Caminho Mínimo Salvo com Sucesso!" << endl;
    cout << endl;

    cout << "Deseja salvar todos os caminhos minimos do nó " << idOrigem << " ?" << endl;
    cout << "1 - Sim" << endl;
    cout << "2 - Não" << endl;
    cin >> opcao;

    if (opcao == 1) {
        if (!this->getOutput()->is_open()) {
            cout << "Erro ao abrir os arquivos!" << endl;
        }
        for (auto no: *dist) {
            if (no.first == idDestino) continue;
            *this->getOutput() << "Caminho mínimo entre " << idOrigem << " e " << no.first << ": " << (*dist)[no.first]
                               << endl;
        }
    }

    cout << "Caminhos Mínimos Salvos com Sucesso!" << endl;
    cout << endl;
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

                    // Se o grafo não for direcionado, a distância de j até i também passa a ser
                    // a distância de j até k + a distância de k até i
                    if (!this->isDirecionado())
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
                (*dist)[no.first][no2.first] = INT_MAX;
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

set<No *> *Grafo::getVerticeInduzido() {
    auto *nosPossiveis = new set<int>();
    auto *verticeInduzido = new set<No *>();
//    for (auto &no: *this->NOS) {
//        nosPossiveis->insert(no.first);
//    }
//
//    this->menuGvi(verticeInduzido, nosPossiveis);
//    Grafo::imprimeVerticeInduzido(verticeInduzido);
    for (auto &no: *this->NOS) {
        verticeInduzido->insert(no.second);
    }

    return verticeInduzido;
}

void Grafo::menuGvi(set<No *> *verticeInduzido, set<int> *nosPossiveis) {
    int opcao = -1;
    while (opcao != 0 && !nosPossiveis->empty()) {
        cout << "Escolha uma opção: " << endl;
        cout << "1 - Inserir nó" << endl;
        if (!verticeInduzido->empty()) {
            cout << "2 - Remover nó" << endl;
            cout << "3 - Imprimir Vertice Induzido" << endl;
        }

        cout << "0 - Sair" << endl;
        cin >> opcao;

        switch (opcao) {
            case 1:
                this->insereGvi(verticeInduzido, nosPossiveis);
                break;
            case 2:
                if (!verticeInduzido->empty())
                    this->removeGvi(verticeInduzido, nosPossiveis);
                break;
            case 3:
                if (!verticeInduzido->empty())
                    Grafo::imprimeVerticeInduzido(verticeInduzido);
                break;
            case 0:
                return;
            default:
                cout << "Opção inválida!" << endl;
                break;
        }
    }
}

void Grafo::insereGvi(set<No *> *verticeInduzido, set<int> *nosPossiveis) {
    cout << "Digite o ID do nó que deseja inserir: " << endl;
    Grafo::imprimeNosPossiveis(nosPossiveis);
    int idNo;
    cin >> idNo;

    if (this->existeNo(idNo) && nosPossiveis->find(idNo) != nosPossiveis->end()) {
        verticeInduzido->insert(this->NOS->at(idNo));
        nosPossiveis->clear();

        for (auto &no: *verticeInduzido)
            for (auto &aresta: no->getArestas()) {
                if (verticeInduzido->find(aresta.second->getDestino()) == verticeInduzido->end())
                    nosPossiveis->insert(aresta.second->getIdDestino());
                else if (verticeInduzido->find(aresta.second->getOrigem()) == verticeInduzido->end())
                    nosPossiveis->insert(aresta.second->getIdOrigem());
            }
    } else
        cout << "Nó inválido!" << endl;

}

void Grafo::removeGvi(set<No *> *verticeInduzido, set<int> *nosPossiveis) {
    cout << "Digite o ID do nó que deseja remover: " << endl;
    Grafo::imprimeVerticeInduzido(verticeInduzido);
    int idNo;
    cin >> idNo;

    if (this->existeNo(idNo) && verticeInduzido->find(this->NOS->at(idNo)) != verticeInduzido->end()) {
        verticeInduzido->erase(this->NOS->at(idNo));
        nosPossiveis->clear();

        if (!verticeInduzido->empty()) {
            for (auto &no: *verticeInduzido) {
                for (auto &aresta: no->getArestas()) {
                    if (verticeInduzido->find(aresta.second->getDestino()) == verticeInduzido->end())
                        nosPossiveis->insert(aresta.second->getIdDestino());
                    else if (verticeInduzido->find(aresta.second->getOrigem()) == verticeInduzido->end())
                        nosPossiveis->insert(aresta.second->getIdOrigem());
                }
            }
        } else
            for (auto &no: *this->NOS)
                nosPossiveis->insert(no.first);

    } else
        cout << "Nó inválido!" << endl;
}

vector<Aresta *> *Grafo::OrdenaArestas(set<No *> *verticeInduzido) {
    // Cria um vetor ordenado de arestas usando o comparador de arestas
    auto *arestas = new vector<Aresta *>();

    // Percorre todos os nós do vetor de vértices induzidos
    for (auto Aresta: *this->ARESTAS) {
        // Se os nós de origem e destino da aresta estiverem no vetor de vértices induzidos
        if (verticeInduzido->find(Aresta.second->getOrigem()) != verticeInduzido->end() &&
            verticeInduzido->find(Aresta.second->getDestino()) != verticeInduzido->end()) {
            // Insere a aresta na posição correta do vetor ordenado
            arestas->insert(upper_bound(arestas->begin(), arestas->end(), Aresta.second, Aresta::comparaAresta),
                            Aresta.second);
        }
    }

    return arestas;
}

void Grafo::Prim(set<No *> *verticeInduzido) {
    //Verifica se o vertice induzido é vazio
    if (verticeInduzido->empty()) {
        cout << "Vertice induzido vazio!" << endl;
        return;
    }

    // Ordena as arestas vertice induzido e armazena em uma fila de prioridade
    auto *fila = this->OrdenaArestas(verticeInduzido);

    // Cria um novo grafo para armazenar a AGM
    auto agm = new Grafo(this->isPonderado(), this->isVerticePonderado(), this->isDirecionado());

    // Insere o primeiro nó da fila na AGM
    auto *Raiz = fila->at(0)->getOrigem();
    agm->InserirNo(Raiz->getID(), Raiz->getPeso());

    // Adiciona o nó atual ao vetor de nós visitados
    auto *nosVisitados = new set<No *>();
    nosVisitados->insert(Raiz);

    // Enquanto o vetor de nós visitados não contiver todos os nós do vetor de vértices induzidos
    while (nosVisitados->size() < verticeInduzido->size()) {
        No *noPai = nullptr; // Nó de origem da aresta mínima
        No *noMin = nullptr; // Nó de destino da aresta mínima
        Aresta *arestaMin = nullptr;// Aresta mínima
        int min = INT_MAX / 2; // Peso da aresta mínima

        // Percorre todos os nós visitados para encontrar a aresta de menor peso
        for (auto *no: *nosVisitados) {
            // Percorre todas as arestas do nó
            for (auto &aresta: no->getArestas()) {
                // Pega o nó de destino da aresta
                auto *noDestino =
                        aresta.second->getDestino() == no ? aresta.second->getOrigem() : aresta.second->getDestino();
                // Se o nó de destino já estiver no vetor de nós visitados, pula para a próxima iteração
                if (nosVisitados->find(noDestino) != nosVisitados->end()) continue;
                // Se o peso da aresta for maior que o peso mínimo, pula para a próxima iteração
                if (aresta.second->getPeso() > min) continue;

                // Atualiza os valores da aresta mínima
                noPai = no;
                min = aresta.second->getPeso();
                noMin = noDestino;
                arestaMin = aresta.second;
            }
        }
        // Se retornar nullptr, não existe aresta mínima
        if (noMin == nullptr) break;
        // Insere o nó mínimo na AGM
        agm->InserirNo(noMin->getID(), noMin->getPeso());
        // Insere a aresta mínima na AGM
        agm->CriarAresta(noPai->getID(), noMin->getID(), arestaMin->getPeso());
        // Adiciona o nó mínimo ao vetor de nós visitados
        nosVisitados->insert(noMin);
    }

    salvaAGM(agm, Raiz->getID(), "Prim");

    // Libera a memória
    delete fila;
    delete agm;
    delete nosVisitados;
}

void Grafo::salvaAGM(Grafo *AGM, int noRaiz, const string &algoritmo) {
    auto Raiz = AGM->getNos()->at(noRaiz);

    if (!this->getOutput()->is_open()) {
        cout << "Erro ao abrir os arquivos!" << endl;
        return;
    }

    *this->getOutput() << "Arvore Geradora Minima - " << algoritmo << endl;
    *this->getOutput() << "Raiz: " << Raiz->getID() << endl;
    auto *nosVisitados = new set<No *>();

    // Salva a AGM no arquivo de saída fazendo um caminhamento em profundidade
    this->auxSalvaAGM(AGM, Raiz, nosVisitados);
}

void Grafo::auxSalvaAGM(Grafo *AGMPrim, No *pNo, set<No *> *pSet) {
    if (pNo == nullptr) return;

    if (pSet->find(pNo) != pSet->end()) return;

    pSet->insert(pNo);

    for (auto &aresta: pNo->getArestas()) {
        auto arestaDestino = aresta.second;

        auto noDestino = arestaDestino->getDestino() == pNo ? arestaDestino->getOrigem() : arestaDestino->getDestino();
        if (pSet->find(noDestino) != pSet->end()) continue;

        *this->getOutput() << pNo->getID() << " -> " << noDestino->getID() << " Peso: " << arestaDestino->getPeso()
                           << endl;
        auxSalvaAGM(AGMPrim, noDestino, pSet);
    }

    *this->getOutput() << endl;

}

void Grafo::Kruskal(set<No *> *verticeInduzido) {

    // Inicializando Arestas ordenadas
    auto *arestasOrdenadas = this->OrdenaArestas(verticeInduzido);
    //Declarando map de conjuntos disjuntos
    auto *conjuntosDisjuntos = Grafo::inicializaConjuntos(verticeInduzido);

    auto AGMKruskal = auxKruskal(verticeInduzido, arestasOrdenadas, conjuntosDisjuntos);

    auto Raiz = conjuntosDisjuntos->begin().operator*().second->begin().operator*();

    salvaAGM(AGMKruskal, Raiz->getID(), "Kruskal");

    delete arestasOrdenadas;
    delete conjuntosDisjuntos;
    delete verticeInduzido;
    delete AGMKruskal;
}

Grafo *Grafo::auxKruskal(set<No *> *verticeInduzido, vector<Aresta *> *arestasOrdenadas,
                         map<int, set<No *> *> *conjuntosDisjuntos) {

    auto *AGMKruskal = new Grafo(this->isPonderado(), this->isVerticePonderado(), this->isDirecionado());

    while (AGMKruskal->ARESTAS->size() < verticeInduzido->size() - 1) {
        Aresta *aresta = nullptr;
        No *Origem = nullptr;
        No *Destino = nullptr;

        Grafo::buscaArestaKruskal(arestasOrdenadas, conjuntosDisjuntos, Origem, Destino, aresta);

        if (aresta == nullptr || Origem == nullptr || Destino == nullptr) break;

        Grafo::atualizaConjuntos(conjuntosDisjuntos, Origem, Destino);

        AGMKruskal->InserirNo(Origem->getID(), Origem->getPeso());
        AGMKruskal->InserirNo(Destino->getID(), Destino->getPeso());
        AGMKruskal->CriarAresta(Origem->getID(), Destino->getID(), aresta->getPeso());

        //Remove aresta do vetor de arestas ordenadas
        auto position = find(arestasOrdenadas->begin(), arestasOrdenadas->end(), aresta) - arestasOrdenadas->begin();
        arestasOrdenadas->erase(arestasOrdenadas->begin() + position);
    }

    return AGMKruskal;
}

map<int, set<No *> *> *Grafo::inicializaConjuntos(set<No *> *verticeInduzido) {
    auto *conjuntosDisjuntos = new map<int, set<No *> *>();

    //Inicializando conjuntos disjuntos
    for (auto &no: *verticeInduzido) {
        auto *conjunto = new set<No *>();
        conjunto->insert(no);
        conjuntosDisjuntos->insert(pair<int, set<No *> *>(no->getID(), conjunto));
    }

    return conjuntosDisjuntos;
}

void Grafo::buscaArestaKruskal(vector<Aresta *> *arestasOrdenadas, map<int, set<No *> *> *conjuntosDisjuntos,
                               No *&Origem, No *&Destino, Aresta *&aresta) {

    int min = INT_MAX / 2;

    for (auto &arestaOrdenada: *arestasOrdenadas) {
        auto auxOrigem = arestaOrdenada->getOrigem();
        auto auxDestino = arestaOrdenada->getDestino();
        int peso = arestaOrdenada->getPeso();
        if (conjuntosDisjuntos->at(auxOrigem->getID()) == conjuntosDisjuntos->at(auxDestino->getID())) continue;
        if (peso >= min) continue;

        Origem = auxOrigem;
        Destino = auxDestino;
        aresta = arestaOrdenada;
        min = peso;
    }
}

void Grafo::atualizaConjuntos(map<int, set<No *> *> *conjuntosDisjuntos, No *Origem, No *Destino) {

    auto conjOrigem = conjuntosDisjuntos->find(Origem->getID());
    auto conjDestino = conjuntosDisjuntos->find(Destino->getID());

    if (conjOrigem->first < conjDestino->first) {
        auto aux = conjDestino->second;

        for (auto &no: *conjDestino->second) {
            conjuntosDisjuntos->at(no->getID()) = conjOrigem->second;
        }

        conjOrigem->second->merge(*aux);
        conjDestino->second = conjOrigem->second;
        delete aux;
    } else {
        auto aux = conjOrigem->second;

        for (auto &no: *conjOrigem->second) {
            conjuntosDisjuntos->at(no->getID()) = conjDestino->second;
        }
        conjDestino->second->merge(*aux);

        conjOrigem->second = conjDestino->second;
        delete aux;
    }

}

list<No *> Grafo::ordenaLista(Grafo &grafo) {
    list<No *> lista;
    bool inserted;

    for (auto &n: *grafo.NOS) {

        for (auto it = lista.begin(); it != lista.end(); ++it) {
            bool inserted = false;
            if ((*it)->getPeso() > n.second->getPeso()) {
                lista.insert(it, n.second);
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            lista.push_back(n.second);
        }
    }

    return lista;
}


pair<list<list<int>>, int> Grafo::algoritimoGuloso() {
    list<No *> todosNos;
    for (auto n: *NOS) {
        todosNos.push_front(n.second);
    }
    list<int> rota;
    list<list<int>> solucao;
    int caminhao = 1;
    No *menor = NOS->at(2);
    int pontosSolucao = 0;
    No *analisado = NOS->at(1);
    while (!todosNos.empty()) {
        for (auto a: analisado->getArestas()) {
            auto n = *a.second->getDestino();
            if (n.getPeso() < menor->getPeso() && !n.isPassou() &&
                caminhoes.at(caminhao)->capacidade - n.getPeso() < 0) {
                menor = &n;
                pontosSolucao += a.second->getPeso();
            }
        }
        if (menor != analisado) {
            rota.push_front(menor->getID());
            menor->setPassou(true);
            todosNos.remove(menor);
            analisado = menor;
        } else {
            caminhao++;
            rota.push_front(NOS->at(1)->getID());
            solucao.push_front(rota);
            while (!rota.empty()) {
                auto it = rota.begin();
                while (it != rota.end()) {
                    int a = *it;
                    it = rota.erase(it);
                }
            }
            analisado = NOS->at(1);
            for (auto n: *NOS) {
                if (!n.second->isPassou()) {
                    menor = n.second;
                    break;
                }
            }
        }
    }
    return make_pair(solucao, pontosSolucao);
}


pair<list<list<int>>, int> Grafo::algoritimoGulosoRandomizado(double alpha) {
    list<No *> todosNos;
    for (auto n: *NOS) {
        todosNos.push_front(n.second);
    }
    list<int> rota;
    list<list<int>> solucao;
    int caminhao = 1;
    No *menor = nullptr;
    int pontosSolucao = 0;

    No *analisado = NOS->at(1);
    while (!todosNos.empty()) {
        double prob = (double) rand() / RAND_MAX;  // Gera um número aleatório entre 0 e 1
        for (auto a: analisado->getArestas()) {
            auto n = *a.second->getDestino();
            if (menor == nullptr && n.getPeso() < menor->getPeso() && !n.isPassou() &&
                caminhoes.at(caminhao)->capacidade - n.getPeso() < 0 && prob <= alpha) {
                menor = &n;
                pontosSolucao += a.second->getPeso();
            }
        }
        if (menor != analisado) {
            rota.push_front(menor->getID());
            menor->setPassou(true);
            todosNos.remove(menor);
            analisado = menor;
        } else {
            caminhao++;
            rota.push_front(NOS->at(1)->getID());
            solucao.push_front(rota);
            while (!rota.empty()) {
                auto it = rota.begin();
                while (it != rota.end()) {
                    int a = *it;
                    it = rota.erase(it);
                }
            }
            analisado = NOS->at(1);
            menor = nullptr;
        }
    }
    return make_pair(solucao, pontosSolucao);
}


pair<list<list<int>>, int> Grafo::algoritimoGulosoRandomizadoAdaptativo() {

}

