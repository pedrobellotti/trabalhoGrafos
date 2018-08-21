#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Grafo.h"

using namespace std;

void criaGrafo(Grafo* g1, string nomeArquivo){
    ifstream arquivo(nomeArquivo);
    string linha;
    unsigned int numV, a1, a2 = 0;
    int peso = -1;
    if (arquivo.good()){ //Verifica se o arquivo esta aberto
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
        if(peso != -1) //Se a aresta tiver peso, o grafo é ponderado
            g1->alteraPonderado(true);
        else
            g1->alteraPonderado(false);
    }
    else{ //Caso o arquivo nao esteja aberto, mostra um erro.
        cout << "Erro ao abrir arquivo do grafo: " << nomeArquivo << endl;
        exit(1);
    }
}

int main (int argc, char* argv[]){
    //Confere se o numero de parametros está correto
    if(argc != 3){
        cout << "Número de parâmetros incorreto! Use: "<<argv[0]<<" <arquivo_entrada.txt> <arquivo_saida.txt>" << endl;
        return 0;
    }
    //Guardando os nomes dos arquivos
    string nomeEntrada = argv[1];
    string nomeSaida = argv[2];
    //Criando arquivo de saida
    ofstream arquivoSaida;
    arquivoSaida.open(nomeSaida);
    arquivoSaida << "--Inicio do arquivo de saida--\n";
    arquivoSaida << "Arquivo de entrada: " + nomeEntrada + "\n";
    Grafo* g = new Grafo();
    criaGrafo(g, nomeEntrada);
    unsigned short dir;
    do{
        cout << "Informe se o grafo é direcionado, digite 0 para não direcionado ou 1 para direcionado: ";
        cin >> dir;
    }while(dir != 0 && dir != 1);
    if(dir == 0)
        g->alteraDirecionado(false);
    else
        g->alteraDirecionado(true);

    //Variaveis do menu
    unsigned int ver, ver1, ver2, k;
    int peso;
    unsigned short menu;
    do{
        cout << endl;
        cout << "---------------------Menu---------------------" << endl;
        cout << "[0]. Sair." << endl;
        cout << "[1]. Apresentar informacoes do grafo." << endl;
        cout << "[2]. Imprimir o grafo." << endl;
        cout << "[3]. Adicionar um vértice." << endl;
        cout << "[4]. Remover um vértice e suas arestas." << endl;
        cout << "[5]. Adicionar uma aresta." << endl;
        cout << "[6]. Remover uma aresta." << endl;
        cout << "[7]. Verificar adjacência de dois vértices." << endl;
        cout << "[8]. Verificar o grau de um vértice." << endl;
        cout << "[9]. Verificar se o grafo é completo." << endl;
        cout << "[10]. Apresentar a sequência de graus do grafo." << endl;
        cout << "[11]. Apresentar a ordem do grafo." << endl;
        cout << "[12]. Verificar se o grafo é K-regular." << endl;
        cout << "----------------------------------------------" << endl;
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
                if(g->verificaId(ver1) && g->verificaId(ver2))
                    g->adicionaAresta(ver1,ver2,peso);
                else
                    cout << "Algum dos vértices informados não existe no grafo!" << endl;
                break;
            }
            case 6: {
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                if(g->verificaAdjacencia(ver1,ver2))
                    g->removeAresta(ver1,ver2);
                else
                    cout << "A aresta não existe no grafo!" << endl;
                break;
            }
            case 7: {
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
            case 8: {
                cout << "Digite a ID do vértice: ";
                cin >> ver;
                if(!g->verificaId(ver)){//Sai da funcao caso o vertice nao exista
                    cout << "Vértice não existe no grafo!" << endl;
                    break;
                }
                else
                    cout << "O grau do vértice é: " << g->verificaGrau(ver) << endl;
                break;
            }
            case 9: {
                if(g->ehCompleto())
                    cout << "O grafo é completo." << endl;
                else
                    cout << "O grafo não é completo." << endl;
                break;
            }
            case 10: {
                g->sequenciaGraus();
                break;
            }
            case 11: {
                cout << "Ordem do grafo: " << g->getNumeroV() << endl;
                break;
            }
            case 12: {
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
        }
    }while (menu != 0);
    arquivoSaida << "\n--Fim do arquivo de saida--";
    arquivoSaida.close();
    delete g;
    return 0;
}
