#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "TabelaIncidencia.h"

using namespace std;

void LerMatriz(ifstream &input_file, vector<vector<int>> &matriz, int n);
vector<vector<int>> CriarMatrizAdjacencia(const vector<vector<int>> &matrizDist);
vector<vector<int>> CriarMatrizIncidencia(const vector<vector<int>> &matrizDist, int tipoGrafo);
TabelaIncidencia CriarTabelaIncidencia(const vector<vector<int>> &matrizInc);
void ImprimirMatrizNxN(const vector<vector<int>> &matriz, int n, ofstream &output_file);
void ImprimirMatrizIncidencia(const vector<vector<int>> &matrizInc, int n, ofstream &output_file);
void Imprimir(const vector<vector<int>> &matrizAdj, const vector<vector<int>> &matrizInc, TabelaIncidencia *tabelaInc, int n, ofstream &output_file);

int main()
{
    // Abre o arquivo de entrada
    ifstream input_file("../input/grafo.txt");

    // Abre/cria o arquivo de saída
    ofstream output_file("../output/saida.txt");

    if (!input_file.is_open())
    {
        cout << "Não foi possível abrir o arquivo." << endl;
        return 1;
    }

    // Leitura número de vértices
    int n;
    input_file >> n;

    // Matriz a ser lida (adjadência ou distância)
    vector<vector<int>> matriz;
    LerMatriz(input_file, matriz, n);

    vector<vector<int>> matrizAdj;
    vector<vector<int>> matrizInc;
    TabelaIncidencia tabelaInc;

    int tipoGrafo; // 1 - Simples (matriz lida = adjacência), 2 - Digrafo não-valorado (matriz lida = adjacência), 3 - Digrafo valorado (matriz lida = distância)
    int opcao;

    cout << "[1] Grafo Simples, não-valorado" << endl;
    cout << "[2] Digrafo Simples, não-valorado" << endl;
    cout << "[3] Digrafo Simples, valorado" << endl << endl;
    cin >> opcao;
    cout << endl;

    switch (opcao)
    {
        case 1:
            tipoGrafo = 1;
            matrizInc = CriarMatrizIncidencia(matriz, tipoGrafo);
            tabelaInc = CriarTabelaIncidencia(matrizInc);

            // Imprime no console e escreve no arquivo
            Imprimir(matriz, matrizInc, &tabelaInc, n, output_file);
            break;
        case 2:
            tipoGrafo = 2;            
            matrizInc = CriarMatrizIncidencia(matriz, tipoGrafo);
            tabelaInc = CriarTabelaIncidencia(matrizInc);

            // Imprime no console e escreve no arquivo
            Imprimir(matriz, matrizInc, &tabelaInc, n, output_file);            
            break;
        case 3:
            tipoGrafo = 3;
            matrizAdj = CriarMatrizAdjacencia(matriz);
            matrizInc = CriarMatrizIncidencia(matriz, tipoGrafo);
            tabelaInc = CriarTabelaIncidencia(matrizInc);

            // Imprime no console e escreve no arquivo
            cout << "Matriz de Distância:" << endl;
            output_file << "Matriz de Distância:" << endl;
            ImprimirMatrizNxN(matriz, n, output_file);
            Imprimir(matriz, matrizInc, &tabelaInc, n, output_file);            
            break;
        default:
            cout << "Erro: Entrada inválida!" << endl;
            break;
    }
    cout << endl;

    // Fecha arquivo de saída
    output_file.close();

    return 0;
}

void LerMatriz(ifstream &input_file, vector<vector<int>> &matriz, int n)
{
    for (int i = 0; i < n; i++)
    {
        vector<int> linha;

        for (int j = 0; j < n; j++)
        {
            int valor;
            input_file >> valor;
            linha.push_back(valor);
        }
        matriz.push_back(linha);
    }
}

// Função para criar a matriz de adjacência a partir da matriz de distância
vector<vector<int>> CriarMatrizAdjacencia(const vector<vector<int>> &matrizDist)
{
    int nVertices = matrizDist.size();
    vector<vector<int>> matrizAdj(nVertices, vector<int>(nVertices, 0));

    for (int i = 0; i < nVertices; i++)
    {
        for (int j = 0; j < nVertices; j++)
        {
            if (matrizDist[i][j] != 0 && matrizDist[i][j] != 999)
            {
                matrizAdj[i][j] = 1; // Existe uma aresta entre i e j
            }
        }
    }

    return matrizAdj;
}

