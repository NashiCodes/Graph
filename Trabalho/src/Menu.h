#ifndef GRAFOS_MENU_H
#define GRAFOS_MENU_H

#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include "Grafo.h"

class Menu {
private:
    Grafo *grafo;
    ifstream *entrada;
    ofstream *arquivoSaida;
    string linha;

public:
    Menu(Grafo *grafo, ifstream *entrada, ofstream *arquivoSaida) :
            grafo(grafo), entrada(entrada), arquivoSaida(arquivoSaida) {

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
        cout << "cheguei no menu principal" << endl;
    }

    void lerArquivo() {
        try {
            while (!entrada->eof()) {
                getline(*entrada, linha);
                if (linha.empty()) {
                    break;
                }

                auto id = linha.substr(0, linha.find(' '));
                linha.erase(0, linha.find(' ') + 1);
                auto idDestino = linha.substr(0, linha.find(' '));

                grafo->inserirNo(stoi(id));
                grafo->inserirNo(stoi(idDestino));

                if (grafo->isPonderado()) {
                    linha.erase(0, linha.find(' ') + 1);
                    auto peso = linha.substr(0, linha.find(' '));
                    grafo->criarAresta(stoi(id), stoi(idDestino), stoi(peso));
                } else {
                    grafo->criarAresta(stoi(id), stoi(idDestino));
                }

            }
        } catch (exception &e) {
            cout << "Erro ao ler o arquivo!" << endl;
            cout << e.what() << endl;
        }
    }
};

#endif // GRAFOS_MENU_H
