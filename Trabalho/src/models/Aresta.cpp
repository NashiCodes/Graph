#include "Aresta.h"

Aresta::Aresta(No *noOrigem, No *noDestino, int id) {
    this->noOrigem = noOrigem;
    this->noDestino = noDestino;
    this->ID = id;
    this->PESO = 1;
}

Aresta::Aresta(No *noOrigem, No *noDestino, int id, int peso) {
    this->noOrigem = noOrigem;
    this->noDestino = noDestino;
    this->ID = id;
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

int Aresta::getID() const {
    return this->ID;
}

void Aresta::setID(int valor) {
    this->ID = valor;
}

No *Aresta::getNoOrigem() {
    return nullptr;
}
