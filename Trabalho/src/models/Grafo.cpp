#include "Grafo.h"
#include "limits.h"
#define INF 1e9;
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
        auto noDestino = arestaDestino->getNoDestino();
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
        if (arestas.second->getNoDestino() == no) {
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
        nosVizinhos->insert(aresta.second->getNoDestino());
    }

    long numArestas = 0;
    for (auto &noVizinho: *nosVizinhos) {
        for (auto &aresta: noVizinho->getArestas()) {
            if (nosVizinhos->find(aresta.second->getNoDestino()) != nosVizinhos->end()) {
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
float Grafo::dijkstra(int id1,int id2){
    if (!this->existeNo(id1)) return -1;
    if (!this->existeNo(id2)) return -1;
    float infinito = INT_MAX/2;
    auto *no1 = this->NOS->at(id1);
    auto *no2 = this->NOS->at(id2);
    for(auto &aresta: no1->getArestas()) {
       cout << aresta.second->getPeso() << endl;
    }
    return 1;
    
}

void Grafo::Floyd(int idNoOrigem, int idNoDestino, map<int, No *> *NOS;){

    // Criando matriz adjacente
    // i / j = id de cada nó
    // (i,j) = dist entre o nó i para o nó j

    int qtdNos = NOS.size(); 
    int* dist = new [tam][tam];

    for(int i = 0; i <= tam; i++){

        map<int, Aresta> arestas = NOS[i]->ARESTAS;
        int qtdAresta = ARESTAS.size();

        for(int j = 0; j <= qtdAresta; j++){
            // Se ID no = ID noDestino, então o peso é 0 pois o peso de um nó para ele mesmo é 0
            if(arestas[j]->noDestino->ID == i + 1){ 
                dist[i][j] = 0;
            }
            // Se ID no != ID noDestino, então atribuir o peso  da aresta (se ela existir)
            elseif(arestas[j]->noDestino->ID != i + 1){
                dist[i][j] = aresta[j]->PESO;
            }
            // Se a aresta não existir, ent o valor é INFINITO (INF)
            else{
                dist[i][j] = INF;
            }
        }
    }

    // Implementação do algorímo
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    cout << "O peso do caminho mínimo entre " << idNoOrigem << " e " << idNoDestino << " é: " << dist[idNoOrigem][idNoDestino] << endl; 

}