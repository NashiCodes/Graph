#include "Aresta.h"
#include "No.h"


Aresta::Aresta(No *Origem, No *Destino, int id, int peso) {
    this->Origem = Origem;
    this->Destino = Destino;
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

No *Aresta::getOrigem() {
    return this->Origem;
}

No *Aresta::getDestino() {
    return this->Destino;
}

int Aresta::getIdOrigem() const {
    return this->Origem->getID();
}

int Aresta::getIdDestino() const {
    return this->Destino->getID();
}

void Aresta::setOrigem(No *valor) {
    this->Origem = valor;
}

 void Aresta::setDestino(No *valor) {
    this->Destino = valor;
}

int Aresta::getID() const {
    return this->ID;
}

 void Aresta::setID(int valor) {
    this->ID = valor;
}


