#include "Grafo.h"

Grafo::Grafo(){
    primeiroVertice = nullptr;
    numeroV = 0;
    numeroA = 0;
    direcionado = false;
    ponderado = false;
}

Grafo::~Grafo(){
    Vertice* aux = primeiroVertice;
    Vertice* prox = nullptr;
    while(aux != nullptr){
        prox = aux->getProximo();
        delete aux;
        aux = prox;
    }
    numeroV = 0;
    numeroA = 0;
    primeiroVertice = nullptr;
}

void Grafo::alteraPonderado(bool p){
    ponderado = p;
}

void Grafo::alteraDirecionado(bool d){
    direcionado = d;
}

bool Grafo::getPonderado(){
    return (ponderado ? true : false);
}

bool Grafo::getDirecionado(){
    return (direcionado ? true : false);
}

void Grafo::exibeInformacoes(){
    cout << "Número de vértices: " << numeroV << endl;
    cout << "Número de arestas: " << numeroA << endl;
    cout << "Grafo direcionado: " << (direcionado ? "Sim" : "Não") << endl;
    cout << "Grafo ponderado: " << (ponderado ? "Sim" : "Não") << endl;
}

unsigned int Grafo::getNumeroV(){
    return numeroV;
}

Vertice* Grafo::getPrimeiro(){
    return primeiroVertice;
}

//Adiciona um vertice ao grafo
void Grafo::adicionaVertice(unsigned int idnovo){
    Vertice* novo = new Vertice(idnovo);
    Vertice* v = primeiroVertice;
    if(v == nullptr)
        primeiroVertice = novo;
    else{
        //Chega no ultimo vertice da lista
        for(v; v->getProximo() != nullptr; v=v->getProximo());
        v->setProximo(novo);
    }
    numeroV++;
}

//Adiciona uma aresta ao grafo
void Grafo::adicionaAresta(unsigned int idorigem, unsigned int iddestino, int peso){
    Vertice* ori = nullptr;
    Vertice* dest = nullptr;
    //Encontrando a id
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == idorigem)
            ori = i;
        else if(i->getId() == iddestino)
            dest = i;
    }
    //Se os vertices foram encontrados, cria a aresta e adiciona no vertice origem
    if(ori != nullptr && dest != nullptr){
        if(direcionado){
            Aresta* nova = new Aresta();
            nova->setDestino(dest);
            nova->setPeso(peso);
            ori->adicionaArestaAux(nova);
            numeroA++;
        }
        else{
            Aresta* nova = new Aresta();
            Aresta* equivalente = new Aresta();
            nova->setDestino(dest);
            nova->setPeso(peso);
            equivalente->setDestino(ori);
            equivalente->setPeso(peso);
            ori->adicionaArestaAux(nova);
            dest->adicionaArestaAux(equivalente);
            numeroA++;
        }
    }
    else
        cout<<"Erro ao adicionar aresta: algum dos vértices não existe no grafo!"<<endl;
}

//Imprime a lista de adjacencia de cada vertice
/*
*   vO - vértice origem / vD - vértice destino / p - peso
*   O grafo é impresso da segunte forma:
*   Vertice vO-> (p)vD | (p)vD | (p)vD ...
*/
void Grafo::imprimeGrafo(){
    if (ponderado){ //se for ponderado, imprime com os pesos
        for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
            cout << "Vertice " << i->getId() << "-> ";
            for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima())
                cout << "(" << a->getPeso() << ")" << a->getDestino()->getId() << " | ";
            cout<<endl;
        }
    }
    else
    {
        for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
            cout << "Vertice " << i->getId() << "-> ";
            for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima())
                cout << a->getDestino()->getId() << " | ";
            cout<<endl;
        }
    }
}

//Verifica adjacencia entre dois vertices do grafo
bool Grafo::verificaAdjacencia(unsigned int v1, unsigned int v2){
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == v1){
            for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima())
                if(a->getDestino()->getId() == v2)
                    return true;
        }
        if(i->getId() == v2){
            for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima())
                if(a->getDestino()->getId() == v1)
                    return true;
        }
    }
    return false;
    if(direcionado){
        //fazer para grafos direcionados
    }
}

