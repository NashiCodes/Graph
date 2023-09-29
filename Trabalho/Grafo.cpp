//
// Created by Nashi on 29/09/2023.
//

#include "Grafo.h"

void Grafo::createNo(int idNo) {
    No *no = new No(idNo);
    this->NOS[idNo] = no;
}
