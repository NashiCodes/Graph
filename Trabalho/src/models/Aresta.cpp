#include "Aresta.h"

Aresta::Aresta(No *noDestino) {
    this->noDestino = noDestino;
    this->PESO = 0;
}

Aresta::Aresta(No *noDestino, int peso) {
    this->noDestino = noDestino;
    this->PESO = peso;
}

Aresta::~Aresta() {
    delete this;
}

int Aresta::getPeso() const {
    return this->PESO;
}

void Aresta::setPeso(int valor) {
    this->PESO = valor;
}

No *Aresta::getNoDestino() {
    return this->noDestino;
}

void Aresta::setNoDestino(No *valor) {
    this->noDestino = valor;
}