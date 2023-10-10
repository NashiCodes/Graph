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
    explicit No(int idNo);
    virtual ~No();

    [[nodiscard]] int getID() const;

    [[nodiscard]] int getGrauEntrada() const;
    void setGrauEntrada(int valor);

    [[nodiscard]] int getGrauSaida() const;
    void setGrauSaida(int valor);

    void printarNo(bool ponderado, bool direcionado);

    void setAresta(int idNoDestino, Aresta *aresta);

    [[maybe_unused]] Aresta *getAresta(int idNoDestino);

    map<int, Aresta*> getArestas();

private:
    int ID;
    int GRAU_ENTRADA;
    int GRAU_SAIDA;
    map<int, Aresta*> ARESTAS;

};

#endif //NO_H
