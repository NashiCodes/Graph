#ifndef GRAFOS_MENU_H
#define GRAFOS_MENU_H

#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include "models/Grafo.cpp"
#include "models/No.h"
#include "models/Aresta.h"

using namespace std;

class Grafo;

class Menu {
private:
    Grafo *grafo;
public:
    explicit Menu(Grafo *grafo) {
        this->grafo = grafo;
    };

    virtual ~Menu() {
        delete grafo;
    };

    void menuPrincipal() {
        int opcao;
        do {
            cout << endl;
            cout << "   ------  MENU ------" << endl;
            cout << "[1] Fecho transitivo direto de um vertice" << endl;
            cout << "[2] Fecho transitivo indireto de um vertice" << endl;
            cout << "[3] Coeficiente de agrupamento local de um vertice" << endl;
            cout << "[4] Coeficiente de agrupamento medio do grafo" << endl;
            cout << "[5] Caminho Minimo entre dois vertices - Dijkstra " << endl;
            cout << "[6] Caminho Minimo entre dois vertices - Floyd" << endl;
            cout << "[7] Arvore Geradora Minima - Prim" << endl;
            cout << "[8] Arvore Geradora Minima - Kruskal " << endl;
            cout << "[9] Caminhamento em profundidade " << endl;
            cout << "[0] Sair" << endl;

            cin >> opcao;
            selecao(opcao);

        } while (opcao != 0);
    }

    void selecao(int opcao) {
        switch (opcao) {
            //Fecho transitivo direto de um vértice
            case 1: {
                int id;
                cout << "Digite o ID do vertice para seu fecho transitivo direto: ";
                cin >> id;
                auto temp = grafo->fechoTransitivoDireto(id);
                grafo->salvaFecho(temp, "Direto");
                delete temp;
                break;
            }
                //Fecho transitivo indireto de um vértice;
            case 2: {
                int id;
                cout << "Digite o ID do vertice para seu fecho transitivo indireto: ";
                cin >> id;
                grafo->fechoTransitivoIndireto(id);
                break;
            }
                //Coeficiente de agrupamento local de um vértice;
            case 3: {
                int id;
                cout << "Digite o ID do vertice: ";
                cin >> id;
                cout << "Coeficiente do nó " << id << ": " << grafo->localClusteringCoefficient(id) << endl;
                break;
            }
                //Coeficiente de agrupamento médio do grafo;
            case 4: {
                cout << "Coeficiente Medio de agrupamento do grafo";
//                cout << " = " << grafo->averageClusteringCoefficient() << endl;
                break;
            }
                // Djkstra
                // Caminho Mínimo entre dois vértices - Dijkstra ;
            case 5: {
                int id1, id2;
                cout << "Digite o vértcie de inicio: ";
                cin >> id1;
                cout << "Digite o vértcie final: ";
                cin >> id2;
                grafo->dijkstra(id1, id2);
                break;
            }
            case 6: {
                int id_one, id_two;
                cout << "Digite o id do vertice de origem: ";
                cin >> id_one;
                cout << "Digite o id do vertice de destino: ";
                cin >> id_two;
                grafo->Floyd(id_one, id_two);
                break;
            }
                //Árvore Geradora Mínima - Prim;
            case 7: {
                if (grafo->isPonderado() && !grafo->isDirecionado()) {
                    cout << "Arvore Geradora Minima - Prim" << endl;
                    grafo->Prim(grafo->getVerticeInduzido());
                } else
                    cout << "Grafo não é ponderado ou é direcionado" << endl;
                break;
            }
                //Árvore Geradora Mínima - Kruskal;
            case 8: {
                if (!grafo->isPonderado() && grafo->isDirecionado())
                    cout << "Grafo não é ponderado ou é direcionado" << endl;
                else {
                    cout << "Arvore Geradora Minima - Kruskal" << endl;
                    grafo->Kruskal(grafo->getVerticeInduzido());
                }
                break;
            }
                //Caminhamento em profundidade;
            case 9: {
                // output_file.close();
                int id;
                cout << "Digite o vértice de inicio: ";
                cin >> id;
//                grafo->depthFirstSearch(output_file, id);
                break;
            }
            case 10: {
                cout << "Algoritimo Guloso: ";
                grafo->algoritmoGuloso(*this->grafo);
                break;
            }
            case 11: {
                printarGrafo();
                break;
            }
            default: {
                cout << "Exit!!!" << endl;
            }

        }
    }

    void printarGrafo() {
        grafo->printListaAdjacencia();
        salvarListaAdjacencia(grafo);
    }


    static void salvarListaAdjacencia(Grafo *grafo) {
        ofstream *arquivo = grafo->getOutput();

        if (arquivo->is_open()) {
            *arquivo << "Lista de Adjacência: " << endl;
            for (auto &no: *grafo->getNos()) {
                *arquivo << "No | " << no.first << " | : ";
                for (auto &aresta: no.second->getArestas()) {
                    if (grafo->isPonderado())
                        *arquivo << "|" << aresta.first << "|(" << aresta.second->getPeso() << "), ";
                    else
                        *arquivo << "|" << aresta.first << "|, ";
                }
                *arquivo << endl;
            }
        } else {
            cout << "Não foi possível abrir o arquivo de saída!" << endl;
        }
    }

    void inserirNo() {
        int idNo, peso = 0;
        cout << "Digite o ID do nó: ";
        cin >> idNo;

        if (grafo->isVerticePonderado()) {
            cout << "Digite o peso do nó: ";
            cin >> peso;
        }

        try {
            grafo->inserirNo(idNo, peso);
        } catch (exception &e) {
            cout << "Erro ao inserir nó!" << endl;
            cout << e.what() << endl;
        }
    }

    void criarAresta() {
        int idNoOrigem, idNoDestino, peso = 0;
        cout << "Digite o ID do nó de origem: ";
        cin >> idNoOrigem;
        cout << "Digite o ID do nó de destino: ";
        cin >> idNoDestino;

        if (grafo->isPonderado()) {
            cout << "Digite o peso da aresta: ";
            cin >> peso;
        }

        try {
            grafo->criarAresta(idNoOrigem, idNoDestino, peso);
        } catch (exception &e) {
            cout << "Erro ao criar aresta!" << endl;
            cout << e.what() << endl;
        }
    }
};

#endif // GRAFOS_MENU_H
