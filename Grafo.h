/*
*
* Trabalho DCC 059 - Teoria dos Grafos
* Grupo 02 - Coloração de vértices
* 
* Para compilar o programa, usar g++ versão 7.3.0 (g++ *.cpp -o nomePrograma)
* Para usar outras versões, usar -std=c++11 na hora de compilar! (g++ -std=c++11 *.cpp -o nomePrograma)
* 
*/

#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <stack>
#include <math.h>

using namespace std;
class Vertice;
class Aresta;
class Grafo;

class Vertice{
    private:
        unsigned int id; //Id do vertice
        unsigned int grau; //Grau do vertice (para grafos nao direcionados)
        unsigned int grauEntrada; //Grau de entrada (para grafos direcionados)
        unsigned int grauSaida; //Grau de saida (para grafos direcionados)
        Vertice* proximo; //Ponteiro para o proximo vertice na lista
        Aresta* primeiraAresta; //Ponteiro para a primeira aresta da lista de adjacencia
        bool visitado; //Marcacao se o vertice foi visitado ou nao (usado para buscas em profundidade)
        unsigned int cor; //Cor do vertice (usada na coloracao)
    public:
        Vertice(unsigned int); //Construtor
        ~Vertice(); //Destrutor
        unsigned int getId(); //Retorna id do vertice
        unsigned int getGrau(); //Retorna grau do vertice
        unsigned int getGrauEntrada(); //Retorna grau de entrada do vertice (para digrafos)
        unsigned int getGrauSaida(); //Retorna grau de saida do vertice (para digrafos)
        void aumentaGrau(); //Aumenta o grau do vertice
        void diminuiGrau(); //Diminui o grau do vertice
        void aumentaGrauEntrada(); //Aumenta o grau de entrada do vertice (para digrafos)
        void diminuiGrauEntrada(); //Diminui o grau de entrada do vertice (para digrafos)
        void aumentaGrauSaida(); //Aumenta o grau de saida do vertice (para digrafos)
        void diminuiGrauSaida(); //Diminui o grau de saida do vertice (para digrafos)
        void setId(unsigned int); //Muda a id do vertice
        Vertice* getProximo(); //Retorna o proximo vertice da lista de vertices
        void setProximo(Vertice*); //Muda o ponteiro para o proximo vertice
        void adicionaArestaAux(Aresta*); //Adiciona aresta no vertice
        void removeTodasArestas(); //Remove todas as arestas do vertice
        Aresta* getPrimeira(); //Retorna a primeira aresta da lista de arestas deste vertice (lista de adjacencia)
        void setPrimeira(Aresta*); //Muda a primeira aresta da lista de arestas
        void setVisitado(bool); //Muda a marcacao de visitado
        bool getVisitado(); //Retorna a marcacao de visitado
        void setCor(unsigned int); //Muda a cor do vertice
        unsigned int getCor(); //Retorna a cor do vertice
};

class Aresta{
    private:
        int peso; //Peso da aresta
        Vertice* destino; //Ponteiro para o vertice de destino
        Aresta* proxima; //Ponteiro para a proxima aresta na lista
        bool equivalente; //Guarda se a aresta é a aresta equivalente (para grafos nao direcionados)
    public:
        Aresta(); //Construtor
        ~Aresta(); //Destrutor
        int getPeso(); //Retorna o peso da aresta
        void setPeso(int); //Muda o peso da aresta
        Vertice* getDestino(); //Retorna o vertice destino da aresta
        void setDestino(Vertice*); //Muda o vertice destino da aresta
        Aresta* getProxima(); //Retorna a proxima aresta da lista de arestas
        void setProxima(Aresta*); //Muda a proxima aresta da lista
        void setEquivalente(bool); //Muda a marcacao de equivalente
        bool getEquivalente(); //Retorna a marcacao de equivalente
};