vector<vector<int>> CriarMatrizIncidencia(const vector<vector<int>> &matriz, int tipoGrafo)
{
    int nVertices = matriz.size();
    int nArestas = 0;

    // Conta o número total de arestas no digrafo
    for (int i = 0; i < nVertices; i++)
    {
        for (int j = 0; j < nVertices; j++)
        {
            if (matriz[i][j] != 0 && matriz[i][j] != 999)
            {
                nArestas++;
            }
        }
    }

    vector<vector<int>> matrizInc(nVertices, vector<int>(nArestas, 0));

    int arestaAtual = 0;
    
    // Preenche a matriz de incidência
    if(tipoGrafo == 2 || tipoGrafo == 3){
        for (int j = 0; j < nVertices; j++)
        {
            for (int i = 0; i < nVertices; i++)
            {
                if (matriz[i][j] != 0 && matriz[i][j] != 999)
                {
                    matrizInc[i][arestaAtual] = -1;
                    matrizInc[j][arestaAtual] = 1;
                    arestaAtual++;
                }
            }
        }
    }
    else if(tipoGrafo == 1){
       for (int i = 0; i < nVertices; i++)
        for (int j = i + 1; j < nVertices; j++)
            if (matriz[i][j] == 1)
            {
                matrizInc[i][arestaAtual] = 1;
                matrizInc[j][arestaAtual] = 1;
                arestaAtual++;
            }
    }

    return matrizInc;
}

TabelaIncidencia CriarTabelaIncidencia(const vector<vector<int>> &matrizInc)
{
    int nLinhas = matrizInc.size();
    int nColunas = matrizInc[0].size();

    TabelaIncidencia tabelaInc(nLinhas, nColunas);

    for (int i = 0; i < nLinhas; i++)
        for (int j = 0; j < nColunas; j++)
            if (matrizInc[i][j] != 0)
                tabelaInc.AdicionarElemento(i, j, matrizInc[i][j]);
    return tabelaInc;
}

void ImprimirMatrizNxN(const vector<vector<int>> &matriz, int n, ofstream &output_file)
{
    cout << "  ";
    output_file << "  ";
    for (int i = 0; i < n; i++)
    {
        cout << setw(5) << i << " ";
        output_file << setw(5) << i << " ";
    }
    cout << endl
         << endl;
    output_file << endl
                << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << " ";
        output_file << i << " ";
        for (int j = 0; j < n; j++)
        {
            cout << setw(5) << matriz[i][j] << " ";
            output_file << setw(5) << matriz[i][j] << " ";
        }
        cout << endl;
        output_file << endl;
    }
}

void ImprimirMatrizIncidencia(const vector<vector<int>> &matrizInc, int n, ofstream &output_file)
{
    for (int i = 0; i < matrizInc[0].size(); i++)
    {
        cout << setw(5) << (char)(97 + i) << " ";
        output_file << setw(5) << (char)(97 + i) << " ";
    }
    cout << endl
         << endl;
    output_file << endl
                << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << " ";
        output_file << i << " ";
        for (int j = 0; j < matrizInc[0].size(); j++)
        {
            cout << setw(5) << matrizInc[i][j] << " ";
            output_file << setw(5) << matrizInc[i][j] << " ";
        }
        cout << endl;
        output_file << endl;
    }
}

void Imprimir(const vector<vector<int>> &matrizAdj, const vector<vector<int>> &matrizInc, TabelaIncidencia *tabelaInc, int n, ofstream &output_file)
{
            cout << endl << "Matriz de Adjacência:" << endl;
            output_file << endl << "Matriz de Adjadência:" << endl;
            ImprimirMatrizNxN(matrizAdj, n, output_file);

            cout << endl << "Matriz de Incidência:" << endl << "  ";
            output_file << endl << "Matriz de Incidência:" << endl  << "  ";
            ImprimirMatrizIncidencia(matrizInc, n, output_file);

            cout << endl << "Tabela de Incidência:" << endl;
            output_file << endl << "Tabela de Incidência:" << endl;
            tabelaInc->Imprimir(output_file);
}


