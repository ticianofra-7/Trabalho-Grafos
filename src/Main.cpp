#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>

#include "TabelaIncidencia.h"

using namespace std;

// Parte 1 - Base
void LerMatriz(ifstream &input_file, vector<vector<int>> &matriz, int n);
vector<vector<int>> CriarMatrizAdjacencia(const vector<vector<int>> &matrizDist, int tipoGrafo);
vector<vector<int>> CriarMatrizIncidencia(const vector<vector<int>> &matrizDist, int tipoGrafo);
TabelaIncidencia CriarTabelaIncidencia(const vector<vector<int>> &matrizInc);
void ImprimirMatrizNxN(const vector<vector<int>> &matriz, int n, ofstream &output_file);
void ImprimirMatrizIncidencia(const vector<vector<int>> &matrizInc, int n, ofstream &output_file);
void Imprimir(const vector<vector<int>> &matrizAdj, const vector<vector<int>> &matrizInc, TabelaIncidencia *tabelaInc, int n, ofstream &output_file);

//Parte 2 - Algoritmos
void BuscaEmLargura(const vector<vector<int>> &matrizAdj, int verticeInicial, vector<bool> &visitados, ofstream &output_file);
void BuscaEmLargura_Completa(const vector<vector<int>> &matrizAdj, int n, ofstream &output_file);

void BuscaEmProfundidade(const vector<vector<int>> &matrizAdj, int verticeInicial, vector<bool> &visitados, ofstream &output_file);
void BuscaEmProfundidade_Completa(const vector<vector<int>> &matrizAdj, int n, ofstream &output_file);

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
            matrizAdj = CriarMatrizAdjacencia(matriz, tipoGrafo); // Serve para execução da Busca em Largura
            matrizInc = CriarMatrizIncidencia(matriz, tipoGrafo);
            tabelaInc = CriarTabelaIncidencia(matrizInc);

            // Imprime no console e escreve no arquivo
            Imprimir(matriz, matrizInc, &tabelaInc, n, output_file);

            // Executa Busca em Largura
            cout << "Busca em Largura: ";
            output_file << "Busca em Largura: ";
            BuscaEmLargura_Completa(matrizAdj, n, output_file);

            // Executa Busca em Profundidade
            cout << "Busca em Profundidade: ";
            output_file << "Busca em Profundidade: ";
            BuscaEmProfundidade_Completa(matrizAdj, n, output_file);  
            break;
        case 2:
            tipoGrafo = 2;
            matrizAdj = CriarMatrizAdjacencia(matriz, tipoGrafo);            
            matrizInc = CriarMatrizIncidencia(matriz, tipoGrafo);
            tabelaInc = CriarTabelaIncidencia(matrizInc);

            // Imprime no console e escreve no arquivo
            Imprimir(matriz, matrizInc, &tabelaInc, n, output_file);

            // Executa Busca em Largura
            cout << "Busca em Largura: ";
            output_file << "Busca em Largura: ";
            BuscaEmLargura_Completa(matrizAdj, n, output_file);    

            // Executa Busca em Profundidade
            cout << "Busca em Profundidade: ";
            output_file << "Busca em Profundidade: ";
            BuscaEmProfundidade_Completa(matrizAdj, n, output_file);          
            break;
        case 3:
            tipoGrafo = 3;
            matrizAdj = CriarMatrizAdjacencia(matriz, tipoGrafo);
            matrizInc = CriarMatrizIncidencia(matriz, tipoGrafo);
            tabelaInc = CriarTabelaIncidencia(matrizInc);

            // Imprime no console e escreve no arquivo
            cout << "Matriz de Distância:" << endl;
            output_file << "Matriz de Distância:" << endl;
            ImprimirMatrizNxN(matriz, n, output_file);
            Imprimir(matrizAdj, matrizInc, &tabelaInc, n, output_file);  

            // Executa Busca em Largura
            cout << "Busca em Largura: ";
            output_file << "Busca em Largura: ";
            BuscaEmLargura_Completa(matrizAdj, n, output_file);

            // Executa Busca em Profundidade
            cout << "Busca em Profundidade: ";
            output_file << "Busca em Profundidade: ";
            BuscaEmProfundidade_Completa(matrizAdj, n, output_file); 
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

