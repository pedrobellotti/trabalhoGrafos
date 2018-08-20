#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Vertice;
class Aresta;
class Grafo;

class Vertice{
    private:
        unsigned int id; //Id do vertice
        unsigned int grau; //Grau do vertice
        Vertice* proximo; //Ponteiro para o proximo vertice na lista
        Aresta* primeiraAresta; //Ponteiro para a primeira aresta da lista de adjacencia
    public:
        Vertice(unsigned int);
        ~Vertice();
        unsigned int getId();
        unsigned int getGrau();
        void diminuiGrau();
        void setId(unsigned int);
        Vertice* getProximo();
        void setProximo(Vertice*);
        void adicionaArestaAux(Aresta*);
        void removeTodasArestas();
        Aresta* getPrimeira();
        void setPrimeira(Aresta*);
};

class Aresta{
    private:
        int peso; //Peso da aresta
        Vertice* destino; //Ponteiro para o vertice de destino
        Aresta* proxima; //Ponteiro para a proxima aresta na lista
    public:
        Aresta();
        ~Aresta();
        int getPeso();
        void setPeso(int);
        Vertice* getDestino();
        void setDestino(Vertice*);
        Aresta* getProxima();
        void setProxima(Aresta*);
};

class Grafo{
    private:
        unsigned int numeroV; //Numero de vertices
        unsigned int numeroA; //Numero de arestas
        Vertice* primeiroVertice; //Ponteiro para o primeiro vertice da lista
        bool direcionado; //Guarda se o grafo é direcionado ou nao
        bool ponderado; //Guarda se o grafo é ponderado ou nao
    public:
        Grafo();
        ~Grafo();
        void alteraPonderado(bool);
        void alteraDirecionado(bool);
        bool getPonderado();
        bool getDirecionado();
        void exibeInformacoes();
        unsigned int getNumeroV();
        Vertice* getPrimeiro();
        void adicionaVertice(unsigned int);
        void adicionaAresta(unsigned int, unsigned int, int);
        void imprimeGrafo();
        bool verificaAdjacencia(unsigned int, unsigned int);
        bool verificaId(unsigned int);
        void removeVertice(unsigned int);
        void removeAresta(unsigned int, unsigned int);
        bool ehCompleto();
        void sequenciaGraus();
        bool verificaRegularidade(unsigned int);
        unsigned int verificaGrau(unsigned int);
};
#endif // GRAFO_H_INCLUDED