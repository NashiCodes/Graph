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

    Aresta(No *noDestino, int id, int peso);

    virtual ~Aresta();

     int getPeso() const;

     void setPeso(int valor);

     int getID() const;

     void setID(int valor);

    int getIdNoDestino() const;

    No *getNoDestino();

     void setNoDestino(No *valor);

private:
    int ID;
    int PESO;
    int ID_NO_DESTINO;
    No *noDestino;
};


#endif //ARESTA_H
