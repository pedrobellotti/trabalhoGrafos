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
        if(direcionado){ //Se for direcionado adiciona somente a aresta ori->dest
            Aresta* nova = new Aresta();
            nova->setDestino(dest);
            nova->setPeso(peso);
            ori->adicionaArestaAux(nova);
            ori->aumentaGrauSaida();
            dest->aumentaGrauEntrada();
            numeroA++;
        }
        else{ //Se nao for direcionado, adiciona a aresta ori->dest e dest->ori
            Aresta* nova = new Aresta();
            Aresta* equivalente = new Aresta();
            nova->setDestino(dest);
            nova->setPeso(peso);
            equivalente->setDestino(ori);
            equivalente->setPeso(peso);
            ori->adicionaArestaAux(nova);
            dest->adicionaArestaAux(equivalente);
            ori->aumentaGrau();
            dest->aumentaGrau();
            numeroA++;
        }
    }
    else
        cout<<"Erro ao adicionar aresta: algum dos vértices não existe no grafo!"<<endl;
}

//Altera o peso de uma aresta
void Grafo::alteraPeso(unsigned int v1, unsigned int v2, int p){
    Vertice* i = primeiroVertice;
    for (i ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == v1)
            break;
    }
    Aresta* a = i->getPrimeira();
    for (a ; a != nullptr ; a=a->getProxima()){
        if(a->getDestino()->getId() == v2){
            a->setPeso(p);
            return;
        }
    }
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

//Salva o grafo no arquivo txt
void Grafo::salvaGrafo(ofstream& arquivo){
    unsigned short salva;
    do{
        cout << "Deseja salvar o grafo no arquivo de saida? Digite 1 para salvar e 0 para não salvar: ";
        cin >> salva;
    }while(salva != 0 && salva != 1);
    if(salva == 0) //Se o usuario nao quer salvar, sai da funcao
        return;
    else{
        if (ponderado){ //se for ponderado, salva com os pesos
            arquivo<<"\n";
            for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
                arquivo << "Vertice " << i->getId() << "-> ";
                for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima())
                    arquivo << "(" << a->getPeso() << ")" << a->getDestino()->getId() << " | ";
                arquivo<<"\n";
            }
        }
        else
        {
            arquivo<<"\n";
            for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
                arquivo << "Vertice " << i->getId() << "-> ";
                for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima())
                    arquivo << a->getDestino()->getId() << " | ";
                arquivo<<"\n";
            }
        }
    }
}

//Verifica adjacencia entre dois vertices do grafo
bool Grafo::verificaAdjacencia(unsigned int v1, unsigned int v2){
    if(direcionado){ //Se for direcionado procura somente por v2 na lista de v1
        for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
            if(i->getId() == v1){
                for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima())
                    if(a->getDestino()->getId() == v2)
                        return true;
            }
        }
        return false;
    }
    else{ //Se nao for direcionado procura por v2 na lista de v1 e v1 na lista de v2
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
    if(direcionado){
        Vertice* i = primeiroVertice;
        for (i ; i != nullptr ; i=i->getProximo()){
            if(i->getId() == id)
                break;
        }
        Aresta* a = i->getPrimeira();
        while(a != nullptr){
            //Para grafos direcionados, basta diminuir o grau de entrada dos adjacentes,
            //ja que as arestas serao removidas no destrutor do vertice
            a->getDestino()->diminuiGrauEntrada();
            a = a->getProxima();
        }
    }
    else{
        for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
                for(Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima()){
                    if(a->getDestino()->getId() == id){
                        removeAresta(i->getId(),a->getDestino()->getId());
                    }
                }
        }
    }
    //Encontrando o vertice
    //Se o vertice é o primeiro da lista, já exclui
    if(id == primeiroVertice->getId()){
        excluir = primeiroVertice;
        primeiroVertice = primeiroVertice->getProximo();
        if(direcionado)
            numeroA -= excluir->getGrauEntrada() + excluir->getGrauSaida();
        else
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
        if(direcionado)
            numeroA -= excluir->getGrauEntrada() + excluir->getGrauSaida();
        else
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
                    if(direcionado){
                        v->diminuiGrauSaida();
                        excluir->getDestino()->diminuiGrauEntrada();
                    }
                    else
                        v->diminuiGrau();
                    i->setPrimeira(excluir->getProxima());
                    delete excluir;
                    numeroA--;
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
        if(direcionado){
            v->diminuiGrauSaida();
            excluir->getDestino()->diminuiGrauEntrada();
        }
        else{
            v->diminuiGrau();
        }
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
    if(direcionado){
        vector<unsigned int> sequenciaEntrada;
        vector<unsigned int> sequenciaSaida;
        for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
            sequenciaEntrada.push_back(i->getGrauEntrada());
            sequenciaSaida.push_back(i->getGrauSaida());
        }
        stable_sort (sequenciaEntrada.begin(), sequenciaEntrada.end()); //Ordena do menor para o maior
        stable_sort (sequenciaSaida.begin(), sequenciaSaida.end()); //Ordena do menor para o maior
        cout << "Sequencia de graus de entrada: ";
        for (auto it = sequenciaEntrada.rbegin(); it != sequenciaEntrada.rend(); ++it) //Percorre vetor ao contrario
            cout << "[" << *it << "]";
        cout << endl << "Sequencia de graus de saida: ";
        for (auto it = sequenciaSaida.rbegin(); it != sequenciaSaida.rend(); ++it) //Percorre vetor ao contrario
            cout << "[" << *it << "]";
        sequenciaEntrada.clear();
        sequenciaSaida.clear();
    }
    else{
        vector<unsigned int> sequencia;
        for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
            sequencia.push_back(i->getGrau());
        }
        stable_sort (sequencia.begin(), sequencia.end()); //Ordena do menor para o maior
        for (auto it = sequencia.rbegin(); it != sequencia.rend(); ++it) //Percorre vetor ao contrario
            cout << "[" << *it << "]";
        sequencia.clear();
    }
}

