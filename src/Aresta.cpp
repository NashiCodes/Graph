#include "Aresta.h"

Aresta::Aresta(No *noDestino) {
    this->noDestino = noDestino;
    this->_PESO = 0;
}

Aresta::Aresta(No *noDestino, int peso) {
    this->noDestino = noDestino;
    this->_PESO = peso;
}

Aresta::~Aresta() {
    delete this;
}

int Aresta::getPeso() {
    return this->_PESO;
}

void Aresta::setPeso(int valor) {
    this->_PESO = valor;
}

No *Aresta::getNoDestino() {
    return this->noDestino;
}

void Aresta::setNoDestino(No *valor) {
    this->noDestino = valor;
}