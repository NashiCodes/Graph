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
#include <vector>

struct caminhao {
public:
    int capacidade;

    explicit caminhao(int capacidade) { this->capacidade = capacidade; }

    virtual ~caminhao() = default;
};

class AGrafo {
public:
    int getOrdem() const { return Ordem; }

    bool getPart() const {
        return
                this->part1;
    }

    void criaNo(int idNo, int pesoNo);

    bool isVerticePonderado() const { return VerticePonderado; }

    void inserirNo(No *no);

    void inserirNo(int idNo, int pesoNo);

    ofstream *getOutput() const { return Output; }

    bool isPonderado() const { return ArestaPonderada; }

    bool isDirecionado() const { return EhDirecionado; }

    void criarAresta(int idNoOrigem, int idNoDestino, int pesoAresta);

    const map<int, No *> *getNos() const { return NOS; }

    int getNumArestas() const { return NumArestas; }

    ifstream *getInput() const { return Input; }

    vector<caminhao *> *getCaminhoes() const { return caminhoes; }

    void setOutput(ofstream *output) {
        if (this->Output == nullptr) this->Output = output;
        else return;
    }

protected:
    int Ordem;
    int NumArestas;
    bool ArestaPonderada;
    bool VerticePonderado;
    bool EhDirecionado;
    bool part1;
    ifstream *Input;
    ofstream *Output;
    map<int, No *> *NOS;
    map<int, Aresta *> *ARESTAS;
    vector<caminhao *> *caminhoes;
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
        this->caminhoes = new vector<caminhao *>();
        this->part1 = true;
    };

    ~AGrafo() {
        for (auto &no: *NOS) { delete no.second; }
        for (auto &aresta: *ARESTAS) { delete aresta.second; }
        delete NOS;
        delete ARESTAS;
        delete idsLiberados;
    };

    void setPart(bool part) { this->part1 = part; }

    void montaGrafo();

    void instanciasParte1();

    bool existeNo(int idNo) const { return this->NOS->find(idNo) != this->NOS->end(); }

    void setPonderado(bool ehPonderado) { ArestaPonderada = ehPonderado; }

    void setDirecionado(bool ehDirecionado) { EhDirecionado = ehDirecionado; }


    void setOrdem(int ordem);

    void setNumArestas(int numArestas);

    void setVerticePonderado(bool ehPonderado) { VerticePonderado = ehPonderado; }

    map<int, Aresta *> *getArestas() const { return ARESTAS; }

    void removerNo(int idNo);

    void removerAresta(int idNoOrigem, int idNoDestino);

    void instanciasParte2();

    void lePropriedades(int &nmDimensao, int &nmCapacidade) const;

    void leDemandas() const;

    void montarArestas(No *no);
};


#endif //AGRAFOS_H
