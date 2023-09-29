#ifndef GRAFOS_MENU_H
#define GRAFOS_MENU_H

#include "Grafo.h"

class Menu
{
private:
    Grafo *grafo;
    ifstream *entrada;
    ofstream *arquivoSaida;

public:
    Menu(Grafo *grafo, ifstream *entrada, ofstream *arquivoSaida) : grafo(grafo), entrada(entrada), arquivoSaida(arquivoSaida){};
    virtual ~Menu()
    {
        delete grafo;
        delete entrada;
        delete arquivoSaida;
    };
    void menuPrincipal()
    {
        cout << "cheguei no menu principal" << endl;
    }

    void lerArquivo()
    {
       //ler o arquivo de entrada e criar o grafo
    }
};

#endif // GRAFOS_MENU_H
