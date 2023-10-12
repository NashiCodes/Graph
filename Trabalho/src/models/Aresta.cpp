#include "Aresta.h"
#include "No.h"


Aresta::Aresta( No *noDestino, int id, int peso) {
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

int Aresta::getIdNoDestino() const {
    return ID_NO_DESTINO;
}
