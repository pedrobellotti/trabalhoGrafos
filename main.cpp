/*
*
* Trabalho DCC 059 - Teoria dos Grafos
* Grupo 02 - Coloração de vértices
* 
* Para compilar o programa, usar g++ versão 7.3.0 (g++ *.cpp -o nomePrograma)
* Para usar outras versões, usar -std=c++11 na hora de compilar! (g++ -std=c++11 *.cpp -o nomePrograma)
* 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Grafo.h"
#include <random>

using namespace std;

/*
* Cria o grafo a partir do arquivo texto de entrada
* Parametros: Ponteiro para o grafo (vazio), nome do arquivo de entrada
*/
void criaGrafo(Grafo* g1, string nomeArquivo){
    ifstream arquivo(nomeArquivo);
    string linha;
    unsigned int numV, a1, a2 = 0;
    int peso = 0;
    if (arquivo.good()){ //Verifica se o arquivo esta aberto
        cout << "Lendo grafo do arquivo "  << nomeArquivo << " ..." << endl;
        arquivo >> numV; //Le a primeira linha com o numero de vertices
        for (int i = 1; i<=numV; i++){ //Comeca do 1 porque o vertice 0 nao existe nos arquivos txt
            g1->adicionaVertice(i); //Adiciona o numero lido de vertices
        }
        getline(arquivo, linha);
        while (getline(arquivo, linha)) //Continua lendo o arquivo
        {
            istringstream iss(linha);
            iss >> a1 >> a2 >> peso;
            g1->adicionaAresta(a1,a2,peso);
        }
        if(peso != 0) //Se a aresta tiver peso, o grafo é ponderado
            g1->alteraPonderado(true);
        else
            g1->alteraPonderado(false);
    }
    else{ //Caso o arquivo nao esteja aberto, mostra um erro.
        cout << "Erro ao abrir arquivo do grafo: " << nomeArquivo << endl;
        exit(1);
    }
}

