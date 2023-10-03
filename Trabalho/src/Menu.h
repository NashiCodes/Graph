#ifndef GRAFOS_MENU_H
#define GRAFOS_MENU_H

#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include "Grafo.h"
#include "models/No.h"
#include "models/Aresta.h"

using namespace std;

class Grafo;

class Menu {
private:
    Grafo *grafo{};
    ifstream *entrada{};
    ofstream *arquivoSaida{};
    string linha;
public:
    Menu() = default;

    Menu(Grafo *grafo, ifstream *entrada, ofstream *arquivoSaida) {
        this->grafo = grafo;
        this->entrada = entrada;
        this->arquivoSaida = arquivoSaida;

        try {
            getline(*entrada, linha);
            grafo->setOrdem(stoi(linha));
        } catch (exception &e) {
            cout << "Erro ao ler a ordem do grafo!" << endl;
            cout << e.what() << endl;
        }

        lerArquivo();

    };

    virtual ~Menu() {
        delete grafo;
        delete entrada;
        delete arquivoSaida;
    };

    void menuPrincipal() {
        printarGrafo();
    }

    void lerArquivo() {
        try {
            int i = 0;
            while (!entrada->eof()) {
                if (i >= 10000) break;
                getline(*entrada, linha);
                if (linha.empty()) {
                    break;
                }

                auto id = linha.substr(0, linha.find(' '));
                linha.erase(0, linha.find(' ') + 1);
                auto idDestino = linha.substr(0, linha.find(' '));
                try {
                    grafo->criaNo(stoi(id));
                    grafo->criaNo(stoi(idDestino));
                } catch (exception &e) {
                    cout << "Erro ao inserir nó!" << endl;
                    cout << e.what() << endl;
                }

                if (grafo->isPonderado()) {
                    linha.erase(0, linha.find(' ') + 1);
                    auto peso = linha.substr(0, linha.find(' '));
                    grafo->criarAresta(stoi(id), stoi(idDestino), stoi(peso));
                } else {
                    grafo->criarAresta(stoi(id), stoi(idDestino));
                }
                i++;
            }
        } catch (exception &e) {
            cout << "Erro ao ler o arquivo!" << endl;
            cout << e.what() << endl;
        }
    }

    void printarGrafo() {
        grafo->printListaAdjacencia();
    }

    void inserirNo() {
        cout << "Digite o ID do nó: ";
        int idNo;
        cin >> idNo;
        try {
            grafo->inserirNo(idNo);
        } catch (exception &e) {
            cout << "Erro ao inserir nó!" << endl;
            cout << e.what() << endl;
        }
    }

    void criarAresta() {
        cout << "Digite o ID do nó de origem: ";
        int idNoOrigem;
        cin >> idNoOrigem;
        cout << "Digite o ID do nó de destino: ";
        int idNoDestino;
        cin >> idNoDestino;
        try {
            grafo->criarAresta(idNoOrigem, idNoDestino);
        } catch (exception &e) {
            cout << "Erro ao criar aresta!" << endl;
            cout << e.what() << endl;
        }
    }
};

#endif // GRAFOS_MENU_H
