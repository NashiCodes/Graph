#ifndef NO_H
#define NO_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <set>
#include "Aresta.h"

using namespace std;

class Aresta;

class No {
public:
    No(int idNo, int peso);
    virtual ~No();

    int getID() const;

    int getPeso() const;
    void setPeso(int valor);

    int getGrauEntrada() const;
    void setGrauEntrada(int valor);

    int getGrauSaida() const;
    void setGrauSaida(int valor);

    void printarNo(bool ponderado, bool direcionado);

    void setAresta(int idNoDestino, Aresta *aresta);

    Aresta *getAresta(int idNoDestino);

    map<int, Aresta*> getArestas();

    void RemoveAresta(int idNoDestino, bool direcionado);

private:
    int ID;
    int PESO;
    int GRAU_ENTRADA;
    int GRAU_SAIDA;
    map<int, Aresta*> ARESTAS;

};

#endif //NO_H
