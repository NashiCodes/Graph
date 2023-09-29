#ifndef ARESTA_H
#define ARESTA_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "No.h"

class No;

class Aresta {
public:
    explicit Aresta(No *noDestino);
    Aresta(No *noDestino, int peso);
    virtual ~Aresta();

    int getPeso();
    void setPeso(int valor);

    No *getNoDestino();
    void setNoDestino(No *valor);
private:
    int _PESO;
    No *noDestino;
};


#endif //ARESTA_H
