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
Grafo::Grafo(){
    primeiroVertice = nullptr;
    numeroV = 0;
    numeroA = 0;
    direcionado = false;
    ponderado = false;
}

/*
* Destrutor
* Parametros: -
*/
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

/*
* Muda a marcacao de ponderado
* Parametros: Nova marcacao
*/
void Grafo::alteraPonderado(bool p){
    ponderado = p;
}

/*
* Muda a marcacao de direcionado
* Parametros: Nova marcacao
*/
void Grafo::alteraDirecionado(bool d){
    direcionado = d;
}

/*
* Retorna a marcacao de ponderado
* Parametros: -
*/
bool Grafo::getPonderado(){
    return (ponderado ? true : false);
}

/*
* Retorna a marcacao de direcionado
* Parametros: -
*/
bool Grafo::getDirecionado(){
    return (direcionado ? true : false);
}

/*
* Mostra as informacoes do grafo na tela
* Parametros: -
*/
void Grafo::exibeInformacoes(){
    cout << "Número de vértices: " << numeroV << endl;
    cout << "Número de arestas: " << numeroA << endl;
    cout << "Grafo direcionado: " << (direcionado ? "Sim" : "Não") << endl;
    cout << "Grafo ponderado: " << (ponderado ? "Sim" : "Não") << endl;
}

/*
* Retorna o numero de vertices do grafo
* Parametros: -
*/
unsigned int Grafo::getNumeroV(){
    return numeroV;
}

/*
* Adiciona um vertice ao grafo
* Parametros: ID do novo vertice que será adicionado
*/
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

/*
* Adiciona uma aresta ao grafo
* Parametros: IDs dos vertices que formam a aresta, peso da aresta
*/
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
            equivalente->setEquivalente(true); //Nova nao precisa de setequivalente porque o padrao já é false
            numeroA++;
        }
    }
    else
        cout<<"Erro ao adicionar aresta: algum dos vértices não existe no grafo!"<<endl;
}

/*
* Altera o peso de uma aresta
* Parametros: IDs dos vertices que formam a aresta, novo peso da aresta
*/
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

/*
* Imprime o grafo na tela
* Parametros: -
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

/*
* Salva o grafo no arquivo txt de saida
* Parametros: Nome do arquivo de saida
*/
void Grafo::salvaGrafo(string nomeArquivo){
    unsigned short salva;
    do{
        cout << "Deseja salvar o grafo neste estado no arquivo de saida? Isso irá sobrescrever o arquivo atual." << endl;
        cout << "Digite 1 para salvar e 0 para não salvar: ";
        cin >> salva;
    }while(salva != 0 && salva != 1);
    if(salva == 0) //Se o usuario nao quer salvar, sai da funcao
        return;
    else{
        ofstream arquivo;
        arquivo.open(nomeArquivo);
        string tipoAresta; //Representacao das arestas no arquivo de saida
        string tipoGrafo; //Representacao do tipo do grafo no arquivo de saida
        if(direcionado){
            tipoGrafo = "digraph {\n";
            tipoAresta = " -> ";
        }
        else{
            tipoGrafo = "graph {\n";
            tipoAresta = " -- ";
        }
        if (ponderado){ //se for ponderado, salva com os pesos
            arquivo<<tipoGrafo;
            for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
                for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima()){
                    if(!a->getEquivalente()) //Nao salva a aresta equivalente (aresta 1-2 é a mesma de 2-1)
                        arquivo << i->getId() << tipoAresta << a->getDestino()->getId() << "[label=" << a->getPeso() << "]" << ";\n";
                }
            }
            arquivo<<"}\n";
        }
        else
        {
            arquivo<<tipoGrafo;
            for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
                for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima()){
                    if(!a->getEquivalente()) //Nao salva a aresta equivalente (aresta 1-2 é a mesma de 2-1)
                        arquivo << i->getId() << tipoAresta << a->getDestino()->getId() << ";\n";
                }
            }
            arquivo<<"}\n";
        }
        arquivo.close();
        cout << endl;
        cout << "Grafo salvo, caso o arquivo de saida tenha extensão .dot é possivel gerar a imagem do grafo usando GraphViz:" << endl;
        cout << "Para grafos pequenos, use 'dot -Tpng -O <nome_arquivo.dot>'." << endl;
        cout << "Caso o grafo seja muito grande, use 'sfdp -x -Goverlap=scale -Tpng <nome_arquivo.dot> > saida.png'." << endl;
    }
}

