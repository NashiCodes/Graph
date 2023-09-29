#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

#include "FileManager.h"
#include "Aresta.h"
#include "No.h"
#include "VectorEdgeSearch.h"
#include "Grafo.h"
#include "Tsp.h"

using namespace std;
typedef vector<No*> NodeVector;
Grafo *grafo;
bool fileReaded;


/***************************** Funcao Auxiliar *****************************/

/**
 * Funcao auxiliar que retorna um nome de arquivo válido passado pelo usuário. Se o  
 * nome do arquivo for inválido, um loop será repetido até que o nome do arquivo esteja  
 * correto.
 */
string getValidFilenameFromCin() {
    ifstream file;
    string filename;
    cout << "Por favor,digite o nome do arquivo...: ";

    while ( true ) {
        filename = "instancias/";
        string filenameAux;
        getline(cin, filenameAux);
        filename.append(filenameAux);
        file.open(filename.c_str());
        if ( file ) break;
        cout << "\nNome do arquivo invalido. Por favor entre com um nome de arquivo valido...: ";
    }

    file.close();
    return filename;
}

/**
 * Funcao auxiliar que retorna um inteiro válido passado pelo usuário. Se o  
 * usuário escrever um caractere inválido, um loop vai ser repetido até que seja passado 
 * uma string equivalente a um número.
 * 
 * @param message (Message that the user will see)
 */
int getIntFromCin(string message) {
    string aux;
    do {
        cout << message;
        cin >> aux;
        cin.ignore();
        if ( aux == "0" ) {
            break;
        }
    } while ( !atoi(aux.c_str()) );
    return atoi(aux.c_str());
}

/**
 * Funcao auxiliar que retorna TRUE se o usuário escolher Y ou y, FALSE se 
 * escolher N ou n. Se o usuário escrever um caracter inválido, um loop
 * será repetido até que a string esteja correta. 
 * 
 * @param message (Message that the user will see)
 */
bool getBoolFromCin(string message) {
    string aux;
    do {
        cout << message;
        cin >> aux;
        cin.ignore();
        transform(aux.begin(), aux.end(), aux.begin(), ::toupper);
    } while ( aux != "Y" && aux != "N" );

    if ( aux == "Y" ) {
        return true;
    } else {
        return false;
    }
}

/**
 * Funcao auxiliar que imprime um monte de  '-'.
 */
void imprimeSeparador() {
    cout << "\n------------------------------------------------------------\n";
}

/**
 * Funcao auxiliar que limpa a tela e imprime o titulo.
 */
void imprimeTitulo() {
    cout << string(40, '\n');
    imprimeSeparador();
    cout << "--------- Teoria dos Grafos - 2017.1 - UFJF --------\n";
    cout << "- Gabriel Miranda - Victor Henrique - Vitor Monteiro - Mariana Trevizani -";
    imprimeSeparador();
}

/**
 * Funcao auxiliar que simula uma pausa até que o usuário digite qualquer caracter e 
 * pressione enter.
 */
void anyCharacterToBackToMenu() {
    string aux;
    cout << "\n\n[Qualquer caracter] + [ENTER] para voltar ao menu... ";
    cin >> aux;
    cin.ignore();
}

/**
 * Funcao auxiliar que retorna uma sequencia de caracteres com cada nome de nó do NodeVector.
 * @param nodeVector (vector<Node*>)
 */
string printNodeVector(NodeVector nodeVector) {
    stringstream ss;

    ss << "Nomes dos Nós: {";
    for ( unsigned int i = 0; i < nodeVector.size(); i++ ) {
        ss << nodeVector[i]->getNome() << "(d" << nodeVector[i]->getPeso() << ")";
        if ( i + 1 < nodeVector.size() ) {
            ss << ", ";
        }
    }
    ss << "}";

    return ss.str();
}

/**
 * Funcao auxiliar que retorna uma sequencia de caracteres com cada nome de nó do NodeVector.
 * @param nodeVector (vector<Node*>)
 */
string printNodeVectorSemNULL(NodeVector nodeVector) {
    stringstream ss;

    ss << "Nomes dos Nós: {";
    for ( unsigned int i = 0; i < nodeVector.size(); i++ ) {
        if ( nodeVector[i] != NULL ) {
            ss << nodeVector[i]->getNome() << "( " << nodeVector[i]->getPeso() << ")";
            if ( i + 1 < nodeVector.size() ) {
                ss << ", ";
            }
        }
    }
    ss << "}";

    return ss.str();
}

/**
 * Funcao auxiliar que retorna uma sequencia de caracteres com cada nome de nó do NodeVector.
 * @param nodeVector (vector<Node*>)
 */
string printNodeVectorSemNULLFuncaPontes(NodeVector nodeVector) {
    stringstream ss;

    ss << "Nomes das Arestas: {";
    int indice = nodeVector.size();
    for ( unsigned int i = 0; i < indice; i + 2 ) {
        if ( nodeVector[i] != NULL ) {
            ss << " (" << nodeVector[ i ]->getNome() << " -> " << nodeVector[ i + 1 ]->getNome() << ")";
            if ( i + 1 < indice ) {
                ss << ",";
            }
        }
    }
    ss << "}";

    return ss.str();
}

/**
 * Funcao auxiliar que gera um arquivo de saida contendo a estrutura 
 * de um dado grafo.
 * 
 * @param *auxGraph ()
 * @param outputFileName ()
 */
