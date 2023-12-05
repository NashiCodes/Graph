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
    bool ArestaPonderada;
    bool VerticePonderado;
    bool EhDirecionado;
    ifstream *Input;
    ofstream *Output;
    map<int, No *> *NOS;
    map<int, Aresta *> *ARESTAS;
    set<int> *idsLiberados;

    AGrafo() {
        this->ArestaPonderada = false;
        this->VerticePonderado = false;
        this->EhDirecionado = false;
        this->Input = nullptr;
        this->Output = nullptr;
        this->NOS = new map<int, No *>();
        this->ARESTAS = new map<int, Aresta *>();
        this->idsLiberados = new set<int>();
        this->NumArestas = 0;
        this->Ordem = 0;
    };

    ~AGrafo() {
        for (auto &no: *NOS) {
            delete no.second;
        }
        for (auto &aresta: *ARESTAS) {
            delete aresta.second;
        }
        delete NOS;
        delete ARESTAS;
        delete idsLiberados;
    };

public:

    void montaGrafo();

    void lerInstancias(bool ponderado, bool direcionado, bool verticePonderado);

    ifstream *getInput() const;

    bool existeNo(int idNo);

    int getOrdem() const;

    void setOrdem(int ordem);

    int getNumArestas() const;

    void setNumArestas(int numArestas);

    bool isPonderado() const;

    void setPonderado(bool ehPonderado);

    void setVerticePonderado(bool ehPonderado);

    bool isVerticePonderado() const;

    bool isDirecionado() const;

    void setDirecionado(bool ehDirecionado);

    ofstream *getOutput() const;

    void setOutput(ofstream *output);

    const map<int, No *> *getNos() const;

    const map<int, Aresta *> *getArestas() const;

    void CriaNo(int idNo, int pesoNo);

    void InserirNo(int idNo, int pesoNo);

    void RemoverNo(int idNo);

    void CriarAresta(int idNoOrigem, int idNoDestino, int pesoAresta);

    void RemoverAresta(int idNoOrigem, int idNoDestino);

    void imprimeGraus(int idNo);

};


#endif //AGRAFOS_H
