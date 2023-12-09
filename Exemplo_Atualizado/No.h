#ifndef NO_H
#define NO_H
#include <iostream>
#include <cstdlib>
#include <string>
#include "Aresta.h"

using namespace std;
class Aresta;

class No {
public:
    No(int idNo);
    No(int idNo, int weight);
    virtual ~No();

    int getIdNo () {return idNo;}

private:
    int idNo;
    int pesoNo;
    int grauEntrada;
    int grauSaida;
    No *proxNo;
    Aresta *primeiraAresta;
    Aresta *ultimaAresta;
};

#endif // NO_H