//Verifica se o grafo é K-regular
bool Grafo::verificaRegularidade(unsigned int k){
    if(direcionado){
        for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
            if(i->getGrauEntrada() != k || i->getGrauSaida() != k)
                return false;
        }
        return true;
    }
    else{
        for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
            if(i->getGrau() != k)
                return false;
        }
        return true;
    }
}

//Verifica o grau de um vertice
unsigned int Grafo::verificaGrau(unsigned int g){
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == g)
            return i->getGrau();
    }
}

//Verifica o grau de entrada de um vertice
unsigned int Grafo::verificaGrauEntrada(unsigned int g){
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == g)
            return i->getGrauEntrada();
    }
}

//Verifica o grau de saida um vertice
unsigned int Grafo::verificaGrauSaida(unsigned int g){
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == g)
            return i->getGrauSaida();
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

//Verifica se o grafo é bipartido
bool Grafo::verificaBipartido(){
    //Marca todos os vertices como nao visitados (0)
    vector<unsigned short> visitado(numeroV + 1);
    for (Vertice *v = primeiroVertice; v != nullptr; v = v->getProximo())
    {
        visitado[v->getId()] = 0;
    }

    //Marca todos os vertices com 1 e seus adjacentes com 2
    //Para direcionados, é necessario conferir se o vertice ja foi visitado pois as arestas nao sao equivalentes
    if(direcionado){
        for (Vertice *i = primeiroVertice; i != nullptr; i = i->getProximo())
        {
            if(visitado[i->getId() == 0])
                visitado[i->getId()] = 1;
            for (Aresta *a = i->getPrimeira(); a != nullptr; a = a->getProxima())
            {
                if(visitado[a->getDestino()->getId()] == 0)
                    visitado[a->getDestino()->getId()] = 2;
            }
        }
    }
    else{
        for (Vertice *i = primeiroVertice; i != nullptr; i = i->getProximo())
        {
            visitado[i->getId()] = 1;
            for (Aresta *a = i->getPrimeira(); a != nullptr; a = a->getProxima())
            {
                visitado[a->getDestino()->getId()] = 2;
            }
        }
    }

    //Verifica se tem algum vertice com a mesma marca de seus adjacentes, se tiver nao é bipartido
    for (Vertice *i = primeiroVertice; i != nullptr; i = i->getProximo())
    {
        for (Aresta *a = i->getPrimeira(); a != nullptr; a = a->getProxima())
        {
            if (visitado[a->getDestino()->getId()] == visitado[i->getId()])
                return false;
        }
    }
    //Se saiu do for anterior significa que todos os vertices tem marca diferente dos adjacentes, entao o grafo é bipartido
    return true;
}