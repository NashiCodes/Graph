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
No::No(int idNo)
{
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
No::No(int idNo, int peso)
{
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
No::~No()
{
    for (auto it = this->ARESTAS.begin(); it != this->ARESTAS.end(); ++it)
    {
        delete it->second;
    }
}

/**
 * Retorna o identificador do nó.
 *
 * @return int
 */
int No::getID()
{
    return this->_ID;
}

/**
 * Define o identificador do nó.
 *
 * @param valor (new valor)
 */
void No::setID(int valor)
{
    this->_ID = valor;
}

/**
 * Retorna o peso do nó.
 *
 * @return int
 */
int No::getPeso()
{
    return this->_PESO;
}

/**
 * Define o peso do nó.
 *
 * @param valor (new valor)
 */
void No::setPeso(int valor)
{
    this->_PESO = valor;
}

/**
 * Retorna o grau de entrada do nó.
 *
 * @return int
 */
int No::getGrauEntrada()
{
    return this->_GRAU_ENTRADA;
}

/**
 * Define o grau de entrada do nó.
 *
 * @param valor (new valor)
 */
void No::setGrauEntrada(int valor)
{
    this->_GRAU_ENTRADA = valor;
}

/**
 * Retorna o grau de saída do nó.
 *
 * @return int
 */
int No::getGrauSaida()
{
    return this->_GRAU_SAIDA;
}

/**
 * Define o grau de saída do nó.
 *
 * @param valor (new valor)
 */
void No::setGrauSaida(int valor)
{
    this->_GRAU_SAIDA = valor;
}

/**
 * Insere uma aresta no nó.
 *
 * @param idNoDestino (new valor)
 * @param aresta (new valor)
 *
 * @return void
 */
void No::setAresta(int idNoDestino, Aresta *aresta)
{
    this->ARESTAS[idNoDestino] = aresta;
}

/**
 * Retorna o nó destino.
 *
 * @return No
 */
Aresta *No::getAresta(int idNoDestino)
{
    return this->ARESTAS.at(idNoDestino);
}

/**
 * Retorna todas as arestas do nó.
 *
 * @return unordered_map<int, Aresta *>
 */
unordered_map<int, Aresta *> No::getArestas()
{
    return this->ARESTAS;
}
