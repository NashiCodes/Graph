#include "Grafo.h"
#include "Basics.cpp"
#include "Output.cpp"
#include "AuxFuncs.cpp"
#include <climits>
#include <algorithm>
#include <set>
#include <vector>
//#define INF 99999999
using namespace std;

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
    agm->inserirNo(Raiz->getID(), Raiz->getPeso());

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
        agm->inserirNo(noMin->getID(), noMin->getPeso());
        // Insere a aresta mínima na AGM
        agm->criarAresta(noPai->getID(), noMin->getID(), arestaMin->getPeso());
        // Adiciona o nó mínimo ao vetor de nós visitados
        nosVisitados->insert(noMin);
    }

    salvaAGM(agm, Raiz->getID(), "Prim");

    // Libera a memória
    delete fila;
    delete agm;
    delete nosVisitados;
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

pair<list<list<int>>, int> Grafo:: algoritmoGuloso(){
    list<No*> todosNos;
    for (auto n: *NOS) {
        todosNos.push_front(n.second);
    }
    list<int> rota;
    list<list<int>> solucao;
    int caminhao = 1;
    No* menor = nullptr;
    int pontosSolucao = 0;
    No *analisado = NOS->at(0);
    int maxDistancia = 0;
    while (!todosNos.empty()) {
        for (auto a:analisado->getArestas()) {
            maxDistancia += a.second->getPeso();
        }
        for(auto a: analisado->getArestas()) {
            auto n = *a.second->getDestino();
            if (menor == nullptr || (n.getPeso() < menor->getPeso() && !n.isPassou() && caminhoes->at(caminhao)->capacidade - n.getPeso() < 0 && a.second->getPeso() < maxDistancia/NOS->size())) {
                menor = &n;
                pontosSolucao += a.second->getPeso();
            }
        }
        if (menor != analisado ) {
            rota.push_front(menor->getID());
            menor->setPassou(true);
            todosNos.remove(menor);
            analisado = menor;
        }else{
            caminhao++;
            rota.push_front(NOS->at(1)->getID());
            solucao.push_front(rota);
            while (!rota.empty()) {
                auto it = rota.begin();
                while (it != rota.end()) {
                    it = rota.erase(it);
                }
            }
            analisado = NOS->at(1);
            for (auto n: *NOS) {
                if(!n.second->isPassou()){
                    menor = n.second;
                    break;
                }
            }
        }
    }
    return make_pair(solucao, pontosSolucao);
}


pair<list<list<int>>, int> Grafo:: algoritmoGulosoRandomizado(double alpha){
    list<No*> todosNos;
    for (auto n: *NOS) {
        todosNos.push_front(n.second);
    }
    list<int> rota;
    list<list<int>> solucao;
    int caminhao = 1;
    No* menor = nullptr;
    int pontosSolucao = 0;
    int maxDistancia = 0;
    int i = 0;
    No *analisado = NOS->at(1);
    while (!todosNos.empty()) {
        for (auto a:analisado->getArestas()) {
            maxDistancia += a.second->getPeso();
        }
        for(auto a: analisado->getArestas()) {
            double prob = (double)rand() / RAND_MAX;  // Gera um número aleatório entre 0 e 1
            auto n = *a.second->getDestino();
            if (menor == nullptr || (n.getPeso() < menor->getPeso() && !n.isPassou() && caminhoes->at(caminhao)->capacidade - n.getPeso() < 0 && prob <= alpha && a.second->getPeso() < maxDistancia/NOS->size())) {
                menor = &n;
                pontosSolucao += a.second->getPeso();
            }else if(!n.isPassou()){
                i++;
            }
        }
        if (menor != analisado && i == 0) {
            rota.push_front(menor->getID());
            menor->setPassou(true);
            todosNos.remove(    menor);
            analisado = menor;
        }else{
            caminhao++;
            rota.push_front(NOS->at(1)->getID());
            solucao.push_front(rota);
            while (!rota.empty()) {
                auto it = rota.begin();
                while (it != rota.end()) {
                    it = rota.erase(it);
                }
            }
            analisado = NOS->at(1);
            menor = nullptr;
        }
    }
    return make_pair(solucao, pontosSolucao);
}

pair<list < list < int>>, int> Grafo::algoritmoGulosoRandomizadoAdaptativo() {
    list<No*> todosNos;
    for (auto& n : *NOS) {
        todosNos.push_front(n.second);
    }

    list<int> rota;
    list<list<int>> solucao;
    int caminhao = 1;
    No* menor = NOS->at(2);
    int pontosSolucao = 0;
    No* analisado = NOS->at(1);

    double probabilidade_base = 0.5;
    double taxa_aprendizado = 0.1;

    srand(static_cast<unsigned int>(time(nullptr)));

    while (!todosNos.empty()) {
        vector<No*> candidatos;
        for (auto& a : analisado->getArestas()) {
            auto* n = a.second->getDestino();
            if (!n->isPassou() && caminhoes->at(caminhao)->capacidade - n->getPeso() >= 0) {
                candidatos.push_back(n);
            }
        }

        if (!candidatos.empty()) {
            double probabilidade_aleatoria = (rand() % 100) / 100.0;

            if (probabilidade_aleatoria < probabilidade_base) {
                menor = candidatos[0];
                for (auto* candidato : candidatos) {
                    if (candidato->getPeso() < menor->getPeso()) {
                        menor = candidato;
                        // Atualize conforme necessário
                        pontosSolucao += candidato->getPeso();
                    }
                }
            } else {
                int indiceAleatorio = rand() % candidatos.size();
                menor = candidatos[indiceAleatorio];
                // Atualize conforme necessário
                pontosSolucao += menor->getPeso();
            }

            probabilidade_base += taxa_aprendizado * (1 - probabilidade_base);
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

            // Limpeza da rota
            rota.clear();

            analisado = NOS->at(1);
            for (auto& n : *NOS) {
                if (!n.second->isPassou()) {
                    menor = n.second;
                    break;
                }
            }
        }
    }

    return make_pair(solucao, pontosSolucao);
}