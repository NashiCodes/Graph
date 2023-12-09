#include "No.h"

using namespace std;

No::No(int name) {
    this->nome = name;
    this->peso = 0;
    this->grauEntrada = 0;
    this->grauSaida = 0;
    this->particao = 0;
    this->proxNo = NULL;
    this->primeiraAresta = NULL;
    this->ultimaAresta = NULL;
    this->searchInfo = NULL;
    this->group = 0;
}

No::No(int name, int peso) {
    this->nome = name;
    this->peso = peso;
    this->grauEntrada = 0;
    this->grauSaida = 0;
    this->particao = 0;
    this->proxNo = NULL;
    this->primeiraAresta = NULL;
    this->ultimaAresta = NULL;
    this->searchInfo = NULL;
    this->group = 0;
}

No::~No() {
    Aresta* auxEdge = getPrimeiraAresta();
    while ( auxEdge != NULL ) {
        Aresta* auxNextEdge = auxEdge->getProxAresta();
        delete( auxEdge );
        auxEdge = auxNextEdge;       
    }
    delete( searchInfo );
}

void No::setNome(int valor) {
    this->nome = valor;
}
int No::getNome() {
    return this->nome;
}

void No::setGroup(int group) {
    this->group = group;
}

int No::getGroup() {
    return this->group;
}

void No::setPeso(int valor) {
    this->peso = valor;
}
int No::getPeso() {
    return this->peso;
}

int No::getGrau() {
    return this->grauSaida;
}
void No::setIncrementaGrau() {
    this->grauEntrada++;
    this->grauSaida++;
}
void No::setDecrementarGrau() {
    this->grauEntrada--;
    this->grauSaida--;
}

int No::getGrauEntrada() {
    return this->grauEntrada;
}
void No::setIncrementaGrauEntrada() {
    this->grauEntrada++;
}
void No::setDecrementaGrauEntrada() {
    this->grauEntrada--;
}

int No::getGrauSaida() {
    return this->grauSaida;
}
void No::setIncrementaGrauSaida() {
    this->grauSaida++;
}
void No::setDecrementaGrauSaida() {
    this->grauSaida--;
}

void No::setProxNo(No *valor) {
    this->proxNo = valor;
}
No* No::getProxNo(){
    return this->proxNo;
}

void No::setPrimeiraAresta(Aresta *valor) {
    this->primeiraAresta = valor;
}
Aresta* No::getPrimeiraAresta(){
    return this->primeiraAresta;
}

void No::setUltimaAresta(Aresta *valor) {
    this->ultimaAresta = valor;
}
Aresta* No::getUltimaAresta() {
    return this->ultimaAresta;
}

/**
 * Define um objeto searchInfo.
 * @param valor (new si)
 */
void No::setSearchInfo(SearchInfo *si) {
    this->searchInfo = si;
}
SearchInfo *No::getSearchInfo() {
    return this->searchInfo;
}