#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>
#include <vector>
#include "src/Grafo.h"
#include "src/Menu.h"

using namespace std;

void criaGrafoListaAdj(Grafo *grafo, ifstream &entrada);


int main(int argc, const char *argv[]) {
    auto *g = new Grafo();

    //urls dos arquivos de entrada e saida para teste
    string in = "instancias_nao_ponderados/grafo_1000_1.txt";
    string out = "saida.txt";


    // Criando arquivos de entrada e saida
    ifstream entrada;
    ofstream saida;
    try {
        entrada.open(in, ios::in);
        saida.open(out, ios::out | ios::trunc);
    } catch (exception &e) {
        cout << e.what() << endl;
        return 0;
    }
//    entrada.open(argv[1], ios::in);
//    saida.open(argv[2], ios::out | ios::trunc);

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
//    criaGrafoListaAdj(g, entrada);

    // Print de arestas (apenas para testes)
    // g->printArestas();

    (new Menu(g, &entrada, &saida))->menuPrincipal();

    return 0;
}