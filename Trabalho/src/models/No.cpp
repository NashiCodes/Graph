#include "No.h"
#include "Aresta.h"

using namespace std;

/**
 * Construtor da classe No.
 *
 * @param idNo: Identificador do nó
 * @return void
 * @precondition: idNo deve ser um inteiro positivo
 * @postcondition: Um nó é criado com o identificador idNo
 *
 */
No::No(int idNo, int peso) {
    this->ID = idNo;
    this->PESO = peso;
    this->GRAU_ENTRADA = 0;
    this->GRAU_SAIDA = 0;
    this->PASSOU = false;
    this->X = 0;
    this->Y = 0;
}

/**
 * Retorna o identificador do nó.
 *
 * @return int
 */
int No::getID() const {
    return this->ID;
}

int No::getGrauEntrada() const {
    return this->GRAU_ENTRADA;
}

/**
 * Define o grau de entrada do nó.
 *
 * @param valor (new valor)
 */
void No::setGrauEntrada(int valor) {
    this->GRAU_ENTRADA = valor;
}

/**
 * Retorna o grau de saída do nó.
 *
 * @return int
 */
int No::getGrauSaida() const {
    return this->GRAU_SAIDA;
}

/**
 * Define o grau de saída do nó.
 *
 * @param valor (new valor)
 */
void No::setGrauSaida(int valor) {
    if (valor < 0 || valor > (int) this->ARESTAS.size())
        throw invalid_argument("Grau de saída não pode ser negativo");
    else
        this->GRAU_SAIDA = valor;
}

/**
 * Insere uma aresta no nó.
 *
 * @param idNoDestino (new valor)
 * @param aresta (new valor)
 *
 * @return void
 */
void No::setAresta(int idNoDestino, Aresta *aresta) {
    if (idNoDestino < 0)
        throw invalid_argument("ID do nó destino não pode ser negativo");
    else if (aresta == nullptr)
        throw invalid_argument("Aresta não pode ser nula");
    else if (this->ARESTAS.find(idNoDestino) != this->ARESTAS.end())
        throw invalid_argument("Aresta já existe");
    else
        this->ARESTAS.insert(pair<int, Aresta *>(idNoDestino, aresta));
}

/**
 * Retorna o nó destino.
 *
 * @return No
 */
Aresta *No::getAresta(int idNoDestino) {
    if (idNoDestino < 0)
        throw invalid_argument("ID do nó destino não pode ser negativo");
    else if (this->ARESTAS.find(idNoDestino) == this->ARESTAS.end())
        throw invalid_argument("Aresta não existe");
    else
        return this->ARESTAS.at(idNoDestino);
}

/**
 * Retorna todas as arestas do nó.
 *
 * @return map<int, Aresta *>
 */
map<int, Aresta *> No::getArestas() {
    return this->ARESTAS;
}

int No::getPeso() const {
    return this->PESO;
}

void No::setPeso(int valor) {
    this->PESO = valor;
}

void No::RemoveAresta(int idNoDestino, bool direcionado) {
    if (idNoDestino < 0) {
        cout << "ID do nó destino não pode ser negativo" << endl;
        return;
    } else if (this->ARESTAS.find(idNoDestino) == this->ARESTAS.end()) {
        cout << "Aresta não existe" << endl;
        return;
    }
    this->ARESTAS.erase(idNoDestino);

    if (direcionado) {
        this->setGrauSaida(this->getGrauSaida() - 1);
    } else {
        this->setGrauSaida(this->getGrauSaida() - 1);
        this->setGrauEntrada(this->getGrauEntrada() - 1);
    }
}

bool No::isPassou() const {
    return PASSOU;
}

void No::setPassou(bool passou) {
    PASSOU = passou;
}