/*
* Verifica adjacencia entre dois vertices do grafo
* Parametros: IDs dos vertices
*/
bool Grafo::verificaAdjacencia(unsigned int v1, unsigned int v2){
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == v1){
            for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima())
                if(a->getDestino()->getId() == v2)
                    return true;
        }
    }
    return false;
}

/*
* Verifica se o vertice existe no grafo ou nao
* Parametros: ID do vertice
*/
bool Grafo::verificaId(unsigned int id){
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == id)
            return true;
    }
    return false;
}

/*
* Remove um vertice e suas arestas do grafo
* Parametros: ID do vertice
*/
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

/*
* Remove uma aresta ao grafo
* Parametros: IDs dos vertices que formam a aresta
*/
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

/*
* Verifica se o grafo é completo
* Parametros: -
*/
bool Grafo::ehCompleto(){
    if(numeroA == (numeroV*(numeroV-1)/2))
        return true;
    else
        return false;
}

/*
* Imprime a sequencia de graus do grafo
* Parametros: -
*/
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

/*
* Verifica se o grafo é K-regular
* Parametros: Número K
*/
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

/*
* Retorna o grau de um vertice
* Parametros: ID do vértice
*/
unsigned int Grafo::verificaGrau(unsigned int g){
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == g)
            return i->getGrau();
    }
}

/*
* Retorna o grau de entrada de um vertice
* Parametros: ID do vértice
*/
unsigned int Grafo::verificaGrauEntrada(unsigned int g){
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == g)
            return i->getGrauEntrada();
    }
}

/*
* Retorna o grau de saida de um vertice
* Parametros: ID do vértice
*/
unsigned int Grafo::verificaGrauSaida(unsigned int g){
    for (Vertice* i = primeiroVertice ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == g)
            return i->getGrauSaida();
    }
}

/*
* Imprime a vizinhanca aberta de um vertice
* Parametros: ID do vértice
*/
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

/*
* Imprime a vizinhanca fechada de um vertice
* Parametros: ID do vértice
*/
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

/*
* Verifica se o grafo é bipartido
* Parametros: -
*/
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

/*
* Marca todos os vertices como nao visitados (importante para fazer buscas em sequencia)
* Parametros: -
*/
void Grafo::limpaVisitados(){
     for (Vertice* v = primeiroVertice; v != nullptr; v=v->getProximo()){
        v->setVisitado(false);
    }
}

/*
* Busca em profundidade a partir de um vertice (nao percorre todos os vértices se o grafo nao for conexo)
* Parametros: Vértice inicial
*/
void Grafo::buscaProf(Vertice* v){
    v->setVisitado(true);
    for (Aresta* a = v->getPrimeira(); a != nullptr; a=a->getProxima()){
        if(!a->getDestino()->getVisitado())
            buscaProf(a->getDestino());
    }
}

/*
* Imprime o fecho transitivo direto
* Parametros: ID do vértice
*/
void Grafo::fechoDireto(unsigned int id){
    Vertice* v = nullptr;
    //Procura o vertice com a id passada
    for (v = primeiroVertice; v != nullptr; v=v->getProximo()){
        if(v->getId() == id)
            break;
    }
    //Marca todos os vertices como nao visitados (caso isso nao seja feito, o resultado da busca ficara errado)
    limpaVisitados();
    //Realiza a busca em profundidade usando o vertice como inicio
    buscaProf(v);
    //Verifica quais vertices foram visitados e os imprime
    cout << "Fecho transitivo direto a partir do vertice " << id << ": ";
    for (v = primeiroVertice; v != nullptr; v=v->getProximo()){
        if(v->getVisitado())
            cout << v->getId() << " | ";
    }
    cout << endl;
}

