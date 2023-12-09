#include <iostream>
#include <fstream>
#include <unistd.h>
#include <climits>
#include <vector>
#include <string>
#include "src/models/Grafo.h"
#include "src/Menu.h"

using namespace std;

string input;
string out;
bool ehDirecionado;
bool ehPonderado;
bool ehVerticePonderado;
bool ehParte1;
string diretorio;
ifstream entrada;
ofstream saida;

string *getCurrentDirName();

void abreInput();

void abreOutput();

bool ehCmakeDir(const string *path);

void parte1(const char *argv[]);

void parte2(const char *argv[]);

int main(int argc, const char *argv[]) {

    //A estrutura de Arquivos do Grafo foi alterada
    //Agora temos 3 arquivos .cpp que conversam entre si

    // Grafos.cpp que contem todos os metodos principais de chamada unitaria
    //Como o Prim, Kruskal, Dijkstra, Floyd, etc

    //AuxFuncs.cpp que contem todos os metodos auxiliares principais
    // Como auxFTD, auxFTI, auxDijkstra, auxFloyd, etc

    //Basics.cpp que contem todos os metodos auxiliares basicos
    // Como minDistance, Incidentes, Ordena, etc

    //Tambem foi criado um arquivo Output.cpp que contem todos os metodos de saida e salvamento
    // Como printListaAdjacencia, imprimeDijkstra, imprimeFloyd, etc

    //Dentro de AGrafo.h temos um struct que contem a classe Caminhao
    //Pode ser feita a alteracao de metodos auxiliares para que o caminhao seja utilizado
    //Porem tomar cuidado para nao poluir dms o codigo

    //Metodos que nao estao sendo utilizados podem ser removidos

    //TODO: Refatorar metodos para nao fazer impressao no console
    // Se caso estiver rodando a parte 2 do trabalho, nao imprimir nada no console
    // Apenas salvar os resultados no arquivo de saida

    //TODO: Refatorar metodos desnecessarios

    //TODO: Refatorar metodos para nao fazerem chamadas de metodos desnecessarios

    //TODO: Implementar o algoritmo guloso e guloso randomizado para busca de rotas

    cout << "Trabalho de Grafos" << endl;
    cout << "Alunos: João Victor Pereira dos Anjos" << endl;
    cout << "Marcelo Rother" << endl;
    cout << "Igor Mattos" << endl;
    cout << "Alvaro Davi" << endl;

    cout << '\n' << endl;

    cout << "Argumentos Necesarios: " << endl;
    cout << "Parte 1: " << endl;
    cout << "1 - Nome do arquivo de entrada" << endl;
    cout << "2 - Nome do arquivo de saida" << endl;
    cout << "3 - true ou false para  Grafo Direcionado" << endl;
    cout << "4 - true ou false para  Grafo Ponderado nas arestas" << endl;
    cout << "5 - true ou false para  Grafo Ponderado nos vertices" << endl;

    cout << "Parte 2: " << endl;
    cout << "1 - Nome do arquivo de saida" << endl;

    cout << '\n' << endl;

    //Tem que passar os parametros corretos
    if (argc == 2) {
        //Não é necessario passar o nome do arquivo de entrada, apenas o de saida
        parte2(argv);
        return 0;
    } else if (argc == 6)
        parte1(argv);
    else {
        cout << "Argumentos invalidos" << endl;
        return 0;
    }


    cout << "Aguarde enquanto o grafo esta sendo criado..." << endl;

    auto *g = new Grafo(ehParte1, ehVerticePonderado, ehPonderado, ehDirecionado, &entrada);
    g->setOutput(&saida);

    if (ehParte1) {
        auto menu = new Menu(g);
        menu->menuPrincipal();
        delete menu;
    }

    entrada.close();
    saida.close();

    delete g;

    return 0;
}

void abreAquivos() {
    abreInput();
    abreOutput();

    if (!entrada.is_open() || !saida.is_open()) {
        cout << "Erro ao abrir os arquivos!" << endl;
        exit(1);
    }
    cout << "arquivos aberto" << endl;
}

void parte1(const char *argv[]) {
    input = argv[1];
    out = argv[2];
    ehDirecionado = argv[3][0] == 't';
    ehPonderado = argv[4][0] == 't';
    ehVerticePonderado = argv[5][0] == 't';
    diretorio = ehPonderado ? "instancias_ponderadas" : "instancias_nao_ponderadas";
    ehParte1 = true;
    abreAquivos();
}

void parte2(const char *argv[]) {
    input = "A-n34-k5.txt";
    out = argv[1];
    ehDirecionado = false;
    ehPonderado = true;
    ehVerticePonderado = true;
    diretorio = "Parte2";
    ehParte1 = false;
    abreAquivos();
    auto *g = new Grafo(ehParte1, ehVerticePonderado, ehPonderado, ehDirecionado, &entrada);
    g->setOutput(&saida);

    g->algoritmoGuloso();
    //Fazer Aqui a chamada dos algoritmos e guloso randomizado
    //O metodo principal a ser chamado deve estar no arquivo Grafo.cpp
    //Metodos auxiliares devem estar no arquivo AuxFuncs.cpp
    //Metodos basicos devem estar no arquivo Basics.cpp
    //Metodos de saida devem estar no arquivo Output.cpp
}

string *getCurrentDirName() {
    char buffer[PATH_MAX];
    getcwd(buffer, PATH_MAX);
    return new string(buffer);
}

void abreInput() {
    auto path = getCurrentDirName();

    if (ehCmakeDir(path)) {
        path->erase(path->find("cmake-build-debug"), path->length());
    }

    path->append("/").append(diretorio).append("/").append(input);
    entrada.open(*path, ios::in);
}

void abreOutput() {
    auto path = getCurrentDirName();

    if (ehCmakeDir(path)) {
        path->erase(path->find("cmake-build-debug"), path->length());
    }

    path->append("/output").append(out);
    saida.open(*path, ios::out | ios::trunc);
}

bool ehCmakeDir(const string *path) {
    return path->find("cmake-build-debug") != string::npos ||
           path->find("cmake-build-release") != string::npos;
}