#include <algorithm>
#include "Grafo.h"

using namespace std;

/**
 * @brief Imprime a lista de adjacência do grafo
 * @return void
*/
void Grafo::printListaAdjacencia() {
    cout << "Lista de Adjacência: " << endl;
    for (auto &no: *this->NOS) {
        cout << "No | " << no.first << " | : ";
        for (auto &aresta: no.second->getArestas()) {
            if (this->isPonderado())
                cout << "|" << aresta.first << "|(" << aresta.second->getPeso() << "), ";
            else
                cout << "|" << aresta.first << "|, ";
        }
        cout << endl;
    }
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

void Grafo::salvaFecho(set<No *> *fecho, const string &tipo) {
    if (!this->getOutput()->is_open()) {
        cout << "Erro ao abrir os arquivos!" << endl;
        return;
    }

    for (auto &no: *fecho) {
        *this->getOutput() << no->getID() << ", ";
    }
    *this->getOutput() << "]" << endl;
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