/*
* Imprime o fecho transitivo indireto
* Parametros: ID do vértice
*/
void Grafo::fechoIndireto(unsigned int id){
    Vertice* v = nullptr;
    Vertice* n = nullptr;
    //Procura o vertice com a id passada
    for (n = primeiroVertice; n != nullptr; n=n->getProximo()){
        if(n->getId() == id)
            break;
    }
    cout << "Fecho transitivo indireto do vertice " << id << ": ";
    for (v = primeiroVertice; v != nullptr; v=v->getProximo()){
        limpaVisitados(); //Marca todos os vertices como nao visitados
        buscaProf(v); //Faz a busca em profundidade a partir do vertice
        /*Se na busca em profundidade a partir do vertice v o vertice com a id passada foi atingido,
        entao o vertice v faz parte do fecho transitivo indireto*/
        if(n->getVisitado())
            cout << v->getId() << " | ";
    }
}

/*
* Auxiliar para ordenacao topologica - similar a busca em profundidade, a unica diferenca sendo que
* os vertices só sao adicionados na pilha após todos seus vizinhos terem sido visitados
* Parametros: Endereço para a pilha (criada na funcao principal), ponteiro para o vertice inicial
*/
void Grafo::ordenacaoTopologicaAux(stack<unsigned int> &pilha, Vertice* ver){
    ver->setVisitado(true);
    for (Aresta* a = ver->getPrimeira(); a != nullptr; a=a->getProxima()){
        if(!a->getDestino()->getVisitado())
            ordenacaoTopologicaAux(pilha, a->getDestino());
    }
    pilha.push(ver->getId()); //Coloca o vertice na pilha apos seus adjacentes terem sido visitados
}

/*
* Ordenacao topologica do grafo
* Parametros: -
*/
void Grafo::ordenacaoTopologica(){
    stack<unsigned int> pilha; //Cria a pilha para usar na funcao auxiliar
    limpaVisitados(); //Marca todos os vertices como nao visitados
    for (Vertice*v = primeiroVertice; v!=nullptr; v=v->getProximo()){
        if(!v->getVisitado())
            ordenacaoTopologicaAux(pilha, v); //Chama a funcao auxiliar para todos os vertices do grafo
    }

    cout << "Ordenação topológica do grafo: ";
    //Imprime a pilha em ordem (imprime o primeiro elemento e depois o remove da pilha)
    while(!pilha.empty()){
        cout << pilha.top() << " | ";
        pilha.pop();
    }
    cout<<endl;
}

/*
* Imprime a arvore geradora minima do grafo usando algoritmo de Kruskal
* Parametros: -
*/
void Grafo::agmKruskal(){
    //Ainda nao feito
    return;
}

/*
* Imprime a arvore geradora minima do grafo usando algoritmo de Prim
* Parametros: -
*/
void Grafo::agmPrim(){
    //Ainda nao feito
    return;
}

/*
* Função auxiliar para algoritmo de Dijkstra - encontra a menor distancia entre vértices não visitados
* Parametros: Vetor de distâncias
*/
Vertice* Grafo::dijkstraAux(int dist[]){
    int menorDist = __INT_MAX__;
    Vertice* menorId = nullptr;

    for (Vertice*v = primeiroVertice; v!=nullptr; v=v->getProximo()){
        if(v->getVisitado() == false && dist[v->getId()] <= menorDist){
            menorDist = dist[v->getId()];
            menorId = v;
        }
    }
    return menorId;
}

