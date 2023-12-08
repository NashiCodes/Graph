#include <algorithm>
#include "Grafo.h"
// Aqui contem as funçoes comuns e auxiliares para os grafos
using namespace std;

///@brief Retorna os nós que incidem em um nó
///@param no: Nó
///@return set<No *>
set<No *> *Grafo::incidentes(No *no) {
    auto *nosIncidentes = new set<No *>();
    for (auto &arestas: *this->ARESTAS) {
        if (arestas.second->getDestino() == no) {
            nosIncidentes->insert(arestas.second->getOrigem());
        }
    }
    return nosIncidentes;
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
    if (!this->getPart()) {
        for (auto &no: *this->NOS) {
            verticeInduzido->insert(no.second);
        }
        return verticeInduzido;
    } else
        for (auto &no: *this->NOS) {
            nosPossiveis->insert(no.first);
        }

    this->menuGvi(verticeInduzido, nosPossiveis);
    Grafo::imprimeVerticeInduzido(verticeInduzido);

    return verticeInduzido;
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
            inserted = false;
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