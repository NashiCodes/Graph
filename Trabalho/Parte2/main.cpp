#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "../src/models/Grafo.h"
#include "../src/Menu.h"

using namespace std;

void lerDemandas(Grafo *grafo, fstream *arquivo) {
    int id, demanda;
    string linha;
    while (getline(*arquivo, linha) && !arquivo->eof()) {
        if (std::equal(linha.begin(), linha.end(), "DEMAND_SECTION ")) continue;
        if (std::equal(linha.begin(), linha.end(), "DEPOT_SECTION ")) break;

        istringstream iss(linha);
        iss >> id >> demanda;
        No *no = grafo->getNos()->at(id);
        no->setPeso(demanda);
    }
}

void criaArestas(No *no, Grafo *grafo) {
    for (const auto &par: *grafo->getNos()) {
        No *noDestino = par.second;
        if (no->getID() == noDestino->getID()) continue;

        int cateto1 = no->X > noDestino->X ? no->X - noDestino->X : noDestino->X - no->X;
        int cateto2 = no->Y > noDestino->Y ? no->Y - noDestino->Y : noDestino->Y - no->Y;
        int peso = (int) round(sqrt(pow(cateto1, 2) + pow(cateto2, 2)));

        grafo->CriarAresta(no->getID(), noDestino->getID(), peso);
    }
}

int main() {
    fstream arquivo;
    ofstream saida;
    arquivo.open("A-n34-k5.txt", ios::in);
    saida.open("saida.txt", ios::out);

    if (saida.is_open() && arquivo.is_open()) {
        auto *grafo = new Grafo(true, true, false);

        string linha;
        string caminhoes = "No of trucks: ";
        string dimensao = "DIMENSION : ";
        string capaciadede = "CAPACITY : ";
        int nmCaminhoes, nmDimensao, nmCapacidade;


        while (getline(arquivo, linha) && !std::equal(linha.begin(), linha.end(), "NODE_COORD_SECTION ")) {
            string substr;
            if (linha.find(caminhoes) != string::npos) {
                substr = linha.substr(linha.find(caminhoes) + caminhoes.size());
                substr = substr.substr(0, substr.find(','));
                nmCaminhoes = stoi(substr);
            }
            if (linha.find(dimensao) != string::npos) {
                substr = linha.substr(linha.find(dimensao) + dimensao.size());
                nmDimensao = stoi(substr);
            }
            if (linha.find(capaciadede) != string::npos) {
                substr = linha.substr(linha.find(capaciadede) + capaciadede.size());
                nmCapacidade = stoi(substr);
            }
        }
        grafo->setOrdem(nmDimensao);
        while (nmCaminhoes > 0) {
            grafo->caminhoes.push_back(new Caminhao(nmCapacidade));
            nmCaminhoes--;
        }
        while (getline(arquivo, linha) && !arquivo.eof()) {
            if (std::equal(linha.begin(), linha.end(), "NODE_COORD_SECTION ")) continue;
            if (std::equal(linha.begin(), linha.end(), "DEMAND_SECTION ")) {
                lerDemandas(grafo, &arquivo);
                break;
            }
            int x, y, id;
            istringstream iss(linha);
            iss >> id >> x >> y;
            No *no = new No(id, 0);
            no->X = x;
            no->Y = y;
            grafo->InserirNo(no);

            criaArestas(no, grafo);
        }
        arquivo.close();

        cout << "Ordem do Grafo: " << grafo->getOrdem() << endl;
        cout << "Capacidade dos Caminhões: " << grafo->caminhoes.at(0)->capacidade << endl;
        cout << "Numero de arestas: " << grafo->getNumArestas() << endl;
        cout << "Numero de vertices: " << grafo->getNos()->size() << endl << endl;
        for (auto no: *grafo->getNos()) {
            cout << endl;
            cout << "No: " << no.second->getID() << " X: " << no.second->X << " Y: " << no.second->Y << endl;
            cout << "Demanda: " << no.second->getPeso() << endl;
            cout << "Grau de entrada: " << no.second->getGrauEntrada() << endl;
            cout << "Grau de saida: " << no.second->getGrauSaida() << endl;
        }

        // Exibir coordenadas e demandas dos clientes
        /*for (const auto& par : grafo.clientes) {
            int id = par.first;
            const No& no = par.second;
            cout << "Cliente " << id << ": (" << no.posX << ", " << no.posY << "), Demanda: " << no.demanda << endl;
        }*/
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }

    return 0;
}