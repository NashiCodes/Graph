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

    [[nodiscard]] int getPeso() const;

    [[maybe_unused]] void setPeso(int valor);

    [[nodiscard]] int getID() const;

    [[maybe_unused]] void setID(int valor);

    No *getNoOrigem();

    [[maybe_unused]] void setNoOrigem(No *valor);

    No *getNoDestino();

    [[maybe_unused]] void setNoDestino(No *valor);

private:
    int PESO;
    int ID;
    No *noOrigem;
    No *noDestino;
};


#endif //ARESTA_H