/*
* Caminho minimo entre dois vertices usando algoritmo de Dijkstra
* Parametros: IDs dos dois vertices
*/
void Grafo::caminhoDijkstra(unsigned int origem){
    //Limpa a marcacao de visitados de todos os vertices
    limpaVisitados();

    //Cria vetor de distancias
    int dist[numeroV+1]; //+1 porque os ids dos vertices comecam a partir de 1

    //Inicializando o vetor de distancias com valores infinitos
    for (int i = 0; i<numeroV+1; i++)
        dist[i] = __INT_MAX__;

    //Colocando o valor 0 na posição da origem (distancia para o proprio vértice é 0)
    dist[origem] = 0;

    //Itera para todos os vértices
    for (int cont = 1; cont < numeroV; cont++){
        //Pega o vertice de menor distancia entre o vertice e um que ainda nao esteja na solução
        Vertice* u = dijkstraAux(dist);

        //Seta o vertice encontrado como já visitado
        u->setVisitado(true);

        //Atualiza o valor de distancias para todos os vértice adjacentes ao vértice escolhido
        for (Aresta* a = u->getPrimeira(); a!=nullptr; a=a->getProxima()){
            if(a->getDestino()->getVisitado() == false && dist[u->getId()] != __INT_MAX__ && dist[u->getId()] + a->getPeso() < dist[a->getDestino()->getId()]){
                dist[a->getDestino()->getId()] = dist[u->getId()] + a->getPeso();
            }
        }
    }
    //Imprime os resultados
    cout << endl << "Caminhos mínimos usando algoritmo de Dijkstra." << endl;
    cout << "Vértice de origem: " << origem << endl;
    for (int j = 1; j<numeroV+1; j++){
        cout << "Custo do caminho para o vértice " << j << ": "<< dist[j] << endl;
    }
}

/*
* Caminho minimo entre dois vertices usando algoritmo de Floyd
* Parametros: IDs dos dois vertices
*/
void Grafo::caminhoFloyd(unsigned int origem, unsigned int destino){
    //Ainda nao feito
    return;
}

/* ---------- ALGORITMOS DE COLORAÇÃO DOS VÉRTICES DO GRAFO ---------- */

/*
* Algumas instancias para testes: https://cse.unl.edu/~tnguyen/npbenchmarks/graphcoloring.html 
* Remover o "e" antes das arestas (o find and replace faz isso rapido)
*/

/*
* Descolore o grafo (muda a cor de todos os vertices para 0)
* Parametros: -
*/
void Grafo::descolore(){
    for (Vertice* v = primeiroVertice; v != nullptr; v=v->getProximo()){
        v->setCor(0);
    }
}

/*
* Comparador para ordenacao da lista de candidatos (nao tem Grafo:: porque nao é uma funçao do grafo, só serve para ordenação)
* Parametros: IDs dos vertices
*/
bool comparador(Vertice* g1, Vertice* g2){
    if(g1->getGrau() < g2->getGrau())
        return true;
    else
        return false; 
}

/*
* Imprime as cores de todos os vértices do grafo
* Parametros: -
*/
void Grafo::imprimeCores(){
    for (Vertice* v = primeiroVertice; v != nullptr; v=v->getProximo()){
        cout << "Vertice " << v->getId() << " - Cor: " << v->getCor() << endl;
    }
}

