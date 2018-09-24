/*
*
* Trabalho DCC 059 - Teoria dos Grafos
* Grupo 02 - Coloração de vértices
* 
* Para compilar o programa, usar g++ versão 7.3.0 (g++ *.cpp -o nomePrograma)
* Para usar outras versões, usar -std=c++11 na hora de compilar! (g++ -std=c++11 *.cpp -o nomePrograma)
* 
*/

#include "Grafo.h"

/*
* Construtor
* Parametros: ID do vertice
*/
Vertice::Vertice(unsigned int a){
    id = a;
    proximo = nullptr;
    primeiraAresta = nullptr;
    grau = 0;
    grauEntrada = 0;
    grauSaida = 0;
    visitado = false;
    cor = 0;
}

/*
* Destrutor
* Parametros: -
*/
Vertice::~Vertice(){
    removeTodasArestas();
}

/*
* Retorna a ID do vertice
* Parametros: -
*/
unsigned int Vertice::getId(){
    return id;
}

/*
* Retorna o grau do vértice
* Parametros: -
*/
unsigned int Vertice::getGrau(){
    return grau;
}

/*
* Retorna o grau de entrada do vértice
* Parametros: -
*/
unsigned int Vertice::getGrauEntrada(){
    return grauEntrada;
}

/*
* Retorna o grau de saida do vértice
* Parametros: -
*/
unsigned int Vertice::getGrauSaida(){
    return grauSaida;
}

/*
* Aumenta o grau do vértice
* Parametros: -
*/
void Vertice::aumentaGrau(){
    grau++;
}

/*
* Diminui o grau do vértice
* Parametros: -
*/
void Vertice::diminuiGrau(){
    grau--;
}

/*
* Aumenta o grau de entrada do vértice
* Parametros: -
*/
void Vertice::aumentaGrauEntrada(){
    grauEntrada++;
}

/*
* Diminui o grau de entrada do vértice
* Parametros: -
*/
void Vertice::diminuiGrauEntrada(){
    grauEntrada--;
}

/*
* Aumenta o grau de saida do vértice
* Parametros: -
*/
void Vertice::aumentaGrauSaida(){
    grauSaida++;
}

/*
* Diminui o grau de saida do vértice
* Parametros: -
*/
void Vertice::diminuiGrauSaida(){
    grauSaida--;
}

/*
* Muda a ID do vértice
* Parametros: Nova ID
*/
void Vertice::setId(unsigned int a){
    id = a;
}

/*
* Retorna o proximo vértice da lista de vértices
* Parametros: -
*/
Vertice* Vertice::getProximo(){
    return proximo;
}

/*
* Muda o ponteiro para o próximo vértice
* Parametros: Ponteiro para o próximo vértice
*/
void Vertice::setProximo(Vertice* v){
    proximo = v;
}

/*
* Adiciona a aresta na lista de adjacencia do vertice
* Parametros: Ponteiro para a nova aresta
*/
void Vertice::adicionaArestaAux(Aresta* nova){
    Aresta* a = primeiraAresta;
    if(a == nullptr)
        primeiraAresta = nova;
    else{
        //Chega na ultima aresta da lista
        for(a; a->getProxima() != nullptr; a=a->getProxima());
        a->setProxima(nova);
    }
}

/*
* Remove todas as arestas do vertice
* Parametros: -
*/
void Vertice::removeTodasArestas(){
    Aresta* aux = primeiraAresta;
    Aresta* prox = nullptr;
    while(aux != nullptr){
        prox = aux->getProxima();
        delete aux;
        aux = prox;
    }
    primeiraAresta = nullptr;
    grau = 0;
    grauEntrada = 0;
    grauSaida = 0;
}

/*
* Retorna a primeira aresta da lista de arestas deste vertice (lista de adjacencia)
* Parametros: -
*/
Aresta* Vertice::getPrimeira(){
    return primeiraAresta;
}

/*
* Muda a primeira aresta da lista de arestas
* Parametros: Ponteiro para a aresta
*/
void Vertice::setPrimeira(Aresta* a){
    primeiraAresta = a;
}

/*
* Muda a marcacao de visitado
* Parametros: Nova marcacao
*/
void Vertice::setVisitado(bool v){
    visitado = v;
}

/*
* Retorna a marcacao de visitado
* Parametros: -
*/
bool Vertice::getVisitado(){
    return visitado;
}

/*
* Muda a cor do vertice
* Parametros: Nova cor
*/
void Vertice::setCor(unsigned int c){
    cor = c;
}

/*
* Retorna a cor do vertice
* Parametros: -
*/
unsigned int Vertice::getCor(){
    return cor;
}