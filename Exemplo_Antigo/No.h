#ifndef NO_H
#define NO_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Aresta.h"
#include "SearchInfo.h"

using namespace std;
class Aresta;
class SearchInfo;

class No {
public:
    No(int name);
    No(int name, int weight);
    virtual ~No();

    void setNome(int nome);
    int getNome();

    void setPeso(int nome);
    int getPeso();
    
    void setGroup(int nome);
    int getGroup();

    void setIncrementaGrau();
    void setDecrementarGrau();
    int getGrau();

    void setIncrementaGrauEntrada();
    void setDecrementaGrauEntrada();
    int getGrauEntrada();

    void setIncrementaGrauSaida();
    void setDecrementaGrauSaida();
    int getGrauSaida();

    void setProxNo(No *valor);
    No *getProxNo();

    void setPrimeiraAresta(Aresta *valor);
    Aresta *getPrimeiraAresta();

    void setUltimaAresta(Aresta *valor);
    Aresta *getUltimaAresta();
    
    void setSearchInfo(SearchInfo *searchInfo);
    SearchInfo *getSearchInfo();

private:
    int nome;
    int peso;
    int grauEntrada;
    int grauSaida;
    int particao;
    No *proxNo;
    Aresta *primeiraAresta;
    Aresta *ultimaAresta;
    SearchInfo *searchInfo;
    int group;
};

#endif // NO_H
