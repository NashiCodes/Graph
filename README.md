# Especificação do trabalho prático da disciplina Teoria dos Grafos – Semestre 2023-2
Este documento traz a especificação do Trabalho 1, atividade avaliativa do tipo “Trabalho Prático”, e serve de base
para todas as atividades de implementação cobradas ao longo do curso da disciplina DCC059 - Teoria dos Grafos no
semestre letivo 2023-2.
- - - - -
## Objetivo

Desenvolver um Tipo Abstrato de Dados - TAD ou uma Classe que represente grafos simples, orientados e
não orientados, ponderados e não ponderados (nos vértices e arestas) e implemente o conjunto de funcionalidades
apresentados a seguir, detalhadas em sala de aula. O desenvolvimento dos algoritmos aqui requeridos contribui como
base para a resolução das questões das avaliações teóricas.
- - - - -
## Orientações

- O TAD ou Classe deve conseguir representar grafos utilizando lista de adjacência;

- O código deve ser desenvolvido em C++ e não deve usar funções que não sejam nativas da linguagem, pois isso pode levar
  à impossibilidade de compilar seu código no ambiente que será usado para testes;

- Alguns dos elementos avaliados são a clareza e a organização do código (nomes de funções e variáveis, comentários que
  indiquem o propósito das principais funções e procedimentos, inclusive explicando o que são os parâmetros e o retorno,
  em caso de função);

- O programa principal que usará o TAD ou a Classe Grafo deve ler os dados do grafo de entrada (direcionados ou não
  direcionados, ponderados ou não ponderados) a partir de arquivo texto. O formato do arquivo dependerá da origem dos
  dados de entrada. Assim, cabe ao grupo ler o arquivo README que explica a semântica do arquivo de entrada ou, caso não
  haja este arquivo, o grupo deve ler o detalhamento do mesmo na fonte de dados, implementando conforme o caso.
  Entenda-se por formato do arquivo a estrutura em que os dados do grafo aparecem no texto do mesmo. Por exemplo, para
  algumas instâncias teste, o arquivo pode ser apresentado como segue no exemplo, onde se tem um grafo simples, não
  ponderado nos vértices e nas arestas, e não direcionado. Neste exemplo, a primeira linha indica o número de vértices e
  as demais linhas indicam as arestas.

- a informação sobre o tipo de grafo, se direcionado ou não direcionado, deve ser passada ao programa por parâmetro via
  linha de comando, sendo 0 (zero) para não direcionado e 1 (um) para grafos direcionados. Note que o TAD ou Classe deve
  prever a existência de duas formas de inclusão das adjacências, conforme cada caso.

- A informação sobre arestas ponderadas ou não deve ser passada ao programa por parâmetro via linha de
  comando, sendo 0 (zero) para não ponderado nas arestas e 1 (um) para grafos com peso nas arestas.

- A informação sobre a existência de pesos nos vértices deve ser passada ao programa por parâmetro via linha
  de comando, sendo 0 (zero) quando o grafo não é ponderado nos vértices e 1 (um) para grafos com pesos nos
  vértices.

- o nome do arquivo a ser lido deve ser informado ao programa via teclado para a função main (utilizar int main
  (int argc, char ** argv) para passar ao programa todas as informações necessárias ao seu funcionamento;

- cada grupo enviará um único e-mail contendo APENAS os arquivos fonte (extensão c, cc, cpp e h) e os
  arquivos de entrada utilizados (quando o professor não os tiver encaminhado antes);

- o padrão para compilação a ser utilizado (ambiente Linux ou IOS) será g++ *.c* - o execGrupoX. Onde
  “GrupoX” indica a qual grupo o trabalho se refere;

- o padrão para a execução a ser utilizado pelo professor será a linha abaixo, executada em ambiente Linux ou
  IOS:

```bash

g++ *.c* -o execGrupoX && ./execGrupoX <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>

```

- #### Onde:
- < arquivo_entrada> é o nome do arquivo que contém as informações do grafo;
- < arquivo_saida> é o arquivo onde será gravado o grafo armazenado na memória ao término da execução do programa;
- <Opc_Direc> é o parâmetro que indica se o grafo é direcionado ou não;
- < Opc_Peso_Aresta> é o parâmetro que indica se o grafo é ponderado nas arestas ou não;
- < Opc_Peso_Nos> é o parâmetro que indica se o grafo é ponderado nos vértices ou não.

- o grupo deve enviar um ÚNICO arquivo compactado de nome Trabalho_GrupoX.zip para o e-mail indicado em
    sala de aula, cujo assunto da mensagem seja “Trabalho Grafos Grupo X – 2023-2”, onde X indica o número do
    grupo.


    Nota: no arquivo zip deve ter incluso APENAS os arquivos com extensão c, cc, cpp ou h e os arquivos das
    instâncias usadas no experimento.

- - - - -
## Funcionalidades:

 * O programa deve apresentar em tela a saída para as seguintes funcionalidades definidas nas saídas conforme os 
  parâmetros:
    * a) **Parâmetro:** um Id de um vértice de um **grafo direcionado**.
      *   **Saída:** o grau de entrada e o grau de saída do vértice
    * b) **Parâmetro:** um Id de um vértice de um **grafo não direcionado**.
      *   **Saída:** o fecho transitivo indireto deste vértice.
    * c) **Parâmetro:** dois IDs de vértices do grafo.
      *   **Saída:** o caminho mínimo entre estes dois vértices usando algoritmo de Dijkstra. 
    * d) **Parâmetro:** dois IDs de vértices do grafo.
    * e) **Parâmetro:** um subconjunto X de vértices do grafo;
      * **Saída:** uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Prim.
    * f) **Parâmetro:** um subconjunto X de vértices do grafo;
      * **Saída:** uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Kruskal;
    * g) **Parâmetro:** um ID de vértice;
      * **Saída:** a árvore dada pela ordem de caminhamento em profundidade a partir de nó dado parâmetro, 
        destacando as arestas de retorno;
    * h) **Parâmetro:** o próprio grafo acíclico direcionado D;
      * **Saída:** uma ordenação topológica em D ou a informação de que D não é um grafo acíclico direcionado.
    * i) **Parâmetro:** o grafo (direcionado ou não direcionado) ponderado nas arestas
      * **Saída:** O raio, o diâmetro, o centro e a periferia do grafo.
    * j) **Parâmetro:** o grafo não direcionado
      * **Saída:** O conjunto de vértices de articulação.
  
  * Cada uma das saídas das funcionalidades acima deve ser apresentada na tela. Ao final da sua execução e, em 
    seguida, deve-se perguntar ao usuário se o mesmo deseja salvar a saída em arquivo.
  * O programa deve apresentar as funcionalidades na forma de um menu de opções que se repete até que o
    usuário escolha sair do programa.

- - - - -