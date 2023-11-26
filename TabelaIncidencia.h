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
        TabelaIncidencia(int nLinhas, int nColunas) : linhas(nLinhas, nullptr){}
        void addElement(int linha, int coluna, int valor);
        void imprimeTabelaInc();
};

#endif // TABELAINCIDENCIA_H
