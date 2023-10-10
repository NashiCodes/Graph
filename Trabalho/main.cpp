#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include "src/models/Grafo.h"
#include "src/Menu.h"

using namespace std;
namespace fs = std::filesystem;


void AbreInput(ifstream &entrada, const string &diretorio, const string &nomeArquivo);

void AbreOutput(ofstream &saida, const string &nomeArquivo);

bool ehCmakeDir(const fs::path &path);


int main(int argc, const char *argv[]) {

    // Obtendo a informacao se o grafo eh direcionado ou nao
    bool ehDirecionado;
    cout << "Seu grafo eh direcionado? (1) Direcionado ou (0) Nao Direcionado: ";
    cin >> ehDirecionado;
    cout << "Eh direcionado: " << ehDirecionado;
    cout << '\n' << endl;

    // Obtendo a informacao se o grafo eh ponderado ou nao
    bool ehPonderado;
    cout << "Seu grafo eh Ponderado? (1) Ponderado ou (0) Nao Ponderado: ";
    cin >> ehPonderado;
    cout << "Eh ponderado: " << ehPonderado;
    cout << '\n' << endl;

    //urls dos arquivos de entrada e saida para teste
    string diretorio = "instancias_nao_ponderadas";
    string nomeArquivo = "grafo_1000_1.txt";
    string out = "saida.txt";

    if (ehPonderado) {
        diretorio = "instancias_ponderadas";
        nomeArquivo = "grafo_125.txt";
        out = "saida_ponderada.txt";
    }
//    string test = argv[1];

    // Criando arquivos de entrada e saida
    ifstream entrada;
    ofstream saida;

    AbreInput(entrada, diretorio, nomeArquivo);
    AbreOutput(saida, out);

    if (!entrada.is_open()) {
        cout << "Erro ao abrir os arquivos!" << endl;
        return 0;
    }
//    entrada.open(argv[1], ios::in);
//    saida.open(argv[2], ios::out | ios::trunc);

    auto *g = new Grafo(ehPonderado, ehDirecionado, &entrada, &saida);


    // Criando grafo a partir de uma lista de adjacencia
    cout << "Aguarde enquanto o grafo esta sendo criado..." << endl;
//    criaGrafoListaAdj(g, entrada);

    // Print de arestas (apenas para testes)
    // g->printArestas();

    (new Menu(g))->menuPrincipal();

    return 0;
}

void AbreInput(ifstream &entrada, const string &diretorio, const string &nomeArquivo) {
    auto path = fs::current_path();

    if (ehCmakeDir(path)) {
        path /= "../";
    }

    path /= diretorio;
    path /= nomeArquivo;
    entrada.open(path, ios::in);
}

void AbreOutput(ofstream &saida, const string &nomeArquivo) {
    auto path = fs::current_path();

    if (ehCmakeDir(path)) {
        path /= "../";
    }

    path /= nomeArquivo;
    saida.open(path, ios::out | ios::trunc);
}

bool ehCmakeDir(const fs::path &path) {
    return path.filename() == "cmake-build-debug" || path.filename() == "cmake-build-release";
}