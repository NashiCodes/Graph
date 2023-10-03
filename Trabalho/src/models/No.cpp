#include "No.h"

/**
 * Construtor da classe No.
 *
 * @param idNo: Identificador do nó
 * @return void
 * @precondition: idNo deve ser um inteiro positivo
 * @postcondition: Um nó é criado com o identificador idNo
 *
 */
No::No(int idNo) {
    this->_ID = idNo;
    this->_PESO = 0;
    this->_GRAU_ENTRADA = 0;
    this->_GRAU_SAIDA = 0;
}

/**
 * Construtor da classe No.
 *
 * @param idNo: Identificador do nó
 * @param peso: Peso do nó
 * @return void
 * @precondition: idNo deve ser um inteiro positivo
 * @postcondition: Um nó é criado com o identificador idNo e peso peso
 *
 */
No::No(int idNo, int peso) {
    this->_ID = idNo;
    this->_PESO = peso;
    this->_GRAU_ENTRADA = 0;
    this->_GRAU_SAIDA = 0;
}

/**
 * Destrutor da classe No.
 *
 * @return void
 * @precondition: Nenhuma
 * @postcondition: O nó é destruído
 *
 */
No::~No() {
    for (auto &it: this->ARESTAS) {
        delete it.second;
    }
}

/**
 * Retorna o identificador do nó.
 *
 * @return int
 */
int No::getID() const {
    return this->_ID;
}

/**
 * Define o identificador do nó.
 *
 * @param valor (new valor)
 */
void No::setID(int valor) {
    this->_ID = valor;
}

/**
 * Retorna o peso do nó.
 *
 * @return int
 */
int No::getPeso() const {
    return this->_PESO;
}

/**
 * Define o peso do nó.
 *
 * @param valor (new valor)
 */
void No::setPeso(int valor) {
    this->_PESO = valor;
}

/**
 * Retorna o grau de entrada do nó.
 *
 * @return int
 */
int No::getGrauEntrada() const {
    return this->_GRAU_ENTRADA;
}

/**
 * Define o grau de entrada do nó.
 *
 * @param valor (new valor)
 */
void No::setGrauEntrada(int valor) {
    this->_GRAU_ENTRADA = valor;
}

/**
 * Retorna o grau de saída do nó.
 *
 * @return int
 */
int No::getGrauSaida() const {
    return this->_GRAU_SAIDA;
}

/**
 * Define o grau de saída do nó.
 *
 * @param valor (new valor)
 */
void No::setGrauSaida(int valor) {
    if (valor < 0 || valor > this->ARESTAS.size())
        throw invalid_argument("Grau de saída não pode ser negativo");
    else
        this->_GRAU_SAIDA = valor;
}

/**
 * Retorna se o nó foi visitado.
 *
 * @return bool
 */
bool No::isVisitado() const {
    return this->visitado;
}

/**
 * Define se o nó foi visitado.
 *
 * @param valor (new valor)
 */
void No::setVisitado(bool valor) {
    this->visitado = valor;
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

void No::printarNo(bool ponderado, bool direcionado) {
    cout << "Nó: " << this->getID() << endl;
    cout << "Grau de entrada: " << this->getGrauEntrada() << endl;
    cout << "Grau de saída: " << this->getGrauSaida() << endl;
    cout << "Peso: " << this->getPeso() << endl;
    cout << "Arestas: " << endl;
    for (auto &aresta: this->getArestas()) {
        if (direcionado)
            if (ponderado)
                cout << "|" << this->getID() << "| -> |" << aresta.first << "| (" << aresta.second->getPeso() << ")";
            else
                cout << "|" << this->getID() << "| -> |" << aresta.first << "|";
        else if (ponderado)
            cout << "|" << this->getID() << "| <-> |" << aresta.first << "| (" << aresta.second->getPeso() << ")";
        else
            cout << "|" << this->getID() << "| <-> |" << aresta.first << "|";

        cout << endl;
    }
    cout << endl;
}
