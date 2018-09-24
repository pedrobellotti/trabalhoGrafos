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
* Parametros: -
*/
Aresta::Aresta(){
    peso = 0;
    destino = nullptr;
    proxima = nullptr;
    equivalente = false;
}

/*
* Destrutor
* Parametros: -
*/
Aresta::~Aresta(){
    destino = nullptr;
    proxima = nullptr;
}

/*
* Retorna o peso da aresta
* Parametros: -
*/
int Aresta::getPeso(){
    return peso;
}

/*
* Muda o peso da aresta
* Parametros: Novo peso
*/
void Aresta::setPeso(int p){
    peso = p;
}

/*
* Retorna o vertice destino da aresta
* Parametros: -
*/
Vertice* Aresta::getDestino(){
    return destino;
}

/*
* Muda o vertice destino da aresta
* Parametros: Ponteiro para o novo vertice de destino
*/
void Aresta::setDestino(Vertice* dest){
    destino = dest;
}

/*
* Retorna a proxima aresta da lista de arestas
* Parametros: -
*/
Aresta* Aresta::getProxima(){
    return proxima;
}

/*
* Muda a proxima aresta da lista
* Parametros: Ponteiro para a aresta
*/
void Aresta::setProxima(Aresta* a){
    proxima = a;
}

/*
* Muda a marcacao de equivalente
* Parametros: Nova marcacao
*/
void Aresta::setEquivalente(bool e){
    equivalente = e;
}

/*
* Retorna a marcacao de equivalente
* Parametros: -
*/
bool Aresta::getEquivalente(){
    return equivalente;
}
