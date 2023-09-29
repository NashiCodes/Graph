#ifndef NO_H
#define NO_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include "Aresta.h"

using namespace std;

class Aresta;

class No {
public:
    explicit No(int idNo);
    No(int idNo, int peso);
    virtual ~No();

    int getID() const;
    void setID(int valor);

    int getPeso() const;
    void setPeso(int valor);

    int getGrauEntrada() const;
    void setGrauEntrada(int valor);

    int getGrauSaida() const;
    void setGrauSaida(int valor);

    void setAresta(int idNoDestino, Aresta *aresta);
    Aresta *getAresta(int idNoDestino);

    unordered_map<int, Aresta *> getArestas();

private:
    int _ID;
    int _PESO;
    int _GRAU_ENTRADA;
    int _GRAU_SAIDA;
    unordered_map<int, Aresta *> ARESTAS;
};

#endif //NO_H
