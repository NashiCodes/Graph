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
    Aresta(int noDestino);
    Aresta(int noDestino, int pesoAresta);

    int getPesoAresta();

    
    //Aresta *getProxAresta();
    //void setProxAresta(Aresta *valor);
    
private:
    int pesoAresta;
    int idNoDestino;
    Aresta *proxAresta;
};

#endif // ARESTA_H
