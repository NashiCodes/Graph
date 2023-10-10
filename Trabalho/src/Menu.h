#ifndef GRAFOS_MENU_H
#define GRAFOS_MENU_H

#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include "models/Grafo.h"
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
        grafo->imprimeGraus(1);
    }

    [[maybe_unused]] void printarGrafo() {
        grafo->PrintListaAdjacencia();
    }

    [[maybe_unused]] void inserirNo() {
        cout << "Digite o ID do nó: ";
        int idNo;
        cin >> idNo;
        try {
            grafo->InserirNo(idNo);
        } catch (exception &e) {
            cout << "Erro ao inserir nó!" << endl;
            cout << e.what() << endl;
        }
    }

    [[maybe_unused]] void criarAresta() {
        cout << "Digite o ID do nó de origem: ";
        int idNoOrigem;
        cin >> idNoOrigem;
        cout << "Digite o ID do nó de destino: ";
        int idNoDestino;
        cin >> idNoDestino;
        try {
            grafo->CriarAresta(idNoOrigem, idNoDestino);
        } catch (exception &e) {
            cout << "Erro ao criar aresta!" << endl;
            cout << e.what() << endl;
        }
    }
};

#endif // GRAFOS_MENU_H