string gerarArquivoDeUmGrafo(Grafo *auxGraph, string outputFileName) {
    ofstream outputFile(outputFileName.c_str());

    if ( outputFile.is_open() && auxGraph != NULL ) {
        No *auxNode = auxGraph->getNoRaiz();
        Aresta *auxEdge;

        outputFile << auxGraph->getOrdem() << "\n";

        while ( auxNode != NULL ) {
            auxEdge = auxNode->getPrimeiraAresta();
            if ( auxEdge == NULL ) {
                outputFile << auxNode->getNome() << "\n";
            } else {
                while ( auxEdge != NULL ) {
                    outputFile << auxNode->getNome() << " " << auxEdge->getNoDestino()->getNome() << " " << auxEdge->getPeso() << "\n";
                    auxEdge = auxEdge->getProxAresta();
                }
            }

            auxNode = auxNode->getProxNo();
        }
        outputFile.close();
    } else {
        stringstream ss;
        ss << "ERRO: Não foi possivel criar o arquivo" << outputFileName << "'.";
        return ss.str();
    }

    stringstream ss;
    ss << "O arquivo de saida '" << outputFileName << "' foi gerado.";
    return ss.str();
}

/**
 * Funcao auxiliar que gera um arquivo de saida contendo um determinado texto.
 * 
 * @param text (text to be inserted in the file)
 * @param outputFileName (output filename)
 */
string gerarArquivoTexto(string text, string outputFileName) {
    ofstream outputFile(outputFileName.c_str());

    if ( outputFile.is_open() ) {
        outputFile << text;
        outputFile.close();
    } else {
        stringstream ss;
        ss << "ERRO: Não foi possivel criar o arquivo '" << outputFileName << "'.";
        return ss.str();
    }

    stringstream ss;
    ss << "O arquivo de saida '" << outputFileName << "' foi gerado.";
    return ss.str();
}



/************************ Funcões das opcões do menu ***********************/

/**
 /**
 * Esta funcao e chamada na main() quando o usuário digita”1” no menu principal. \n
 * 
 * Ele pergunta ao usuário se ele quer um digrafo ou não, lê todo o arquivo de entrada 
 * e faz a insercao dos nós e das arestas. Se bool askUser == FALSE,
 * o grafo padrão não e um digrafo.\n
 *
 * ATTENTION: Ask the user to choose digraph makes it not necessary to make a 
 * check function, prevents edges are inserted when they should not be able
 * and the most interesting is that the same input file can now be used or not 
 * for digraphs.\n
 *
 * Example: 1 2 333\n
 *    > Em um grafo normal: Cria 2 arestas (1 to 2 and 2 to 1)\n
 *    > Em um digrafo: Cria 1 aresta(1 to 2)
 *
 * @param filename (file to be readed)
 */
string leECriaGrafo(string filename) {
    bool isDigraph;

    cout << "Preparando para ler o arquivo '" << filename << "'...\n";
    isDigraph = getBoolFromCin("Seu grafo e um digrafo? ([Y]es / [N]o) ");

    grafo = FileManager::readAndCreateGraph(filename, isDigraph);

    return "O grafo foi criado.";
}

string leECriaGrafo(string filename, Grafo* auxGrafo) {
    bool isDigraph;

    cout << "Preparando para ler o arquivo '" << filename << "'...\n";
    isDigraph = getBoolFromCin("Seu grafo e um digrafo? ([Y]es / [N]o) ");

    auxGrafo = FileManager::readAndCreateGraph(filename, isDigraph);

    return "O grafo foi criado.";
}

/**
 * Esta funcao e chamado no main() quando o usuário digita “3” no menu principal.\n
 * 
 * Esta funcao obtém o nome do nó e o seu peso a partir do teclado e chama
 * graph->insertNode(...).
 */
