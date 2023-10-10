#include "Grafo.h"

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
[[maybe_unused]] void Grafo::fechoTransitivoDireto(int idNo) {
    if (!this->isDirecionado() || !this->existeNo(idNo)) return;

    auto *no = this->NOS->at(idNo);
    cout << "Fecho Transitivo Direto: " << endl;
    auto *nosVisitados = new set<No *>();
    auxFTD(no, 0, nosVisitados);
}

/**
 * @brief Função auxiliar para o fecho transitivo direto
 * @param no: Nó
 * @param level: Nível
 * @param nosVisitados: Nós visitados
 * @return void
*/
void Grafo::auxFTD(No *no, int level, set<No *> *nosVisitados) {
    if (no == nullptr) return;
    if (nosVisitados->find(no) != nosVisitados->end())
        return;

    nosVisitados->insert(no);
    for (int i = 0; i < level; i++) {
        cout << " --- " << i;
    }
    cout << " -> " << no->getID() << endl;

    for (auto &aresta: no->getArestas()) {
        auto arestaDestino = aresta.second;
        auto noDestino = arestaDestino->getNoDestino();
        auxFTD(noDestino, level + 1, nosVisitados);
    }
}

/**
 * @brief Imprime o fecho transitivo indireto do grafo
 * @param idNo: Identificador do nó
 * @return void
*/
[[maybe_unused]] void Grafo::fechoTransitivoIndireto(int idNo) {
    if (!this->isDirecionado() || !this->existeNo(idNo)) return;

    auto *no = this->NOS->at(idNo);
    cout << "Fecho Transitivo Indireto: " << endl;
    cout << "Nó: " << no->getID() << endl;
    auto *nosVisitados = new set<No *>();
    set<No *> *nosIncidentes = incidentes(no);
    auxFTI(no, 0, nosVisitados, nosIncidentes);
}

/**
 * @brief Função auxiliar para o fecho transitivo indireto
 * @param no: Nó
 * @param level: Nível
 * @param nosVisitados: Nós visitados
 * @param nosIncidentes: Nós incidentes
 * @return void
*/
void Grafo::auxFTI(No *no, int level, set<No *> *nosVisitados, set<No *> *nosIncidentes) {
    if (no == nullptr) return;
    if (nosVisitados->find(no) != nosVisitados->end()) return;

    nosVisitados->insert(no);

    for (auto &noIncidente: *nosIncidentes) {
        for (int i = 0; i < level; i++) {
            cout << "---";
        }
        cout << ">" << noIncidente->getID() << endl;
        nosVisitados->insert(noIncidente);
        set<No *> *auxNosIncidentes = incidentes(noIncidente);
        auxFTI(noIncidente, level + 1, nosVisitados, auxNosIncidentes);
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
        if (arestas.second->getNoDestino() == no) {
            nosIncidentes->insert(arestas.second->getNoOrigem());
        }
    }
    return nosIncidentes;
}

[[maybe_unused]] set<int> *Grafo::getFTD(int idNo) {
    if (!this->isDirecionado() || !this->existeNo(idNo)) return nullptr;

    auto *no = this->NOS->at(idNo);
    auto *nosVisitados = new set<No *>();
    auxFTD(no, 0, nosVisitados);
    return nullptr;
}



