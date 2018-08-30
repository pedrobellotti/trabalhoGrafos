#include "Grafo.h"

Vertice::Vertice(unsigned int a){
    id = a;
    proximo = nullptr;
    primeiraAresta = nullptr;
    grau = 0;
    grauEntrada = 0;
    grauSaida = 0;
}

Vertice::~Vertice(){
    removeTodasArestas();
}

unsigned int Vertice::getId(){
    return id;
}

unsigned int Vertice::getGrau(){
    return grau;
}

unsigned int Vertice::getGrauEntrada(){
    return grauEntrada;
}

unsigned int Vertice::getGrauSaida(){
    return grauSaida;
}

void Vertice::aumentaGrau(){
    grau++;
}

void Vertice::diminuiGrau(){
    grau--;
}

void Vertice::aumentaGrauEntrada(){
    grauEntrada++;
}

void Vertice::diminuiGrauEntrada(){
    grauEntrada--;
}

void Vertice::aumentaGrauSaida(){
    grauSaida++;
}

void Vertice::diminuiGrauSaida(){
    grauSaida--;
}

void Vertice::setId(unsigned int a){
    id = a;
}

Vertice* Vertice::getProximo(){
    return proximo;
}

void Vertice::setProximo(Vertice* v){
    proximo = v;
}

//Adiciona a aresta na lista de adjacencia do vertice
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

//Remove todas as arestas do vertice
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

Aresta* Vertice::getPrimeira(){
    return primeiraAresta;
}

void Vertice::setPrimeira(Aresta* a){
    primeiraAresta = a;
}
