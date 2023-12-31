#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "TabelaIncidencia.h"

using namespace std;

void TabelaIncidencia::AdicionarElemento(int linha, int coluna, int valor)
{
    No* novoNo = new No(coluna, valor);
    novoNo->prox = linhas[linha];
    linhas[linha] = novoNo;
}

void TabelaIncidencia::Imprimir(ofstream &output_file)
{
    for(int i = 0; i < linhas.size(); i++){
        No* atual = linhas[i];
        while(atual != nullptr){
            cout << "(" << i << ", " << (char)(atual->coluna + 97) << ") = " << setw(2) << atual->valor << endl;
            output_file << "(" << i << ", " << (char)(atual->coluna + 97) << ") = " << setw(2) << atual->valor << endl;
            atual = atual->prox;
        }
    }
}

