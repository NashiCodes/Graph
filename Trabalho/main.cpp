#include <iostream>
#include <fstream>
#include <unistd.h>
#include <climits>
#include <vector>
#include <string>
#include "src/models/Grafo.h"
#include "src/Menu.h"

using namespace std;

string *get_current_dir_name();

void AbreInput(ifstream &entrada, const string &diretorio, const string &nomeArquivo);

void AbreOutput(ofstream &saida, const string &nomeArquivo);

bool ehCmakeDir(const string *path);


int main(int argc, const char *argv[]) {
    // Obtendo a informacao se o grafo eh direcionado ou nao
    bool ehDirecionado = false;
    cout << "Seu grafo eh direcionado? (1) Direcionado ou (0) Nao Direcionado: ";
//    cin >> ehDirecionado;
    cout << "Eh direcionado: " << ehDirecionado;
    cout << '\n' << endl;

    // Obtendo a informacao se o grafo eh ponderado ou nao
    bool ehPonderado = true;
    cout << "Seu grafo eh Ponderado? (1) Ponderado ou (0) Nao Ponderado: ";
//    cin >> ehPonderado;
    cout << "Eh ponderado: " << ehPonderado;
    cout << '\n' << endl;

    //urls dos arquivos de entrada e saida para teste
    string diretorio = "instancias_nao_ponderadas";
    string nomeArquivo = "grafo_1000_1.txt";
    string out = "saida.txt";
//
//    if (ehPonderado) {
    diretorio = "instancias_ponderadas";
    nomeArquivo = "test.txt";
    out = "saida_ponderada.txt";
//    }
//    string test = argv[1];

    // Criando arquivos de entrada e saida
    ifstream entrada;
    ofstream saida;

    AbreInput(entrada, diretorio, nomeArquivo);
    AbreOutput(saida, out);

    if (!entrada.is_open() || !saida.is_open()) {
        cout << "Erro ao abrir os arquivos!" << endl;
        return 0;
    }

    cout << "arquivos aberto" << endl;
//    entrada.open(argv[1], ios::in);
//    saida.open(argv[2], ios::out | ios::trunc);

    auto *g = new Grafo(ehPonderado, false, ehDirecionado, &entrada, &saida);


    // Criando grafo a partir de uma lista de adjacencia
    cout << "Aguarde enquanto o grafo esta sendo criado..." << endl;
//    criaGrafoListaAdj(g, entrada);

    // Print de arestas (apenas para testes)
    // g->printArestas();

    (new Menu(g))->menuPrincipal();

    return 0;
}

string *get_current_dir_name() {
    char buffer[PATH_MAX];
    getcwd(buffer, PATH_MAX);
    return new string(buffer);
}

void AbreInput(ifstream &entrada, const string &diretorio, const string &nomeArquivo) {
    auto path = get_current_dir_name();

    if (ehCmakeDir(path)) {
        path->erase(path->find("cmake-build-debug"), path->length());
    }

    path->append("/").append(diretorio).append("/").append(nomeArquivo);
    entrada.open(*path, ios::in);
}

void AbreOutput(ofstream &saida, const string &nomeArquivo) {
    auto path = get_current_dir_name();

    if (ehCmakeDir(path)) {
        path->erase(path->find("cmake-build-debug"), path->length());
    }

    path->append("/").append(nomeArquivo);
    saida.open(*path, ios::out | ios::trunc);
}

bool ehCmakeDir(const string *path) {
    return path->find("cmake-build-debug") != string::npos ||
           path->find("cmake-build-release") != string::npos;
}