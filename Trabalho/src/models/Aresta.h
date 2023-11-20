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

    Aresta(No *Origem, No *Destino, int id, int peso);

    virtual ~Aresta();

     int getPeso() const;

     void setPeso(int valor);

     int getID() const;

     void setID(int valor);

    int getIdDestino() const;

    int getIdOrigem() const;

    No *getDestino();

    No *getOrigem();

    void setDestino(No *valor);

private:
    int ID;
    int PESO;
    No *Origem;
    No *Destino;

    void setOrigem(No *valor);
};


#endif //ARESTA_H
