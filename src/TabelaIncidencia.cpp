#include <iostream>
#include <vector>
#include "TabelaIncidencia.h"

using namespace std;

void TabelaIncidencia::addElement(int linha, int coluna, int valor)
{
    No* novoNo = new No(coluna, valor);
    novoNo->prox = linhas[linha];
    linhas[linha] = novoNo;
}

void TabelaIncidencia::imprimeTabelaInc()
{
    for(int i = 0; i < linhas.size(); i++){
        No* atual = linhas[i];
        while(atual != nullptr){
            cout << "(" << i << ", " << (char)(atual->coluna + 97) << ") = " << atual->valor << endl;
            atual = atual->prox;
        }
    }
    cout << endl;
}