//Verifica se o vertice existe no grafo ou nao
bool Grafo::verificaId(unsigned int id){
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == id)
            return true;
    }
    return false;
}

//Remove um vertice e suas arestas do grafo
void Grafo::removeVertice(unsigned int id){
    Vertice* excluir = nullptr;
    Vertice* anterior = nullptr;
    //Removendo o vértice da lista de adjacencia dos outros vertices
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
            for(Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima()){
                if(a->getDestino()->getId() == id){
                    removeAresta(i->getId(),a->getDestino()->getId());
                }
            }
    }
    //Encontrando o vertice
    //Se o vertice é o primeiro da lista, já exclui
    if(id == primeiroVertice->getId()){
        excluir = primeiroVertice;
        primeiroVertice = primeiroVertice->getProximo();
        numeroA -= excluir->getGrau();
        delete excluir;
        numeroV--;
        return;
    }
    //Procura o vertice na lista
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getProximo()->getId() == id){
            excluir = i->getProximo();
            anterior = i;
            break;
        }
    }
    //Se o vertice nao foi encontrado, nao faz nada
    if(excluir == nullptr){
        cout << "Vértice não encontrado!" << endl;
        return;
    }
    else{
        anterior->setProximo(excluir->getProximo());
        numeroA -= excluir->getGrau();
        delete excluir;
        numeroV--;
        return;
    }
}

//Remove uma aresta do grafo
void Grafo::removeAresta(unsigned int v1, unsigned int v2){
    Aresta* excluir = nullptr;
    Aresta* anterior = nullptr;
    Vertice* v = nullptr;
    //Encontrando a aresta
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == v1){
            v = i; //Vertice para diminuir o grau
            for(Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima()){
                //Se a aresta é a primeira da lista, já exclui
                if(a->getDestino()->getId() == v2){
                    excluir = i->getPrimeira();
                    i->setPrimeira(excluir->getProxima());
                    delete excluir;
                    numeroA--;
                    v->diminuiGrau();
                    return;
                }
                if(a->getProxima()->getDestino()->getId() == v2){
                    excluir = a->getProxima();
                    anterior = a;
                    break;
                }
            }
        }
    }
    //Se a aresta nao foi encontrada, nao faz nada
        if(excluir == nullptr){
        cout << "Aresta não encontrada!" << endl;
        return;
    }
    else{
        anterior->setProxima(excluir->getProxima());
        v->diminuiGrau();
        delete excluir;
        numeroA--;
        return;
    }
}

//Verifica se o grafo é completo
bool Grafo::ehCompleto(){
    if(numeroA == (numeroV*(numeroV-1)/2))
        return true;
    else
        return false;
}

//Apresenta a sequencia de graus do grafo
void Grafo::sequenciaGraus(){
    vector<unsigned int> sequencia;
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        sequencia.push_back(i->getGrau());
    }
    stable_sort (sequencia.begin(), sequencia.end()); //Ordena do menor para o maior
    for (auto it = sequencia.rbegin(); it != sequencia.rend(); ++it) //Percorre vetor ao contrario
        cout << "[" << *it << "]";
    sequencia.clear();
}

//Verifica se o grafo é K-regular
bool Grafo::verificaRegularidade(unsigned int k){
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getGrau() != k)
            return false;
    }
    return true;
}

//Verifica o grau de um vertice
unsigned int Grafo::verificaGrau(unsigned int g){
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == g)
            return i->getGrau();
    }
}

//Vizinhanca aberta de um vertice
void Grafo::vizinhancaAberta(unsigned int id){
    cout << "Vizinhanca aberta do vertice: ";
    Vertice* i = primeiroVertice;
     for (i ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == id)
            break;
    }
    for (Aresta* a = i->getPrimeira(); a != nullptr; a=a->getProxima())
        cout << a->getDestino()->getId() << " ";
}

//Vizinhanca fechada de um vertice
void Grafo::vizinhancaFechada(unsigned int id){
    cout << "Vizinhanca fechada do vertice: ";
    Vertice* i = primeiroVertice;
     for (i ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == id)
            break;
    }
    cout << i->getId() << " ";
    for (Aresta* a = i->getPrimeira(); a != nullptr; a=a->getProxima())
        cout << a->getDestino()->getId() << " ";
}