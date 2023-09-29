#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>
#include <vector>
#include "Grafo.h"

using namespace std;

void menu(Grafo *grafo, ofstream &saida);

void criaGrafoListaAdj(Grafo *grafo, ifstream &entrada);


int main(int argc, const char *argv[]) {
    auto *g = new Grafo();

    // Criando arquivos de entrada e saida
    ifstream entrada;
    ofstream saida;
    entrada.open(argv[1], ios::in);
    saida.open(argv[2], ios::out | ios::trunc);

    // Obtendo a informacao se o grafo eh direcionado ou nao
    bool ehDirecionado;
    cout << "Seu grafo eh direcionado? (1) Direcionado ou (0) Nao Direcionado: ";
    cin >> ehDirecionado;
    cout << "Eh direcionado: " << ehDirecionado;
    cout << '\n' << endl;
    g->setDirecionado(ehDirecionado);

    // Obtendo a informacao se o grafo eh ponderado ou nao
    bool ehPonderado;
    cout << "Seu grafo eh Ponderado? (1) Ponderado ou (0) Nao Ponderado: ";
    cin >> ehPonderado;
    cout << "Eh ponderado: " << ehPonderado;
    cout << '\n' << endl;
    g->setPonderado(ehPonderado);


    // Criando grafo a partir de uma lista de adjacencia
    cout << "Aguarde enquanto o grafo esta sendo criado..." << endl;
    criaGrafoListaAdj(g, entrada);

    // Print de arestas (apenas para testes)
    // g->printArestas();

    menu(g, saida);


    return 0;
}

void menu(Grafo *grafo, ofstream &saida) {


}