/*
* Faz a coloracao dos vertices do grafo usando o algoritmo guloso
* Parametros: -
*/
unsigned int Grafo::coloreGuloso(){
    //Descolore o grafo
    descolore();
    //Cria o vetor de candidatos que sera ordenado pelo grau
    vector<Vertice*> vertices;
    //Vetor de marcaco de vertices ja coloridos, cores usadas/disponiveis (inicializa todas com false - nao usada)
    vector<bool> colorido;
    //Preenche os vetores
    Vertice* v = nullptr;
    for (v = primeiroVertice; v != nullptr; v=v->getProximo()){
        vertices.push_back(v);
        colorido.push_back(false);
    }
    //Ordena o vetor pelo grau dos vertices
    sort(vertices.begin(), vertices.end(), comparador);

    //Faz a coloracao dos vertices
    vertices[0]->setCor(1); //Seta o primeiro vertice como cor 1
    //Itera pelos outros vertices
    for (int i = 1; i < vertices.size(); i++){
        //Marca todas as cores dos adjacentes já coloridos como nao disponiveis
        Aresta* a = nullptr;
        for(a = vertices[i]->getPrimeira(); a != nullptr; a=a->getProxima()){
            if(a->getDestino()->getCor() != 0){
                colorido[a->getDestino()->getCor()] = true;
            }
        }
        
        //Procura a primeira cor disponivel, comeca de 1 porque cor = 0 significa nao colorido
        unsigned int cor;
        for(cor = 1; cor < colorido.size(); cor++){
            if(colorido[cor] == false){
                //Seta a cor encontrada para o vertice da iteracao atual e sai do for
                vertices[i]->setCor(cor);
                break;
            }
        }        

        //Reseta a marcacao de vertices coloridos para a proxima iteracao
        for(a = vertices[i]->getPrimeira(); a != nullptr; a=a->getProxima()){
            if(a->getDestino()->getCor() != 0){
                colorido[a->getDestino()->getCor()] = false;
            }
        }
    }

    //Calcula o total de cores usadas
    unsigned int totalCores = 0;
    for (v = primeiroVertice; v != nullptr; v=v->getProximo()){
        if(v->getCor() > totalCores)
            totalCores = v->getCor();
    }
    return totalCores;
}

/*
* Faz a coloracao dos vertices do grafo usando o algoritmo guloso aleatorio
* Parametros: Seed (semente) para gerar o numero aleatorio e porcentagem dos valores que serao escolhidos
*/
unsigned int Grafo::coloreGulosoAleatorio(int seed, float alfa){
    //Descolore o grafo
    descolore();
    //Cria o vetor de candidatos que sera ordenado pelo grau
    vector<Vertice*> vertices;
    //Vetor de marcaco de vertices ja coloridos, cores usadas/disponiveis (inicializa todas com false - nao usada)
    vector<bool> colorido;
    //Preenche os vetores
    Vertice* v = nullptr;
    for (v = primeiroVertice; v != nullptr; v=v->getProximo()){
        vertices.push_back(v);
        colorido.push_back(false);
    }
    //Ordena o vetor pelo grau dos vertices
    sort(vertices.begin(), vertices.end(), comparador);
    //Seta a seed para o numero aleatorio
    srand(seed);
    int random; //Numero aleatorio

    //Itera pela lista de vertices até ficar vazia (todos os vertices coloridos)
    while(!vertices.empty()){
        //Gera um numero aleatorio entre 0 e a porcentagem do tamanho do vetor
        random = fmod(rand(), (vertices.size()*alfa));
        
        //Marca todas as cores dos adjacentes já coloridos como nao disponiveis
        Aresta* a = nullptr;
        for(a = vertices[random]->getPrimeira(); a != nullptr; a=a->getProxima()){
            if(a->getDestino()->getCor() != 0){
                colorido[a->getDestino()->getCor()] = true;
            }
        }

        //Procura a primeira cor disponivel, comeca de 1 porque cor = 0 significa nao colorido
        unsigned int cor;
        for(cor = 1; cor < colorido.size(); cor++){
            if(colorido[cor] == false){
                //Seta a cor encontrada para o vertice da iteracao atual e sai do for
                vertices[random]->setCor(cor);
                break;
            }
        }

        //Reseta a marcacao de vertices coloridos para a proxima iteracao
        for(a = vertices[random]->getPrimeira(); a != nullptr; a=a->getProxima()){
            if(a->getDestino()->getCor() != 0){
                colorido[a->getDestino()->getCor()] = false;
            }
        }

        //Remove o vertice atual da lista de vertices, já que ele foi colorido
        if(vertices.size() == 1)
            vertices.erase(vertices.begin());
        else
            vertices.erase(vertices.begin() + random);
    }

    //Calcula o total de cores usadas
    unsigned int totalCores = 0;
    for (v = primeiroVertice; v != nullptr; v=v->getProximo()){
        if(v->getCor() > totalCores)
            totalCores = v->getCor();
    }
    return totalCores;
}
