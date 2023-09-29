#include <iostream>
#include <stdlib.h>
#include <string>
#include "Aresta.h"

using namespace std;

/**
 * Construtor. Os valores padrões são:\n
 * 
 * peso = 1;
 * 
 * @param *noDestino (new valor)
 * @param *proxAresta (new valor)
 */
Aresta::Aresta(No *noDestino, Aresta *proxAresta) {
    this->peso = 1;
    this->noDestino = noDestino;
    this->proxAresta = proxAresta;
}

/**
 * Construtor sobrescrito.
 * 
 * @param *noDestino (new valor)
 * @param *proxAresta (new valor)
 * @param peso (new valor)
 */
Aresta::Aresta(No *noDestino, Aresta *proxAresta, int peso) {
    this->peso = peso;
    this->noDestino = noDestino;
    this->proxAresta = proxAresta;
}

/** Destructor */
Aresta::~Aresta() {
    //dtor
}

/**
 * A funcao define peso valor.
 * 
 * @param valor (new valor)
 */
void Aresta::setPeso(int valor) {
    this->peso = valor;
}

/**
 * A funcao retorna peso valor.
 */
int Aresta::getPeso() {
    return this->peso;
}

/**
 * A funcao define noDestino.
 * 
 * @param valor (new valor)
 */
void Aresta::setNoDestino(No *valor) {
    this->noDestino = valor;
}

/**
 * A funcao retorna noDestino.
 */
No* Aresta::getNoDestino() {
    return this->noDestino;
}

/**
 * A funcao define proxAresta.
 * 
 * @param valor (new valor)
 */
void Aresta::setProxAresta(Aresta *valor) {
    this->proxAresta = valor;
}

/**
 * A funcao retorna proxAresta;
 */
Aresta* Aresta::getProxAresta() {
    return this->proxAresta;
}
