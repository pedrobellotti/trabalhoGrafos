#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Grafo.h"

using namespace std;

void criaGrafo(Grafo* g1, string nomeArquivo){
    ifstream arquivo(nomeArquivo);
    string linha;
    unsigned int numV, a1, a2, peso = 0;
    if (arquivo.good()){ //Verifica se o arquivo esta aberto
        arquivo >> numV; //Le a primeira linha com o numero de vertices
        for (int i = 1; i<=numV; i++){
            g1->adicionaVertice(i); //Adiciona o numero lido de vertices
        }
        getline(arquivo, linha);
        while (getline(arquivo, linha)) //Continua lendo o arquivo
        {
            istringstream iss(linha);
            iss >> a1 >> a2 >> peso;
            g1->adicionaAresta(a1,a2,peso);
        }
        if(peso == 0) //Se o peso for 0 a aresta nao precisa existir em um grafo ponderado
            g1->alteraPonderado(false);
        else
            g1->alteraPonderado(true);
    }
    else{ //Caso o arquivo nao esteja aberto, mostra um erro.
        cout << "Erro ao abrir arquivo do grafo: " << nomeArquivo << endl;
        exit(1);
    }
}


int main (){
    Grafo* g = new Grafo();
    criaGrafo(g, "testes.txt");
    unsigned short menu;
    do{
        cout << endl;
        cout << "--------------------Menu--------------------" << endl;
        cout << "[0]. Sair." << endl;
        cout << "[1]. Imprimir informacoes do grafo." << endl;
        cout << "[2]. Imprimir o grafo." << endl;
        cout << "[3]. Adicionar um vértice." << endl;
        cout << "[4]. Remover um vértice e suas arestas." << endl;
        cout << "[5]. Adicionar uma aresta." << endl;
        cout << "[6]. Remover uma aresta." << endl;
        cout << "[7]. Verificar adjacência de dois vértices." << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Digite a opcão desejada: ";
        cin >> menu;
        switch (menu){
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
                unsigned int ver;
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
                unsigned int ver;
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
                unsigned int ver1, ver2, p = 0;
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                if(g->getPonderado()){
                    cout << "Digite o peso da aresta: ";
                    cin >> p;
                }
                g->adicionaAresta(ver1,ver2,p);
                break;
            }
            case 6: {
                unsigned int ver1, ver2;
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                g->removeAresta(ver1,ver2);
                break;
            }
            case 7: {
                unsigned int ver1, ver2;
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
        }
    }while (menu != 0);
    return 0;
}