// Parte 1 - Base
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

vector<vector<int>> CriarMatrizAdjacencia(const vector<vector<int>> &matriz, int tipoGrafo)
{
    int nVertices = matriz.size();
    vector<vector<int>> matrizAdj(nVertices, vector<int>(nVertices, 0));

    if(tipoGrafo == 1){
        for (int i = 0; i < nVertices; i++)
        {
            for (int j = 0; j < nVertices; j++)
            {
                if (matriz[i][j] != 0 && matriz[i][j] != 999)
                {
                    matrizAdj[i][j] = 1; // Existe uma aresta de i para j
                    matrizAdj[j][i] = 1; // Existe uma aresta de j para i, ou seja, existe uma única aresta entre i e j (via de mão dupla)
                }
            }
        }

    }
    else if(tipoGrafo == 2 || tipoGrafo == 3){
        for (int i = 0; i < nVertices; i++)
        {
            for (int j = 0; j < nVertices; j++)
            {
                if (matriz[i][j] != 0 && matriz[i][j] != 999)
                {
                    matrizAdj[i][j] = 1; // Existe uma aresta de i para j
                }
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


// Parte 2 - Algoritmos
void BuscaEmLargura(const vector<vector<int>> &matrizAdj, int verticeInicial, vector<bool> &visitados, ofstream &output_file) {
    queue<int> fila;

    // Inicializa a fila e marca o vértice inicial como visitado
    fila.push(verticeInicial);
    visitados[verticeInicial] = true;

    while (!fila.empty()) {
        int verticeAtual = fila.front(); // Retorna uma referência ao elemento no início da fila 
        fila.pop();

        cout << verticeAtual << " ";
        output_file << verticeAtual << " ";

        // Percorre todos os vértices adjacentes ao vértice atual
        for (int i = 0; i < matrizAdj.size(); i++) {
            // Verifica se há uma aresta entre os vértices e se o vértice adjacente não foi visitado
            if (matrizAdj[verticeAtual][i] == 1 && !visitados[i]) {
                fila.push(i);
                visitados[i] = true;
            }
        }
    }
}

// Função para realizar a Busca em Largura em todos os vértices do grafo
void BuscaEmLargura_Completa(const vector<vector<int>> &matrizAdj, int n, ofstream &output_file) {
    vector<bool> visitados(n, false);

    // Executa a Busca em Largura a partir de todos os vértices não visitados
    for (int i = 0; i < n; i++) {
        if (!visitados[i]) {
            BuscaEmLargura(matrizAdj, i, visitados, output_file);
        }
    }
    cout << endl;
    output_file << endl;
}

void BuscaEmProfundidade(const vector<vector<int>> &matrizAdj, int verticeInicial, vector<bool> &visitados, ofstream &output_file)
{
    visitados[verticeInicial] = true;
    cout << verticeInicial << " ";
    output_file << verticeInicial << " ";

    for (int i = 0; i < matrizAdj.size(); ++i)
    {
        if (matrizAdj[verticeInicial][i] == 1 && !visitados[i])
        {
            BuscaEmProfundidade(matrizAdj, i, visitados, output_file);
        }
    }
}

void BuscaEmProfundidade_Completa(const vector<vector<int>> &matrizAdj, int n, ofstream &output_file)
{
    vector<bool> visitados(n, false);

    for (int i = 0; i < n; ++i)
    {
        if (!visitados[i])
        {
            BuscaEmProfundidade(matrizAdj, i, visitados, output_file);
        }
    }
    cout << endl;
    output_file << endl;
}

