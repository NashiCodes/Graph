#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "No.h"

using namespace std;

class No;

class Aresta {
public:
    Aresta(No *noDestino, Aresta *proxAresta);
    Aresta(No *noDestino, Aresta *proxAresta, int peso);
    virtual ~Aresta();

    int getPeso();
    void setPeso(int valor);
    
    No *getNoDestino();
    void setNoDestino(No *valor);
    
    Aresta *getProxAresta();
    void setProxAresta(Aresta *valor);
    
private:
    int peso;
    No *noDestino;
    Aresta *proxAresta;
    bool visitado;
};

#endif // ARESTA_H
