#ifndef ARESTA_H
#define ARESTA_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "No.h"

using namespace std;

class No;

class Aresta {
public:
    Aresta(No *noOrigem, No *noDestino, int id);

    Aresta(No *noOrigem, No *noDestino, int id, int peso);

    virtual ~Aresta();

    int getPeso() const;

    void setPeso(int valor);

    int getID() const;

    void setID(int valor);

    No *getNoOrigem();

    void setNoOrigem(No *valor);

    No *getNoDestino();

    void setNoDestino(No *valor);

private:
    int PESO;
    int ID;
    No *noOrigem;
    No *noDestino;
};


#endif //ARESTA_H
