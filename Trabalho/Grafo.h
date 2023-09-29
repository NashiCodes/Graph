#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include "src/models/No.h"
#include "src/models/Aresta.h"
#include "src/models/AGrafo.h"

using namespace std;

class Grafo : public AGrafo {
public:
    Grafo() : AGrafo() {};
    explicit Grafo(int ordem) : AGrafo(ordem) {};
    Grafo(int ordem, bool ehPonderado, bool ehDirecionado) : AGrafo(ordem, ehPonderado, ehDirecionado) {};

    void createNo(int idNo);

};


#endif //GRAFO_H
