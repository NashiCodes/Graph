#ifndef AGRAFOS_H
#define AGRAFOS_H

#include "No.cpp"
#include "Aresta.cpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <set>


class AGrafo {
protected:
    int Ordem;
    int NumArestas;
    bool EhPonderado{};
    bool EhDirecionado{};
    ifstream *Input{};
    ofstream *Output{};
    map<int, No *> *NOS;
    map<int, Aresta *> *ARESTAS;

    AGrafo() {
        this->EhPonderado = false;
        this->EhDirecionado = false;
        this->Input = nullptr;
        this->Output = nullptr;
        this->NOS = new map<int, No *>();
        this->ARESTAS = new map<int, Aresta *>();
        this->NumArestas = 0;
        this->Ordem = 0;
    };

    ~AGrafo() {
        delete NOS;
        delete ARESTAS;
    };

public:

    void montaGrafo();

    ifstream *getInput() const;

    bool existeNo(int idNo);

    [[nodiscard]] int getOrdem() const;

    void setOrdem(int ordem);

    [[nodiscard]] int getNumArestas() const;

    void setNumArestas(int numArestas);

    [[nodiscard]] bool isPonderado() const;

    void setPonderado(bool ehPonderado);

    [[nodiscard]] bool isDirecionado() const;

    void setDirecionado(bool ehDirecionado);

    [[nodiscard]] ofstream *getOutput() const;

    void setOutput(ofstream *output);

    [[nodiscard]] const map<int, No *> *getNos() const;

    [[nodiscard]] const map<int, Aresta *> *getArestas() const;

    void CriaNo(int idNo);

    void InserirNo(int idNo);

    void CriarAresta(int idNoOrigem, int idNoDestino, int pesoAresta);

    void CriarAresta(int idNoOrigem, int idNoDestino);

    void imprimeGraus(int idNo);


};


#endif //AGRAFOS_H