string insereNo() {
    int name, weight;
    imprimeTitulo();
    cout << "---------------------- Insercao do No ---------------------";
    imprimeSeparador();
    cout << "Atencao: Se o nó já existir, seu peso será atualizado.";
    imprimeSeparador();

    name = getIntFromCin("Por favor, digite o nome do no............: ");
    weight = getIntFromCin("Por favor, digite o peso do no ...: ");

    No *aux = grafo->insereNo(name, weight, true);

    stringstream ss;
    if ( aux->getProxNo() != NULL ) {
        ss << "O No existente " << name << "teve seu peso atualizado " << weight << ".";
    } else {
        ss << "O no " << name << " de peso " << weight << " foi inserido.";
    }

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "4" no menu principal.\n
 * 
 * Esta funcao obtém o nome do nó a partir do teclado e chama graph->removeNode(...).
 */
string removeNo() {
    int name;
    imprimeTitulo();
    cout << "----------------------- Remocao do No ----------------------";
    imprimeSeparador();

    name = getIntFromCin("Por favor, digite o nome do no............: ");

    stringstream ss;
    if ( grafo->removeNo(name) ) {
        ss << "O No " << name << " foi removido.";
    } else {
        ss << "O No " << name << " não existe.";
    }
    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "5" no menu principal.\n
 * 
 * Esta funcao obtém o nome do no de origem, o nome do no de destino e o peso da aresta
 * do teclado e chama graph->insertEdge(...).
 */
string insereAresta() {
    int sourceNodeName, destinyNodeName, edgeWeight;
    imprimeTitulo();
    cout << "---------------------- Insercao de Aresta ---------------------";
    imprimeSeparador();
    cout << "Atencao: Se você digitar um nome de No que não existe, ele será criado.\n";
    cout << "Atencao: Se a aresta já existe, o peso da aresta vai ser atualizado.";
    imprimeSeparador();

    sourceNodeName = getIntFromCin("Por favor, digite o nome do No de origem....: ");
    destinyNodeName = getIntFromCin("Por favor, digite o nome do No de destino...: ");
    edgeWeight = getIntFromCin("Por favor, digite o peso da aresta ........: ");

    stringstream ss;
    if ( grafo->inserirAresta(sourceNodeName, destinyNodeName, edgeWeight) ) {
        ss << "A aresta do No de origem " << sourceNodeName << ", No de destino " << destinyNodeName << " e peso " << edgeWeight << " foi criado.";
    } else {
        ss << "O peso da aresta do No de origem" << sourceNodeName << " e o No de destino " << destinyNodeName << " foi atualizado para " << edgeWeight << ".";
    }

    return ss.str();
}

/**
 * A funcao e chamada na main() quando o usuário digita "6" no menu principal.\n
 * 
 * Esta funcao obtém o nome do No de origem, nome do No de destino a partir do teclado
 * e reove a aresta.\n
 */
string removeAresta() {
    int sourceNodeName, destinyNodeName;
    imprimeTitulo();
    cout << "------------------------ Remocao da Aresta ----------------------";
    imprimeSeparador();

    sourceNodeName = getIntFromCin("Por favor, digite o nome do No de origem....: ");
    destinyNodeName = getIntFromCin("Por favor, digite o nome do No de destino...: ");

    bool sourceFound = grafo->procurarNoPeloNome(sourceNodeName);
    No *auxSourceNode = grafo->getNoAux();

    bool destinyFound = grafo->procurarNoPeloNome(destinyNodeName);
    No *auxDestinyNode = grafo->getNoAux();

    stringstream ss;
    if ( sourceFound && destinyFound ) {
        int count = 0;
        count = 0;
        count += grafo->removeArestas(auxSourceNode, auxDestinyNode, false, false, -1);
        if ( !grafo->isDigraph() ) {
            grafo->removeArestas(auxDestinyNode, auxSourceNode, false, false, -1);
            ss << "A Aresta do No de origem " << sourceNodeName << ", no de destino " << destinyNodeName << " foi removida.";
        } else {
            ss << "A Aresta do No de origem " << sourceNodeName << ", No de destino " << destinyNodeName << " foi removida.";
        }

        ss << "\n" << count << " Aresta foi removida.";
    } else {
        if ( !sourceFound && !destinyFound ) {
            ss << "Os Nos " << sourceNodeName << " e " << destinyNodeName << " não existem.";
        } else if ( !sourceFound ) {
            ss << "O No " << sourceNodeName << " não existe.";
        } else {
            ss << "O No " << destinyNodeName << " não existe.";
        }
    }

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "7" no menu principal.\n
 * 
 * Esta funcao obtém o nome do No do teclado e retorna seu grau.
 * 
 * Se o grafo e um digrafo, esta funcao da os graus de saida e de entrada do No.
 * 
 */
string grauNo() {
    int name;
    imprimeTitulo();
    cout << "------------------------ Grau do No -----------------------";
    imprimeSeparador();

    name = getIntFromCin("Por favor, digite o nome do No...: ");

    stringstream ss;
    if ( grafo->procurarNoPeloNome(name) ) {
        if ( grafo->isDigraph() ) {
            ss << "O grau de entrada do No " << name << " e ";
            ss << grafo->getNoAux()->getGrauEntrada();
            ss << ".\n";
            ss << "O grau de saida do No " << name << " e ";
            ss << grafo->getNoAux()->getGrauSaida();
            ss << ".\n";
        } else {
            ss << "O grau do No " << name << " e ";
            ss << grafo->getNoAux()->getPeso();
            ss << ".";
        }
    } else {
        ss << "O No " << name << " não existe.";
    }
    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "9" no menu principal.\n
 * 
 * Esta funcao retorna a ordem do grafo.
 */
string ordemGrafo() {
    stringstream ss;
    ss << "A ordem do grafo e " << grafo->getOrdem() << ".";
    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "10" no menu principal.\n
 * 
 * Esta funcao diz se o grafo e trivial ou não.
 */
string isTrivial() {
    stringstream ss;
    if ( grafo->isTrivial() ) {
        ss << "O grafo e trivial.";
    } else {
        ss << "O grafo não e trivial.";
    }
    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "11" no menu principal.\n
 * 
 * Esta funcao diz se o grafo e nulo ou não.
 */
string isNULL() {
    if ( grafo->isNULL() ) {
        return "O grafo e nulo.";
    } else {
        return "O grafo não e nulo.";
    }
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "12" no menu principal.\n
 * 
 * Esta funcao pega o nome do No do teclado e chama graph->getNeighborhood(...).
 */
string vizinhacaAberta() {
    int nodeName;
    imprimeTitulo();
    cout << "---------------- Vizinhanca aberta do No ---------------";
    imprimeSeparador();

    nodeName = getIntFromCin("Por favor, digite o nome do No............: ");

    NodeVector nodeVector = grafo->getVizinhaca(nodeName, false);

    stringstream ss;
    if ( grafo->getNoAux() == NULL ) {
        ss << "O No " << nodeName << " não existe.";
    } else {
        ss << "A vizinhanca aberta do No " << nodeName << " e: \n" << printNodeVector(nodeVector) << ".";
    }

    string filename = "openNeighborhood.txt";
    return gerarArquivoTexto(ss.str(), filename);
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "13" no menu principal.\n
 * 
 * Esta funcao pega o nome do No do teclado e chama graph->getNeighborhood(...).
 */
string vizinhacaFechada() {
    int nodeName;
    imprimeTitulo();
    cout << "--------------- A vizinhanca fechada do No --------------";
    imprimeSeparador();

    nodeName = getIntFromCin("Por favor, digite o nome do No............: ");

    NodeVector nodeVector = grafo->getVizinhaca(nodeName, true);

    stringstream ss;
    if ( grafo->getNoAux() == NULL ) {
        ss << "O No " << nodeName << " não existe.";
    } else {
        ss << "A vizinhanca fechada do No" << nodeName << " e: \n" << printNodeVector(nodeVector) << ".";
    }

    string filename = "closedNeighborhood.txt";
    return gerarArquivoTexto(ss.str(), filename);
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "14" no menu principal.\n
 * 
 * Esta funcao diz se o grafo e um multigrafo ou não.
 */
string isMultigrafo() {
    return "O grafo não e multigrafo.";
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "15" no menu principal.\n
 * 
 * Esta funcao diz se o grafo e um grafo completo ou não.
 */
string isCompleto() {
    if ( grafo->isCompleto() ) {
        return "O grafo e um grafo completo.";
    } else {
        return "O grafo não e completo.";
    }
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "16" no menu principal.\n
 * 
 * Esta funcao diz se o grafo e bipartido ou não.
 */
string isBipartite() {
    if ( grafo->isBipartido() ) {
        return "O grafo e um grafo bipartido. IMPLEMENTAR!!!";
    } else {
        return "O grafo não e um grafo bipartido. IMPLEMENTAR!!!";
    }
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "17" no menu principal.\n
 * 
 * Esta funcao obtém o nome do No de origem, do No de destino a partir do teclado e chama graph->shortestPathDijkstra(...).
 */
string menorCaminhoDijkstra() {
    int nodeA, nodeB;
    imprimeTitulo();
    cout << "----- Caminho mais curto do No A ao No B usando DIJKSTRA -----";
    imprimeSeparador();

    nodeA = getIntFromCin("Por favor, digite o nome do No A...: ");
    nodeB = getIntFromCin("Por favor, digite o nome do No B...: ");

    bool sourceFound = grafo->procurarNoPeloNome(nodeA);
    No *auxSourceNode = grafo->getNoAux();

    bool destinyFound = grafo->procurarNoPeloNome(nodeB);
    No *auxDestinyNode = grafo->getNoAux();

    stringstream ss;
    if ( sourceFound && destinyFound ) {
        string filename = "Menor Caminho utilizando Dijkstra.txt";
        string fileText = grafo->caminhoMaisCurtoDijkstra(nodeA, nodeB);
        ss << gerarArquivoTexto(fileText, filename);
    } else {
        if ( !sourceFound && !destinyFound ) {
            ss << "Os Nos " << nodeA << " e " << nodeB << " não existem.";
        } else if ( !sourceFound ) {
            ss << "O No " << nodeA << " não existe.";
        } else {
            ss << "O No " << nodeB << " não existe.";
        }
    }

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "17" no menu principal.\n
 * 
 * Esta funcao obtém o nome do No de origem, do No de destino a partir do teclado e utiliza Dijkstra ou Floyd.
 */
string menorCaminho() {
    int noA, noB;
    imprimeTitulo();
    cout << "----- Caminho mais curto do No A ao No B usando DIJKSTRA -----";
    imprimeSeparador();

    noA = getIntFromCin("Por favor, digite o nome do No A...: ");
    noB = getIntFromCin("Por favor, digite o nome do No B...: ");

    bool sourceFound = grafo->procurarNoPeloNome(noA);
    No *auxSourceNode = grafo->getNoAux();

    bool destinyFound = grafo->procurarNoPeloNome(noB);
    No *auxDestinyNode = grafo->getNoAux();


    stringstream ss;
    if ( sourceFound && destinyFound ) {

        bool dijkstra;
        dijkstra = getBoolFromCin("Utilizar Dijksta ?? caso contra sera usado Floyd\n Sim[y] Nao[n] \n\n");

        string filename = "Menor Caminho.txt";

        if ( dijkstra ) {
            string fileText = grafo->caminhoMaisCurtoDijkstra(noA, noB);
            ss << gerarArquivoTexto(fileText, filename);
        } else {
            string fileText = grafo->menorCaminhoFloyd();
            ss << gerarArquivoTexto(fileText, filename);
        }
    } else {
        if ( !sourceFound && !destinyFound ) {
            ss << "Os Nos " << noA << " e " << noB << " não existem.";
        } else if ( !sourceFound ) {
            ss << "O No " << noA << " não existe.";
        } else {
            ss << "O No " << noB << " não existe.";
        }
    }

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "18" no menu principal.\n
 * 
 * Esta funcao diz o grau do grafo.
 */
string graphDegree() {
    return grafo->getGrau();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "19" no menu principal.\n
 * 
 * Esta funcao obtém o nome do No de origem, do No de destino a partir do teclado e chama graph->isAdjacent(...).
 */
string isAdjacentes() {
    int nodeA, nodeB;
    imprimeTitulo();
    cout << "----------------------- Adjacência do No ---------------------";
    imprimeSeparador();

    nodeA = getIntFromCin("Por favor, digite o nome do No A...: ");
    nodeB = getIntFromCin("Por favor, digite o nome do No B..: ");

    return grafo->isAdjacente(nodeA, nodeB);
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "20" no menu principal.\n
 * 
 * Esta funcao obtém um conjunto de nomes dos Nos a partir do teclado, chama 
 * graph->generateGraphInducedByANodeSet(...) e gera um arquivo texto com resultado. 
 * 
 */
string grafoInduzidoPorUmConjuntoNos() {
    int numberOfNodes, node;
    imprimeTitulo();
    cout << "---------------- Grafo induzido por um conjunto de Nos ---------------";
    imprimeSeparador();
    cout << "Atencao: Pressione uma tecla sem algarismos e pressione [ENTER] para finalizar.";
    imprimeSeparador();

    NodeVector nodeVector;
    numberOfNodes = getIntFromCin("\nQuantos nós serão inseridos? ");
    nodeVector.resize(numberOfNodes);

    for ( int i = 0; i < numberOfNodes; i++ ) {

        node = getIntFromCin("\nPor favor, digite um nome do No...: ");
        if ( grafo->procurarNoPeloNome(node) ) {
            nodeVector[i] = grafo->getNoAux();
            cout << "Inserido!";
        } else {
            cout << "O No não existe.";
        }
    }

    string filename = "graphInducedByANodeSet.txt";
    return gerarArquivoDeUmGrafo(Grafo::generateGraphInducedByANodeSet(nodeVector, grafo->isDigraph()), filename);
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "21" no menu principal.\n
 * 
 * Esta funcao chama graph->getComplementaryGraph() e gera um arquivo texto
 * com o resultado.
 */
string grafoComplementar() {
    string filename = "complementaryGraph.txt";
    return gerarArquivoDeUmGrafo(grafo->getGrafoComplementar(), filename);
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "22" no menu principal.\n
 * 
 * Esta funcao diz se o grafo e conectado ou não.
 */
string isConnected() {
    if ( grafo->isConexo() ) {
        return " O grafo e conectado.";
    } else {
        return "O grafo não e conectado.";
    }
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "23" no menu principal.\n
 * 
 * Esta funcao obtém o nome do No a partir do teclado e chama graph->nodeOfJoint(...).
 */
string noDeArticulacao() {

    imprimeTitulo();
    cout << "--------------------- No de articulacao --------------------";
    imprimeSeparador();

    NodeVector noVector = grafo->getTodasNosArticulacao();
    stringstream ss;

    ss << "No de Articulacao \n\n";
    ss << printNodeVectorSemNULL(noVector);
    return gerarArquivoTexto(ss.str(), "Nos de Articulacao.txt");
}

/**
 * @decrepated
 * Esta funcao e chamada na main() quando o usuário digita "24" no menu principal.\n
 * 
 * Esta funcao diz se uma aresta e ponte ou não.
 */
string isPonte() {
    int sourceNodeName, destinyNodeName;
    imprimeTitulo();
    cout << "------------------------ Ponte -----------------------";
    imprimeSeparador();

    sourceNodeName = getIntFromCin("Por favor, digite o nome do No de origem....: ");
    destinyNodeName = getIntFromCin("Por favor, digite o nome do No de destino...: ");

    bool sourceFound = grafo->procurarNoPeloNome(sourceNodeName);
    No *auxSourceNode = grafo->getNoAux();

    bool destinyFound = grafo->procurarNoPeloNome(destinyNodeName);
    No *auxDestinyNode = grafo->getNoAux();

    stringstream ss;
    if ( sourceFound && destinyFound ) {
        //        return grafo->isPonte(sourceNodeName, destinyNodeName);
    } else {
        if ( !sourceFound && !destinyFound ) {
            ss << "Os Nos " << sourceNodeName << " e " << destinyNodeName << " não existem.";
        } else if ( !sourceFound ) {
            ss << "O No " << sourceNodeName << " não existe.";
        } else {
            ss << "O No " << destinyNodeName << " não existe.";
        }
    }

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "24" no menu principal.\n
 * 
 * Esta funcao retorna todos as aresta pontes
 */
string getAllPontes() {

    imprimeTitulo();
    cout << "------------------------ Ponte -----------------------";
    imprimeSeparador();

    stringstream ss;
    NodeVector noVector = grafo->getTodasPontes();

    ss << "Arestas Pontes \n\n";
    ss << printNodeVectorSemNULLFuncaPontes(noVector);
    gerarArquivoTexto(printNodeVectorSemNULL(noVector), "teste.txt");
    return gerarArquivoTexto(ss.str(), "Arestas Pontes.txt");
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "25" no menu principal.\n
 * 
 * Esta funcao imprime a sequência de graus do grafo.
 */
string sequenceDegree() {
    string filename = "Sequencia Grau.txt";
    string fileText = grafo->sequenciaGrau();
    return gerarArquivoTexto(fileText, filename);
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "26" no menu principal.\n
 * 
 * Esta funcao recebe o nome do No raiz do teclado, chama graph->depthFirstSearchTree(...) 
 * e gera um arquivo texto com a árvore resultante da pesquisa.
 */
string buscaProfundidade() {
    int nodeName;
    imprimeTitulo();
    cout << "-------------------- Busca em profundidade --------------------";
    imprimeSeparador();

    nodeName = getIntFromCin("Por favor, digite o nome do No raiz.......: ");

    string filename = "Busca Profundidade.txt";
    string fileText = grafo->arvoreBuscaProfundidade(nodeName);
    stringstream ss;

    if ( fileText != "" ) {
        ss << gerarArquivoTexto(fileText, filename);
    } else {
        ss << "O No " << nodeName << " não existe.";
    }

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "27" no menu principal.\n
 * 
 * Esta funcao recebe o nome do No raiz do teclado, chama graph->depthFirstSearchTree(...) 
 * e gera um arquivo texto com a árvore resultante da pesquisa.
 */
string buscaLargura() {
    int nodeName;
    imprimeTitulo();
    cout << "------------------- Busca em largura -------------------";
    imprimeSeparador();

    nodeName = getIntFromCin("Por favor, digite o nome do No raiz.......: ");

    string filename = "Busca Largura.txt";
    string fileText = grafo->arvoreBuscaLargura(nodeName);
    stringstream ss;

    if ( fileText != "" ) {
        ss << gerarArquivoTexto(fileText, filename);
    } else {
        ss << "O No " << nodeName << " não existe.";
    }

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "28" no menu principal.\n
 * 
 * Esta funcao retorna uma string com os componentes conexa de um determinado No
 * A e de um dado no B.
 */
string ComponenteConexaDeAeB() {
    int nodeNameA, nodeNameB;
    No *nodeA, *nodeB;
    bool nodeAFound, nodeBFound;

    imprimeTitulo();
    cout << "---------- Componentes conexa do No A e B ----------";
    imprimeSeparador();

    nodeNameA = getIntFromCin("Por favor, digite o nome do No A....: ");
    nodeNameB = getIntFromCin("Por favor, digite o nome do No B....: ");

    if ( grafo->procurarNoPeloNome(nodeNameA) ) {
        nodeAFound = true;
        nodeA = grafo->getNoAux();
    } else {
        nodeAFound = false;
    }

    if ( grafo->procurarNoPeloNome(nodeNameB) ) {
        nodeBFound = true;
        nodeB = grafo->getNoAux();
    } else {
        nodeBFound = false;
    }

    stringstream ss;
    if ( !nodeAFound and !nodeBFound ) {
        ss << "O No " << nodeNameA << " e o No " << nodeNameB << " não existem.";
    } else if ( !nodeAFound and nodeBFound ) {
        ss << "O No " << nodeNameA << " não existes.";
    } else if ( nodeAFound and !nodeBFound ) {
        ss << "O No " << nodeNameB << " não existes.";
    } else {
        grafo->arvoreBuscaProfundidade(nodeNameA);
        if ( nodeA->getSearchInfo()->getConnectedComponent() == nodeB->getSearchInfo()->getConnectedComponent() ) {
            ss << "O No " << nodeNameA << " e o No " << nodeNameB << " estão na mesma componente conexa.";
        } else {
            ss << "O No " << nodeNameA << " e o No " << nodeNameB << " não estão na mesma componente conexa.";
        }
    }

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "29" no menu principal.\n
 * 
 * Esta funcao retorna uma string com o fechamento transitivo direto
 * do No A.
 */
string fechoTransitivoDiretoDeUmNo() {

    int nodeName;
    imprimeTitulo();
    cout << "------------ Fechamento Transitivo Direto de um No -----------";
    imprimeSeparador();
    nodeName = getIntFromCin("Por favor, digite o nome do No raiz...: ");

    bool sourceFound = grafo->procurarNoPeloNome(nodeName);
    No *auxSourceNode = grafo->getNoAux();

    stringstream ss;
    if ( sourceFound ) {
        string filename = "fechoTransitivoDiretoDeUmNo.txt";
        string fileText = grafo->fechoTransitivoDiretoDeUmNo(nodeName);
        ss << gerarArquivoTexto(fileText, filename);
    } else {
        ss << "O No " << nodeName << " não existe.";
    }

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "30" no menu principal.\n
 * 
 * Esta funcao retorna uma string com o fechamento transitivo indireto do
 * no A.
 */
string fechoTransitivoIndiretoDeUmNo() {

    int nodeName;
    imprimeTitulo();
    cout << "----------- Fechamento transitivo indireto de um No ----------";
    imprimeSeparador();
    nodeName = getIntFromCin("Por favor, digite o nome do No raiz...: ");

    bool sourceFound = grafo->procurarNoPeloNome(nodeName);
    No *auxSourceNode = grafo->getNoAux();

    stringstream ss;
    if ( sourceFound ) {
        string filename = "fechoTransitivoIndiretoDeUmNo.txt";
        string fileText = grafo->fechoTransitivoIndiretoDeUmNo(nodeName);
        ss << gerarArquivoTexto(fileText, filename);
    } else {
        ss << "O No " << nodeName << " não existe.";
    }

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "31" no menu principal.\n
 * 
 * Esta funcao gera um arquivo com a ordem topológica deste grafo se o 
 * e um grafo aciclico.
 */
string DAGOrdenacaoTopologica() {
    imprimeTitulo();
    cout << "---------- Ordenacao Topológica ----------\n";
    imprimeSeparador();
    return grafo->DAGOrdenacaoTopologica();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "32" no menu principal.\n
 * 
 * Esta funcao gera um arquivo com uma matriz com o valor do caminho mais curto 
 * de todos os Nos para todos os Nos usando o algoritmo de FLOYD.
 */
string menocaminhoTodosNos() {
    stringstream ss;
    imprimeTitulo();
    cout << "----- Caminho mais curto de todos os Nos para todos os Nos usando FLOYD -----";
    imprimeSeparador();
    string filename = "menor Caminho Floyd.txt";
    string fileText = grafo->menorCaminhoFloyd();
    ss << gerarArquivoTexto(fileText, filename);
    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "33" no menu principal.\n
 * 
 * esta funcao gera um arquivo com todas as componentes conexas do grafo
 * e um exemplo de uma arvore de busca de cada componente.
 */
string componentesConexas() {
    stringstream ss;
    ss << "O grafo tem " << grafo->getComponentesConexas() << " componentes conexas.\n";
    ss << "Para ver a árvore de busca de cada componente conexa, chama a DFS/BFS funcionalidades.";

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "35" no menu principal.\n
 * 
 * esta funcao gera um arquivo com árvore geradora minima usando algoritmo de
 * PRIM.
 */
string agmPRIM() {

    int nodeName;
    imprimeTitulo();
    cout << "---------- Arvore geradora minima usando PRIM ---------";
    imprimeSeparador();
    nodeName = getIntFromCin("Por favor, digite o nome do No raiz...: ");

    bool sourceFound = grafo->procurarNoPeloNome(nodeName);
    No *auxSourceNode = grafo->getNoAux();

    stringstream ss;
    if ( sourceFound ) {
        string filename = "Arvore geradora minima usando PRIM.txt";
        string fileText = grafo->agmPRIM(nodeName);
        ss << gerarArquivoTexto(fileText, filename);
    } else {
        ss << "O No " << nodeName << " não existe.";
    }

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "36" no menu principal.\n
 * 
 * Esta funcao gera um arquivo com a árvore geradora minima usando o algoritmo de
 * KRUSKAL.
 */
string agmKRUSKAL() {

    stringstream ss;

    string filename = "Arvore geradora minima usando KRUSKAL.txt";
    string fileText = grafo->agmKRUSKAL();
    ss << gerarArquivoTexto(fileText, filename);

    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "37" no menu principal.\n
 * 
 * Esta funcao retorna uma string com a K Conectividade deste grafo.
 */
string KConectividade() {

    imprimeTitulo();
    cout << "---------------------- K-Conectividade----------------------";
    imprimeSeparador();
    return grafo->kConectividade();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "39" no menu principal.\n
 * 
 * Esta funcao retorna o número de arestas do grafo.
 */
string cardinalidadeGrafo() {
    stringstream ss;
    ss << "A cardinalidade do grafo (número de arestas) e " << grafo->getCardinalidade() << ".";
    return ss.str();
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "38" no menu principal.\n
 * 
 * Esta funcao retornar uma string informando se este grafo e um grafo euleriano ou não.
 * 
 */
string grafoEuleriano() {


    imprimeTitulo();
    cout << "----------------------- Grafo Euleriano ----------------------";
    imprimeSeparador();

    return grafo->isEuleriano();
}

string informacoesGrafo() {
    string filename = "Grafo e suas informacoes.txt";
    string fileText = grafo->dadosObtidosFloyd();
    return gerarArquivoTexto(fileText, filename);
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "44" no menu principal.\n
 * 
 * Esta funcao chama graph->nodesInformations() e gera um arquivo texto com 
 * o resultado.
 */
string getInformacoesNo() {
    string filename = "No e suas informacoes.txt";
    string fileText = grafo->informacoesNos();

    return gerarArquivoTexto(fileText, filename);
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "55" no menu principal.\n
 * 
 * Esta funcao chama graph->inMemoryGraphStructure() e gera um arquivo texto com
 * o resultado..
 */
string getEstruturaGrafo() {
    string filename = "Estrutura Grafo.txt";
    string fileText = grafo->estruturaGrafoEmMemoria();

    return gerarArquivoTexto(fileText, filename);
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "66" no menu principal.\n
 * 
 * Esta funcao pega o nome do No, chama graph->subgraphInducedByClosedNeighborhood(...) 
 * e gera um arquivo texto com o resultado.
 */
string getSubgrafoInduzidoPorUmaVizinhancaFechada() {
    int name;
    imprimeTitulo();
    cout << "--------- Subgrafo induzido por uma vizinhanca fechada --------";
    imprimeSeparador();

    name = getIntFromCin("Por favor, digite o nome do No............: ");

    string filename = "subgraphInducedByClosedNeighborhood.txt";
    string fileText = grafo->subrgrafoInduzidoPelaVizinhacaFechada(name);

    if ( fileText.substr(0, 3) != "The" ) {
        return gerarArquivoTexto(fileText, filename);
    }
    return fileText;
}

/**
 * Esta funcao e chamada na main() quando o usuário digita "77" no menu principal.\n
 * 
 * Esta funcao diz se o grafo e um digrafo ou não.
 */
string isDigraph() {
    if ( grafo->isDigraph() ) {
        return "O grafo e um digrafo.";
    } else {
        return "O grafo não e um digrafo.";
    }
}

string rodarAlgoritmoTSP() {

    stringstream ss;
    Tsp* algoritmo = new Tsp(grafo);

    imprimeTitulo();
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    imprimeSeparador();

    Tsp* tsp = new Tsp(grafo);
    ss << gerarArquivoTexto(tsp->rodarTsp(10), "AlgotimoTSP.txt");

    return ss.str();
}

/**
 * Main function.
 * 
 * @param argc ()
 * @param argv ()
 */
int main(int argc, char* argv[]) {

    string alert, option;
    string filename;
    string outputFilename;
    fileReaded = false;

    // Check the value of argc.
    // If the number os parameters is wrong.
    if ( argc > 1 && argc != 3 ) {
        cout << "O uso e: ./grupo8 <inputFileName> <outputFileName>\n";
        system("pause");
        return EXIT_SUCCESS;

        // If the number os parameters is right. 
    } else if ( argc == 3 ) {
        filename = argv[1];
        outputFilename = argv[2];

        ifstream file;
        file.open(filename.c_str());
        if ( !file ) {
            cout << "Usage is: ./grupo8 <inputFileName> <outputFileName>\n";
            cout << "O arquivo'" << filename << "' não existe.\n";
            system("pause");
            return EXIT_SUCCESS;
        }

        if ( !fileReaded ) {
            leECriaGrafo(filename);
        }

        // If not enough parameters have been passed, set the default input filenames.
    } else {
        //        filename = "instancias/grafo_1000_1.txt";
        filename = "instancias/grafo_teste.txt";
        outputFilename = "output.txt";
    }

    // This menu will be printed until the user press a invalid digit.
    while ( true ) {
        imprimeTitulo();
        imprimeSeparador();

        cout << "[1] Le o arquivo e (re)cria o grafo.\n";
        cout << "[2] Gera o arquivo de saida.\n";
        cout << "[3] Inserir No.\n";
        cout << "[4] Remove No.\n";
        cout << "[5] Insere aresta.\n";
        cout << "[6] Remove aresta.\n";
        cout << "[7] Grau do No.\n";
        cout << "[8] k-regular.\n";
        cout << "[9] Ordem do grafo.\n";
        cout << "[10] O Grafo e trivial?\n";
        cout << "[11] O Grafo e vazio?\n";
        cout << "[12] Vizinhanca aberta do no.\n";
        cout << "[13] Vizinhanca fechada do no.\n";
        cout << "[14] O Grafo e um multigrafo?\n";
        cout << "[15] O Grafo e um grafo completo?\n";
        cout << "[16] O Grafo e bipartido? \n"; // Não e necessário.
        cout << "[17] Caminho mais curto do no A para o B. \n";
        cout << "[18] Grau do Grafo.\n";
        cout << "[19] O No A e adjacente ao no B?\n";
        cout << "[20] INDUCED SUBGRAPH by a node set. \n";
        cout << "[21] Grafo complementar. \n"; // Não e necessário.
        cout << "[22] O Grafo e conectado? \n";
        cout << "[23] O no A e um no de articulacao? \n";
        cout << "[24] A aresta A e uma ponte? \n";
        cout << "[25] Sequencia de graus do Grafo.\n";
        cout << "[26] Busca em profundidade (DFS).\n";
        cout << "[27] Busca em largura (BFS). \n";
        cout << "[28] Componente conexas dos nos A e B.\n";
        cout << "[29] DIRECT TRANSITIVE CLOSURE of the node A. \n";
        cout << "[30] INDIRECT TRANSITIVE CLOSURE of the node A. \n";
        cout << "[31] Ordenacao topológica. \n";
        cout << "[32] O menor caminho de todos os nos a todos os nos. (FLOYD) \n";
        cout << "[33] Componentes conexas do grafo. \n";
        //        cout << "[34] Produto cartesiano entre dois grafos. <<<<<<<<<<<<<<<<<<<<\n";
        cout << "[35] Arvore geradora minima. (using PRIM) \n";
        cout << "[36] Arvore geradora minima. (using KRUSKAL) \n";
        cout << "[37] K-conectividade do grafo. \n";
        cout << "[38] O Grafo e um grafo euleriano? \n";
        cout << "[39] Cardinalidade do grafo (numero de arestas).";
        imprimeSeparador();
        cout << "[40] Informacoes do grafo obtido com Floyd.\n";
        cout << "[44] Nos e suas informacoes.\n";
        cout << "[55] Estrutura do grafo.\n";
        cout << "[66] Subgrafo induzido por vizinhanca fechada.\n";
        cout << "[77] O grafo e um digrafo?";
        imprimeSeparador();
        cout << "[999] Problema do Caixeiro Viajante (PCV ou TSp em ingles).";
        imprimeSeparador();

        // Mostra os alertas ao usuarios
        if ( alert != "-1" && alert != "" ) {
            cout << "\\\\\\\n---> ALERTA: " << alert << "\n///\n";
            alert = "";
        }

        imprimeSeparador();
        cout << "------------------- [Outra tecla] EXIT. ------------------";
        imprimeSeparador();

        if ( !fileReaded ) {
            option = "1";
        } else {
            cout << "Por favor, selecione uma opcao...: ";
            cin >> option;
            cin.ignore();
        }

        if ( option == "1" ) {
            alert = leECriaGrafo(filename);
            fileReaded = true;
        } else if ( option == "2" ) {
            alert = gerarArquivoDeUmGrafo(grafo, outputFilename);
        } else if ( option == "3" ) {
            alert = insereNo();
        } else if ( option == "4" ) {
            alert = removeNo();
        } else if ( option == "5" ) {
            alert = insereAresta();
        } else if ( option == "6" ) {
            alert = removeAresta();
        } else if ( option == "7" ) {
            alert = grauNo();
        } else if ( option == "8" ) {
            alert = grafo->kRegularidade();
        } else if ( option == "9" ) {
            alert = ordemGrafo();
        } else if ( option == "10" ) {
            alert = isTrivial();
        } else if ( option == "11" ) {
            alert = isNULL();
        } else if ( option == "12" ) {
            alert = vizinhacaAberta();
        } else if ( option == "13" ) {
            alert = vizinhacaFechada();
        } else if ( option == "14" ) {
            alert = isMultigrafo();
        } else if ( option == "15" ) {
            alert = isCompleto();
        } else if ( option == "16" ) {
            alert = isBipartite();
        } else if ( option == "17" ) {
            alert = menorCaminho();
        } else if ( option == "18" ) {
            alert = graphDegree();
        } else if ( option == "19" ) {
            alert = isAdjacentes();
        } else if ( option == "20" ) {
            alert = grafoInduzidoPorUmConjuntoNos();
        } else if ( option == "21" ) {
            alert = grafoComplementar();
        } else if ( option == "22" ) {
            alert = isConnected();
        } else if ( option == "23" ) {
            alert = noDeArticulacao();
        } else if ( option == "24" ) {
            alert = getAllPontes();
        } else if ( option == "25" ) {
            alert = sequenceDegree();
        } else if ( option == "26" ) {
            alert = buscaProfundidade();
        } else if ( option == "27" ) {
            alert = buscaLargura();
        } else if ( option == "28" ) {
            alert = ComponenteConexaDeAeB();
        } else if ( option == "29" ) {
            alert = fechoTransitivoDiretoDeUmNo();
        } else if ( option == "30" ) {
            alert = fechoTransitivoIndiretoDeUmNo();
        } else if ( option == "31" ) {
            alert = DAGOrdenacaoTopologica();
        } else if ( option == "32" ) {
            alert = menocaminhoTodosNos();
        } else if ( option == "33" ) {
            alert = componentesConexas();
            //        } else if ( option == "34" ) {
            //            alert = cartesianProductBetweenTwoGraphs();
        } else if ( option == "35" ) {
            alert = agmPRIM();
        } else if ( option == "36" ) {
            alert = agmKRUSKAL();
        } else if ( option == "37" ) {
            alert = KConectividade();
        } else if ( option == "38" ) {
            alert = grafoEuleriano();
        } else if ( option == "39" ) {
            alert = cardinalidadeGrafo();
        } else if ( option == "40" ) {
            alert = informacoesGrafo();
        } else if ( option == "44" ) {
            alert = getInformacoesNo();
        } else if ( option == "55" ) {
            alert = getEstruturaGrafo();
        } else if ( option == "66" ) {
            alert = getSubgrafoInduzidoPorUmaVizinhancaFechada();
        } else if ( option == "77" ) {
            alert = isDigraph();
        } else if ( option == "88" ) {
            cout << "\nOrdem Atual:";
            cout << printNodeVector(grafo->nodeVectorDaSequenciaGrau());
            cout << "\n\nOrdenando......\n";
            cout << printNodeVector(grafo->mergeSortAllNodes());
        } else if ( option == "999" ) {
            alert = rodarAlgoritmoTSP();
        } else {
            system("pause");
            return EXIT_SUCCESS;
        }
    }

    return 0;
}