/*
* Realiza as funcoes principais do programa
* Parametros: Nome do arquivo de entrada, arquivo de saida
*/
int main (int argc, char* argv[]){
    //Confere se o numero de parametros está correto
    if(argc != 3){
        cout << "Número de parâmetros incorreto! Use: "<<argv[0]<<" <arquivo_entrada.txt> <arquivo_saida.txt>" << endl;
        return 0;
    }
    //Guardando os nomes dos arquivos
    string nomeEntrada = argv[1];
    string nomeSaida = argv[2];
    
    Grafo* g = new Grafo();
    unsigned short dir;
    do{
        cout << "Informe se o grafo é direcionado, digite 0 para não direcionado ou 1 para direcionado: ";
        cin >> dir;
    }while(dir != 0 && dir != 1);
    if(dir == 0)
        g->alteraDirecionado(false);
    else
        g->alteraDirecionado(true);
    criaGrafo(g, nomeEntrada);

    //Variaveis do menu
    unsigned int ver, ver1, ver2, k;
    int peso;
    unsigned short menu;
    do{
        cout << endl;
        cout << "--------------------------------------Menu--------------------------------------" << endl;
        cout << "[0]. Sair." << endl;
        cout << "[1]. Apresentar informacoes do grafo." << endl;
        cout << "[2]. Imprimir o grafo." << endl;
        cout << "[3]. Adicionar um vértice." << endl;
        cout << "[4]. Remover um vértice e suas arestas." << endl;
        cout << "[5]. Adicionar uma aresta." << endl;
        cout << "[6]. Remover uma aresta." << endl;
        cout << "[7]. Alterar o peso de uma aresta." << endl;
        cout << "[8]. Verificar adjacência de dois vértices." << endl;
        cout << "[9]. Verificar o grau de um vértice." << endl;
        cout << "[10]. Verificar se o grafo é completo." << endl;
        cout << "[11]. Apresentar a sequência de graus do grafo." << endl;
        cout << "[12]. Apresentar a ordem do grafo." << endl;
        cout << "[13]. Verificar se o grafo é K-regular." << endl;
        cout << "[14]. Apresentar a vizinhança aberta de um vértice." << endl;
        cout << "[15]. Apresentar a vizinhança fechada de um vértice." << endl;
        cout << "[16]. Verificar se o grafo é bipartido." << endl;
        cout << "[17]. Apresentar o fecho transitivo direto de um vértice." << endl;
        cout << "[18]. Apresentar o fecho transitivo indireto de um vértice." << endl;
        cout << "[19]. Apresentar a ordenação topológica do grafo." << endl;
        cout << "[20]. Apresentar uma árvore geradora mínima usando algoritmo de Kruskal." << endl;
        cout << "[21]. Apresentar uma árvore geradora mínima usando algoritmo de Prim." << endl;
        cout << "[22]. Apresentar o custo do caminho mínimo entre dois vértices com algoritmo de Dijkstra." << endl;
        cout << "[23]. Apresentar o custo do caminho mínimo entre dois vértices com algoritmo de Floyd." << endl;
        cout << "[24]. Imprimir as cores dos vértices do grafo." << endl;
        cout << "[25]. Fazer a coloração dos vértices do grafo usando algoritmo guloso." << endl;
        cout << "[26]. Fazer a coloração dos vértices do grafo usando algoritmo guloso aleatório." << endl;
        cout << "[27]. Fazer a coloração dos vértices do grafo usando algoritmo guloso aleatório reativo." << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "Digite a opcão desejada: ";
        cin >> menu;
        switch (menu){
            default:{
                cout << "Opcão inválida!" << endl;
                break;
            }
            case 0: {
                break;
            }
            case 1: {
                g->exibeInformacoes();
                break;
            }
            case 2: {
                g->imprimeGrafo();
                g->salvaGrafo(nomeSaida);
                break;
            }
            case 3: {
                cout << "Digite a ID do vértice para adicionar: ";
                cin >> ver;
                if(g->verificaId(ver)){//Sai da funcao caso o vertice já exista
                    cout << "Vértice já existe no grafo!" << endl;
                    break;
                }
                else
                    g->adicionaVertice(ver);
                    g->salvaGrafo(nomeSaida);
                break;
            }
            case 4: {
                cout << "Digite a ID do vértice para remover: ";
                cin >> ver;
                if(!g->verificaId(ver)){//Sai da funcao caso o vertice nao exista
                    cout << "Vértice não existe no grafo!" << endl;
                    break;
                }
                else
                    g->removeVertice(ver);
                    g->salvaGrafo(nomeSaida);
                break;
            }
            case 5: {
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                if(g->getPonderado()){
                    cout << "Digite o peso da aresta: ";
                    cin >> peso;
                }
                if(g->verificaId(ver1) && g->verificaId(ver2)){
                    g->adicionaAresta(ver1,ver2,peso);
                    g->salvaGrafo(nomeSaida);
                }
                else
                    cout << "Algum dos vértices informados não existe no grafo!" << endl;
                break;
            }
            case 6: {
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                if(g->verificaAdjacencia(ver1,ver2)){
                    if(g->getDirecionado()){
                        g->removeAresta(ver1,ver2);
                        g->salvaGrafo(nomeSaida);
                        break;
                    }
                    else{
                        g->removeAresta(ver1,ver2);
                        g->removeAresta(ver2,ver1);
                        g->salvaGrafo(nomeSaida);
                        break;
                    }
                }
                else
                    cout << "A aresta não existe no grafo!" << endl;
                break;
            }
            case 7: {
                if(!g->getPonderado()){
                    cout << "O grafo não é ponderado!" << endl;
                    break;
                }
                else{
                    cout << "Digite a ID do vértice origem: ";
                    cin >> ver1;
                    cout << "Digite a ID do vértice destino: ";
                    cin >> ver2;
                    if(g->verificaAdjacencia(ver1,ver2)){
                        cout << "Digite novo o peso para a aresta: ";
                        cin >> peso;
                        if(g->getDirecionado()){
                            g->alteraPeso(ver1, ver2, peso);
                            g->salvaGrafo(nomeSaida);
                            break;
                        }
                        else{ //Se nao for direcionado o peso da equivalente tambem deve ser alterado
                            g->alteraPeso(ver1, ver2, peso);
                            g->alteraPeso(ver2, ver1, peso);
                            g->salvaGrafo(nomeSaida);
                            break;
                        }
                    }
                    else
                        cout << "A aresta não existe no grafo!" << endl;
                }
                break;
            }
            case 8: {
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                if(g->verificaAdjacencia(ver1,ver2))
                    cout << "Os vértices são adjacentes.";
                else
                    cout << "Os vértices não são adjacentes.";
                break;
            }
            case 9: {
                cout << "Digite a ID do vértice: ";
                cin >> ver;
                if(!g->verificaId(ver)){//Sai da funcao caso o vertice nao exista
                    cout << "Vértice não existe no grafo!" << endl;
                    break;
                }
                else{
                    if(g->getDirecionado()){
                        cout << "O grau de entrada do vértice é: " << g->verificaGrauEntrada(ver) << endl;
                        cout << "O grau de saida do vértice é: " << g->verificaGrauSaida(ver) << endl;
                    }
                    else
                        cout << "O grau do vértice é: " << g->verificaGrau(ver) << endl;
                }
                break;
            }
            case 10: {
                if(g->ehCompleto())
                    cout << "O grafo é completo." << endl;
                else
                    cout << "O grafo não é completo." << endl;
                break;
            }
            case 11: {
                g->sequenciaGraus();
                break;
            }
            case 12: {
                cout << "Ordem do grafo: " << g->getNumeroV() << endl;
                break;
            }
            case 13: {
                cout << "Digite o numero de K: ";
                cin >> k;
                if(g->verificaRegularidade(k)){
                    cout << "O grafo é " << k << "-regular." << endl;
                    break;
                }
                else
                    cout << "O grafo não é " << k << "-regular." << endl;
                break;
            }
            case 14:{
                cout << "Digite a ID do vértice: ";
                cin >> ver;
                if(!g->verificaId(ver)){//Sai da funcao caso o vertice nao exista
                    cout << "Vértice não existe no grafo!" << endl;
                    break;
                }
                else
                    g->vizinhancaAberta(ver);
                break;
            }
            case 15:{
                cout << "Digite a ID do vértice: ";
                cin >> ver;
                if(!g->verificaId(ver)){//Sai da funcao caso o vertice nao exista
                    cout << "Vértice não existe no grafo!" << endl;
                    break;
                }
                else
                    g->vizinhancaFechada(ver);
                break;
            }
            case 16:{
                if(g->verificaBipartido())
                    cout << "O grafo é bipartido." << endl;
                else
                    cout << "O grafo não é bipartido." << endl;
                break;
            }
            case 17:{
                //Verifica se o grafo é direcionado
                if(!g->getDirecionado()){
                    cout << "Essa função só pode ser executada em grafos direcionados!" << endl;
                    break;    
                }
                cout << "Digite a ID do vértice: ";
                cin >> ver;
                if(!g->verificaId(ver)){//Sai da funcao caso o vertice nao exista
                    cout << "Vértice não existe no grafo!" << endl;
                    break;
                }
                else
                    g->fechoDireto(ver);
                break;
            }
            case 18:{
                //Verifica se o grafo é direcionado
                if(!g->getDirecionado()){
                    cout << "Essa função só pode ser executada em grafos direcionados!" << endl;
                    break;    
                }
                cout << "Digite a ID do vértice: ";
                cin >> ver;
                if(!g->verificaId(ver)){//Sai da funcao caso o vertice nao exista
                    cout << "Vértice não existe no grafo!" << endl;
                    break;
                }
                else
                    g->fechoIndireto(ver);
                break;
            }
            case 19:{
                //Verifica se o grafo é direcionado
                if(!g->getDirecionado()){
                    cout << "Essa função só pode ser executada em grafos direcionados!" << endl;
                    break;    
                }
                g->ordenacaoTopologica();
                break;
            }
            case 20:{
                if(g->getPonderado())
                    g->agmKruskal();
                else
                    cout << "Essa função só pode ser executada em grafos ponderados!" << endl;
                break;
            }
            case 21:{
                if(g->getPonderado())
                    g->agmPrim();
                else
                    cout << "Essa função só pode ser executada em grafos ponderados!" << endl;
                break;
            }
            case 22:{
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                if(g->verificaId(ver1)){
                    g->caminhoDijkstra(ver1);
                }
                else
                    cout << "O vértice informado não existe no grafo!" << endl;
                break;
            }
            case 23:{
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                if(g->verificaId(ver1) && g->verificaId(ver2)){
                    g->caminhoFloyd(ver1,ver2);
                }
                else
                    cout << "Algum dos vértices informados não existe no grafo!" << endl;
                break;
            }
            case 24:{
                if(!g->getDirecionado())
                    g->imprimeCores();
                else
                    cout << "Essa função só pode ser executada em grafos não direcionados!" << endl;
                break;
            }
            case 25:{
                if(!g->getDirecionado())
                    cout << "Total de cores usadas com algoritmo guloso: " << g->coloreGuloso() << endl;
                else
                    cout << "Essa função só pode ser executada em grafos não direcionados!" << endl;
                break;
            }
            case 26:{
                if(!g->getDirecionado()){
                    int seed;
                    cout << "Digite a seed que será usada: ";
                    cin >> seed;
                    unsigned int melhorResultado = g->getNumeroV();
                    unsigned int resultadoAtual;
                    float vetAlfas[3] = {0.10, 0.20, 0.30};
                    //Itera 500 vezes para cada alfa (10%,20%,30%)
                    for (int alfa = 0; alfa < 3; alfa++){
                        cout << "Usando alfa = " << vetAlfas[alfa] << endl;
                        for(int iteracoes = 0; iteracoes < 500; iteracoes++){
                            resultadoAtual = g->coloreGulosoAleatorio(seed, vetAlfas[alfa]);
                            if(resultadoAtual < melhorResultado)
                                melhorResultado = resultadoAtual;
                        }
                        // Ao terminar as 500 iteracoes para o alfa atual, imprime o melhor resultado
                        cout << "Total de cores usadas com o alfa atual: " << melhorResultado << endl;
                        cout << endl;
                        melhorResultado = g->getNumeroV(); //Resetando melhor resultado para o proximo alfa
                    }
                }
                else
                    cout << "Essa função só pode ser executada em grafos não direcionados!" << endl;
                break;
            }
            case 27:{
                if(!g->getDirecionado()){
                    int seedReativo;
                    cout << "Digite a seed que será usada: ";
                    cin >> seedReativo;

                    float alfas[10] = {0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50};
                    int somaAlfa[10] = {0};
                    int numIteracoes[10] = {0};
                    double media[10] = {0};
                    double probabilidade[10] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
                    double somatorio = 0.0;
                    int posRandom = 0;
                    double somaProb[10] = {0};
                    double random = 0;
                    srand(seedReativo);
                    int it = 0;

                    //Iterando 2000 vezes
                    for(int i=0; i<2000; i++){
                       //Somando as probabilidades para escolher uma posicao
                       somaProb[0] = probabilidade[0];
                        for (it = 1; it < 10; it++)
                            somaProb[it] = somaProb[it-1] + probabilidade[it];
                        
                        //Gerando um numero aleatorio entre 0 e valor maximo da soma
                        srand(seedReativo + i);
                        random = fmod(rand(),somaProb[9]);
                        //Escolhendo um alfa baseado na probabilidade
                        for (it = 0; it < 10; it++){
                            if(random < somaProb[it])
                                break;
                        }
                        posRandom = it;

                        //Constroi a solucao com o alfa escolhido
                        somaAlfa[posRandom] += g->coloreGulosoAleatorio(seedReativo, alfas[posRandom]);
                        numIteracoes[posRandom]++;
                        media[posRandom] = somaAlfa[posRandom]/numIteracoes[posRandom];

                        //Atualizando a probabilidade de escolha do alfa escolhido
                        somatorio += pow((1 / media[posRandom]), 10);
                        probabilidade[posRandom] = (pow((1 / media[posRandom]), 10)) / somatorio;
                    }

                    //Imprimindo informacoes de cada alfa
                    cout << "----- Informações individuais de cada alfa -----" << endl;
                    for (int k = 0; k < 10; k++){
                        cout << endl;
                        cout << "Alfa: " << alfas[k] << endl;
                        cout << "   Total de vezes escolhido: " << numIteracoes[k] << endl;
                        cout << "   Somatório de cores de todas as soluções do alfa: " << somaAlfa[k] << endl;
                        cout << "   Média de cores usadas: " << media[k] << endl;
                    }
                    cout << "--------------------------------------------------" << endl;

                    /*
                        Verificando qual o melhor alfa e usando ele para colorir o grafo

                        O melhor alfa é escolhido usando os critérios:
                        - Maior quantidade de iteracoes (logo, teve maior probabilidade de escolha)
                        - Melhor média de cores utilizadas
                        - Menor número total de cores utilizadas (logo, no geral as soluções foram melhores)
                    */
                    double prob = probabilidade[0];      //Probabilidade de escolha do melhor alfa
                    float melhorAlfa = alfas[0]; //Melhor alfa
                    unsigned int resultadoMelhorAlfa; //Resultado da coloracao usando o alfa
                    for (int i = 0; i < 10; i++){
                        if (prob < probabilidade[i]){
                            prob = probabilidade[i];
                            melhorAlfa = alfas[i];
                        }
                    }
                    resultadoMelhorAlfa = g->coloreGulosoAleatorio(seedReativo, melhorAlfa);

                    //Imprimindo os resultados
                    cout << endl;
                    cout << "Melhor alfa: " << melhorAlfa << endl;
                    cout << "Melhor solução do alfa: " << resultadoMelhorAlfa << endl;
                    cout << endl;
                }
                else
                    cout << "Essa função só pode ser executada em grafos não direcionados!" << endl;
                break;
            }
        }
        if(menu != 0){
            cout << endl << "--> Pressione ENTER para continuar <--" << endl;
            cin.ignore();
            cin.get();
        }
    }while (menu != 0);
    delete g; //Deleta o grafo
    return 0;
}
