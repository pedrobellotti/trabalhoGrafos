#include "Grafo.h"

Aresta::Aresta(){
    peso = 0;
    destino = nullptr;
    proxima = nullptr;
}

Aresta::~Aresta(){
    destino = nullptr;
    proxima = nullptr;
}

int Aresta::getPeso(){
    return peso;
}

void Aresta::setPeso(int p){
    peso = p;
}

Vertice* Aresta::getDestino(){
    return destino;
}

void Aresta::setDestino(Vertice* dest){
    destino = dest;
}

Aresta* Aresta::getProxima(){
    return proxima;
}

void Aresta::setProxima(Aresta* a){
    proxima = a;
}