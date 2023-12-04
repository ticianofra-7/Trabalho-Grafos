#ifndef TABELAINCIDENCIA_H
#define TABELAINCIDENCIA_H

#include <vector>
#include "No.h"

using namespace std;

class TabelaIncidencia
{
    private:
        vector<No*> linhas; // As linhas são um vetor de ponteiros para os nós
    
    public:
        TabelaIncidencia(){};
        TabelaIncidencia(int nLinhas, int nColunas) : linhas(nLinhas, nullptr){}
        void AdicionarElemento(int linha, int coluna, int valor);
        void Imprimir(ofstream &output_file);
};

#endif // TABELAINCIDENCIA_H