class Grafo{
    private:
        unsigned int numeroV; //Numero de vertices
        unsigned int numeroA; //Numero de arestas
        Vertice* primeiroVertice; //Ponteiro para o primeiro vertice da lista
        bool direcionado; //Guarda se o grafo é direcionado ou nao
        bool ponderado; //Guarda se o grafo é ponderado ou nao
        void limpaVisitados(); //Marca todos os vertices como nao visitados
        void buscaProf(Vertice*); //Busca em profundidade
        void ordenacaoTopologicaAux(stack<unsigned int>&, Vertice*); //Auxiliar para ordenacao topologica
        void descolore(); //Descolore o grafo (muda a cor de todos os vertices para 0)
        Vertice* dijkstraAux(int[]); //Auxiliar para algoritmo de Dijkstra
        Vertice* primAux(int[]); //Auxiliar para algoritmo de Prim
        void unir(vector<int>&,int,int); //Auxiliar para algoritmo de Kruskal
        int buscar(vector<int>,int); //Auxiliar para algoritmo de Kruskal
    public:
        Grafo(); //Construtor
        ~Grafo(); //Destrutor
        void alteraPonderado(bool); //Muda a marcacao de ponderado
        void alteraDirecionado(bool); //Muda a marcacao de direcionado
        bool getPonderado(); //Retorna a marcacao de ponderado
        bool getDirecionado(); //Retorna a marcaco de direcionado
        void exibeInformacoes(); //Mostra as informacoes do grafo na tela
        unsigned int getNumeroV(); //Retorna o numero de vertices do grafo
        void adicionaVertice(unsigned int); //Adiciona um vertice no grafo
        void adicionaAresta(unsigned int, unsigned int, int); //Adiciona uma aresta no grafo
        void alteraPeso(unsigned int, unsigned int, int); //Altera o peso de uma aresta (para grafos ponderados)
        void imprimeGrafo(); //Imprime o grafo na tela
        void salvaGrafo(string); //Salva o grafo no arquivo txt de saida
        bool verificaAdjacencia(unsigned int, unsigned int); //Verifica adjacencia entre dois vertices
        bool verificaId(unsigned int); //Verifica se um vertice com a id passada ja existe no grafo
        void removeVertice(unsigned int); //Remove um vertice do grafo
        void removeAresta(unsigned int, unsigned int); //Remove uma aresta do grafo
        bool ehCompleto(); //Verifica se o grafo é completo
        void sequenciaGraus(); //Imprime a sequencia de graus do grafo
        bool verificaRegularidade(unsigned int); //Verifica a k-regularidade do grafo
        unsigned int verificaGrau(unsigned int); //Verifica o grau de um vertice
        unsigned int verificaGrauEntrada(unsigned int); //Verifica o grau de entrada de um vertice (para digrafos)
        unsigned int verificaGrauSaida(unsigned int); //Verifica o grau de saida de um vertice (para digrafos)
        void vizinhancaAberta(unsigned int); //Imprime a vizinhanca aberta de um vertice
        void vizinhancaFechada(unsigned int); //Imprime a vizinhanca fechada de um vertice
        bool verificaBipartido(); //Verifica se o grafo é bipartido
        void fechoDireto(unsigned int); //Fecho transitivo direto
        void fechoIndireto(unsigned int); //Fecho transitivo indireto
        void ordenacaoTopologica();//Imprime ordenacao topologica do grafo
        void agmKruskal(); //Imprime a arvore geradora minima com algoritmo de Kruskal
        void agmPrim(); //Imprime a arvore geradora minima com o algoritmo de Prim
        void caminhoDijkstra(unsigned int); //Caminho minimo usando algoritmo de Dijkstra
        void caminhoFloyd(); //Caminho minimo usando algoritmo de Floyd
        void imprimeCores();
        unsigned int coloreGuloso(); //Algoritmo de coloracao de vertices guloso
        unsigned int coloreGulosoAleatorio(int,float); //Algoritmo de coloracao de vertices guloso aleatorio
};
#endif // GRAFO_H_INCLUDED
