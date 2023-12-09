#include <algorithm>
#include "Grafo.h"

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

        AGMKruskal->inserirNo(Origem->getID(), Origem->getPeso());
        AGMKruskal->inserirNo(Destino->getID(), Destino->getPeso());
        AGMKruskal->criarAresta(Origem->getID(), Destino->getID(), aresta->getPeso());

        //Remove aresta do vetor de arestas ordenadas
        auto position = find(arestasOrdenadas->begin(), arestasOrdenadas->end(), aresta) - arestasOrdenadas->begin();
        arestasOrdenadas->erase(arestasOrdenadas->begin() + position);
    }

    return AGMKruskal;
}