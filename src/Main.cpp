#include <iostream>
#include <fstream>
#include <vector>

#include "TabelaIncidencia.h"

using namespace std;

void LeMatriz(ifstream &input_file, vector<vector<int>> &matriz, int n);
void CriaMatrizIncidencia(vector<vector<int>> &matrizInc, const vector<vector<int>> &matrizAdj, int n);
TabelaIncidencia CriaTabelaIncidencia(const vector<vector<int>> &matrizInc);
void ImprimeMatrizNxN(const vector<vector<int>> &matriz, int n, ofstream &output_file);
void ImprimeMatrizIncidencia(const vector<vector<int>> &matrizInc, int n, int nArestas, ofstream &output_file);

string diretorio = "../input/grafo.txt";

int main()
{
    ifstream input_file(diretorio);

    if(!input_file.is_open()){
        cout << "Não foi possível abrir o arquivo." << endl;
        return 1;
    }

    // Leitura número de vértices
    int n; 
    input_file >> n;

    // Leitura da matriz de adjacência
    vector<vector<int>> matrizAdj;
    LeMatriz(input_file, matrizAdj, n);

    // Leitura da matriz de distância
    vector<vector<int>> matrizDist;
    LeMatriz(input_file, matrizDist, n);

    // Conta número de arestas do grafo
    int nArestas = 0;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(matrizAdj[i][j] == 1) 
                nArestas++;

    // Cria e zera matriz de incidência
    vector<vector<int>> matrizInc(n, vector<int>(nArestas, 0));
    CriaMatrizIncidencia(matrizInc, matrizAdj, n);    

    // Cria tabela de incidência
    TabelaIncidencia tabelaInc = CriaTabelaIncidencia(matrizInc);

    // Imprime no console e escreve no arquivo de saída
    ofstream output_file("../output/saida.txt"); // Abre/cria o arquivo de saída

    cout << "Matriz de Adjacência:" << endl;
    output_file << "Matriz de Adjadência:" << endl;
    ImprimeMatrizNxN(matrizAdj, n, output_file);

    cout << endl << "Matriz de Distância:" << endl;
    output_file << endl << "Matriz de Distância:" << endl;
    ImprimeMatrizNxN(matrizDist, n, output_file);
    
    cout << endl << "Matriz de Incidência:" << endl << "  ";
    output_file << endl << "Matriz de Incidência:" << endl << "  ";
    ImprimeMatrizIncidencia(matrizInc, n, nArestas, output_file);

    cout << endl << "Tabela de Incidência:" << endl;
    output_file << endl << "Tabela de Incidência:" << endl;
    tabelaInc.imprimeTabelaInc(output_file);

    // Fecha arquivo de saída
    output_file.close();

    return 0;
}

void LeMatriz(ifstream &input_file, vector<vector<int>> &matriz, int n)
{
    for(int i = 0; i < n; i++){
        vector<int> linha;

        for(int j = 0; j < n; j++){
            int valor;
            input_file >> valor;
            linha.push_back(valor);
        }
        matriz.push_back(linha);
    }
}

void CriaMatrizIncidencia(vector<vector<int>> &matrizInc, const vector<vector<int>> &matrizAdj, int n)
{
    int indiceAresta = 0; // Coluna atual

    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            if(matrizAdj[i][j] == 1){
                matrizInc[i][indiceAresta] = 1;
                matrizInc[j][indiceAresta] = 1;
                indiceAresta++;
            }
}

TabelaIncidencia CriaTabelaIncidencia(const vector<vector<int>> &matrizInc)
{
    int nLinhas = matrizInc.size();
    int nColunas = matrizInc[0].size();

    TabelaIncidencia tabelaInc(nLinhas, nColunas);

    for(int i = 0; i < nLinhas; i++)
        for(int j = 0; j < nColunas; j++)
            if(matrizInc[i][j] != 0)
                tabelaInc.addElement(i, j, matrizInc[i][j]);
    return tabelaInc;
}

void ImprimeMatrizNxN(const vector<vector<int>> &matriz, int n, ofstream &output_file)
{
    cout << "  ";
    output_file << "  ";
    for(int i = 0; i < n; i++){
        cout << i << " ";
        output_file << i << " ";
    }
    cout << endl;
    output_file << endl;
    for(int i = 0; i < n; i++){
        cout << i << " ";
        output_file << i << " ";
        for(int j = 0; j < n; j++){
            cout << matriz[i][j] << " ";
            output_file << matriz[i][j] << " ";
        }
        cout << endl;
        output_file << endl;
    }
}

void ImprimeMatrizIncidencia(const vector<vector<int>> &matrizInc, int n, int nArestas, ofstream &output_file)
{
    for(int i = 0; i < nArestas/2; i++){
        cout << (char)(97+i) << " ";
        output_file << (char)(97+i) << " ";
    }
    cout << endl;
    output_file << endl;
    for(int i = 0; i < n; i++){
        cout << i << " ";
        output_file << i << " ";
        for(int j = 0; j < nArestas/2; j++){
            cout << matrizInc[i][j] << " ";
            output_file << matrizInc[i][j] << " ";
        }
        cout << endl;
        output_file << endl;
    }
}
