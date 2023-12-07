#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <climits>

#include "TabelaIncidencia.h"

using namespace std;

// Parte 1 - Base
void LerMatriz(ifstream &input_file, vector<vector<int>> &matriz, int n);
vector<vector<int>> CriarMatrizAdjacencia(const vector<vector<int>> &matriz, int tipoGrafo);
vector<vector<int>> CriarMatrizDistancia(const vector<vector<int>> &matriz, int tipoGrafo);
vector<vector<int>> CriarMatrizIncidencia(const vector<vector<int>> &matriz, int tipoGrafo);
TabelaIncidencia CriarTabelaIncidencia(const vector<vector<int>> &matrizInc);
void ImprimirMatrizNxN(const vector<vector<int>> &matriz, int n, ofstream &output_file);
void ImprimirMatrizIncidencia(const vector<vector<int>> &matrizInc, int n, ofstream &output_file);
void Imprimir(const vector<vector<int>> &matrizDist, const vector<vector<int>> &matrizAdj, const vector<vector<int>> &matrizInc, TabelaIncidencia *tabelaInc, int n, ofstream &output_file);

//Parte 2 - Algoritmos
void BuscaEmLargura(const vector<vector<int>> &matrizAdj, int verticeInicial, ofstream &output_file);

void BuscaEmProfundidade(const vector<vector<int>> &matrizAdj, int verticeInicial, vector<bool> &visitados, ofstream &output_file);
void BuscaEmProfundidade_Aux(const vector<vector<int>> &matrizAdj, int n, int verticeInicial, ofstream &output_file);

void Prim(const vector<vector<int>>& matrizDist, int n, ofstream &output_file);

void caminhoMinimo(const vector<vector<int>> &matrizDist, int verticeInicial, int nVertices, ofstream &output_file);

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

    // Matriz a ser lida (distância)
    vector<vector<int>> matriz;
    LerMatriz(input_file, matriz, n);

    vector<vector<int>> matrizAdj;
    vector<vector<int>> matrizDist;
    vector<vector<int>> matrizInc;
    TabelaIncidencia tabelaInc;

    int tipoGrafo; // 1 - Simples (matriz lida = distância), 2 - Digrafo valorado (matriz lida = distância)
    int opcaoAlgoritmo;
    int verticeInicial; // Para algoritmos BFS e DPS

    cout << "Escolha o tipo de grafo:" << endl;
    cout << "[1] Grafo Simples, valorado" << endl;
    cout << "[2] Digrafo Simples, valorado" << endl << endl;
    cin >> tipoGrafo;
    cout << endl;

    if(tipoGrafo == 1){
        matrizAdj = CriarMatrizAdjacencia(matriz, tipoGrafo);
        matrizDist = CriarMatrizDistancia(matriz, tipoGrafo);
        matrizInc = CriarMatrizIncidencia(matrizAdj, tipoGrafo);
        tabelaInc = CriarTabelaIncidencia(matrizInc);
        Imprimir(matriz, matrizAdj, matrizInc, &tabelaInc, n, output_file);

        do{
            cout << endl << "Escolha um algoritmo:" << endl;
            cout << "[1] Busca em Largura (BFS)" << endl;
            cout << "[2] Busca em Profundidade (DFS)" << endl;
            cout << "[3] Árvore Geradora Mínima (Prim)" << endl;
            cout << "[4] Sair" << endl << endl;
            cin >> opcaoAlgoritmo;

            switch (opcaoAlgoritmo)
            {
            case 1:
                cout << endl << "Informe o vértice inicial: ";
                cin >> verticeInicial;
                output_file << endl << "Vértice inicial: " << verticeInicial << endl;
                cout << "Busca em Largura: ";
                output_file << "Busca em Largura: ";
                BuscaEmLargura(matrizAdj, verticeInicial, output_file);                            
                break;
            
            case 2:
                cout << endl << "Informe o vértice inicial: ";
                cin >> verticeInicial;
                output_file << endl << "Vértice inicial: " << verticeInicial << endl;
                cout << "Busca em Profundidade: ";
                output_file << "Busca em Profundidade: ";
                BuscaEmProfundidade_Aux(matrizAdj, n, verticeInicial, output_file);                    
                break;
            
            case 3:
                cout << endl << "Árvore Geradora Mínima (Prim):" << endl;
                output_file << endl << "Árvore Geradora Mínima (Prim):" << endl;
                Prim(matriz, n, output_file);                
                break;

            case 4:
                cout << "Dijkstra para caminho minimo: ";
                output_file << "Dijkstra para caminho minimo: ";
                caminhoMinimo(matrizDist, 0, n, output_file);
                break;
            
            default:
                cout << endl << "Nenhum algoritmo selecionado. Saindo..." << endl;
                break;
            }
        }while(opcaoAlgoritmo != 4);
    }
    else if(tipoGrafo == 2){
        matrizAdj = CriarMatrizAdjacencia(matriz, tipoGrafo);
        matrizDist = CriarMatrizDistancia(matriz, tipoGrafo);
        matrizInc = CriarMatrizIncidencia(matrizAdj, tipoGrafo);
        tabelaInc = CriarTabelaIncidencia(matrizInc);
        Imprimir(matriz, matrizAdj, matrizInc, &tabelaInc, n, output_file);

        do{
            cout << endl <<"Escolha um algoritmo:" << endl;
            cout << "[1] Busca em Largura (BFS)" << endl;
            cout << "[2] Busca em Profundidade (DFS)" << endl;
            cout << "[3] Árvore Geradora Mínima (Prim)" << endl;
            cout << "[4] Sair" << endl << endl;
            cin >> opcaoAlgoritmo;

            switch (opcaoAlgoritmo)
            {
            case 1:
                cout << endl << "Informe o vértice inicial: ";
                cin >> verticeInicial;
                output_file << endl << "Vértice inicial: " << verticeInicial << endl;
                cout << "Busca em Largura: ";
                output_file << "Busca em Largura: ";
                BuscaEmLargura(matrizAdj, verticeInicial, output_file);                            
                break;
            
            case 2:
                cout << endl << "Informe o vértice inicial: ";
                cin >> verticeInicial;
                output_file << endl << "Vértice inicial: " << verticeInicial << endl;
                cout << "Busca em Profundidade: ";
                output_file << "Busca em Profundidade: ";
                BuscaEmProfundidade_Aux(matrizAdj, n, verticeInicial, output_file);                    
                break;
            
            case 3:
                cout << endl << "Árvore Geradora Mínima (Prim):" << endl;
                output_file << endl << "Árvore Geradora Mínima (Prim):" << endl;
                Prim(matriz, n, output_file);                
                break;
            
            default:
                cout << endl << "Nenhum algoritmo selecionado. Saindo..." << endl;
                break;
            }
        }while(opcaoAlgoritmo != 4);
    }
    
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

vector<vector<int>> CriarMatrizAdjacencia(vector<vector<int>> &matriz, int tipoGrafo)
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

                    matriz[j][i] = matriz[i][j]; // Completa matriz de distância (= matriz simétrica)
                }
            }
        }
    }
    else if(tipoGrafo == 2){
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

vector<vector<int>> CriarMatrizDistancia(const vector<vector<int>> &matriz, int tipoGrafo) {
    int nVertices = matriz.size();
    vector<vector<int>> matrizDist(nVertices, vector<int>(nVertices, 999));
    
    if(tipoGrafo == 1) {
        for(int i = 0; i < nVertices; i++) {
            for(int j = i; j < nVertices; j++) {
                if(matriz[i][j] != 0 && matriz[i][j] != 999) {
                    matrizDist[i][j] = matriz[i][j];
                    matrizDist[j][i] = matriz[i][j];
                }
            }
        }
    }
    if(tipoGrafo == 2) {
        for(int i = 0; i < matriz.size(); i++) {
            for(int j = 0; j < matriz[j].size(); j++) {
                if(matriz[i][j] != 0 && matriz[i][j] != 999) {
                    matrizDist[i][j] = matriz[i][j];
                }
            }
        }
    }

    return matrizDist;
}

vector<vector<int>> CriarMatrizIncidencia(const vector<vector<int>> &matriz, int tipoGrafo)
{
    int nVertices = matriz.size();
    int nArestas = 0;

    // Conta o número total de arestas
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

    vector<vector<int>> matrizInc;

    int arestaAtual = 0;
    
    // Preenche a matriz de incidência
    if(tipoGrafo == 1){
        matrizInc.resize(nVertices, vector<int>(nArestas/2, 0));
       for (int i = 0; i < nVertices; i++)
        for (int j = i + 1; j < nVertices; j++)
            if (matriz[i][j] == 1)
            {
                matrizInc[i][arestaAtual] = 1;
                matrizInc[j][arestaAtual] = 1;
                arestaAtual++;
            }
    }
    else if(tipoGrafo == 2){
        matrizInc.resize(nVertices, vector<int>(nArestas, 0));
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

void Imprimir(const vector<vector<int>> &matrizDist, const vector<vector<int>> &matrizAdj, const vector<vector<int>> &matrizInc, TabelaIncidencia *tabelaInc, int n, ofstream &output_file)
{
            cout << "Matriz de Distância:" << endl;
            output_file << "Matriz de Distância:" << endl;
            ImprimirMatrizNxN(matrizDist, n, output_file);

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
void BuscaEmLargura(const vector<vector<int>> &matrizAdj, int verticeInicial, ofstream &output_file) {
    queue<int> fila;
    vector<bool> visitados(matrizAdj.size(), false);

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
    cout << endl;
    output_file << endl;
}

void BuscaEmProfundidade(const vector<vector<int>> &matrizAdj, int verticeInicial, vector<bool> &visitados, ofstream &output_file)
{

    visitados[verticeInicial] = true;
    cout << verticeInicial << " ";
    output_file << verticeInicial << " ";

    for (int i = 0; i < matrizAdj.size(); i++)
    {
        if (matrizAdj[verticeInicial][i] == 1 && !visitados[i])
        {
            BuscaEmProfundidade(matrizAdj, i, visitados, output_file);
        }
    }
}

void BuscaEmProfundidade_Aux(const vector<vector<int>> &matrizAdj, int n, int verticeInicial, ofstream &output_file)
{
    vector<bool> visitados(n, false);

    BuscaEmProfundidade(matrizAdj, verticeInicial, visitados, output_file);      
    
    cout << endl;
    output_file << endl;
}

void caminhoMinimo(const vector<vector<int>> &matrizDist, int verticeInicial, int nVertices, ofstream &output_file) {

    int verticeAtual, contador, menor, temporario, distancia;
    vector<bool> visitados(nVertices, false);
    vector<int> distancias(nVertices, 999);
    queue<int> filaVertices, filaOrdem, filaDistancias;

    verticeAtual = verticeInicial;
    contador = 0;

    for(int i = 0; i < nVertices; i++) {
        visitados[verticeAtual] = true;
        filaVertices.push(verticeAtual);
        filaOrdem.push(contador);
        if(distancias[verticeAtual] == 999)
            filaDistancias.push(0);
        else
            filaDistancias.push(distancias[verticeAtual]);
        for(int j = 0; j < nVertices; j++) {
            if(!visitados[j]) {
                distancia = matrizDist[verticeAtual][j];
                if(verticeAtual == verticeInicial) {
                    if(distancias[j] == 999)
                        distancias[j] = distancia;
                }
                else {
                    if(distancias[j] == 999) {
                        temporario = distancias[verticeAtual] + distancia;
                        distancias[j] = temporario;
                    }
                    else if(distancias[j] != 999 && distancia != 999) {
                        temporario = distancias[verticeAtual] + distancia;
                        if(temporario < distancias[j])
                            distancias[j] = temporario;
                    }
                }
            }
        }
        menor = distancias[0];
        for(int j = 0; j < distancias.size(); j++) {
            if(distancias[j] < menor && visitados[j] == false) {
                menor = distancias[j];
                verticeAtual = j;
            }
        }
        contador++;
    }

    //cout << "Lista do caminho minimo a partir do vertice inicial (1o parametro: vertice; 2o parametro: ordem; 3o parametro: distancia): ";
    cout << endl << "(1o parametro: vertice; 2o parametro: ordem; 3o parametro: distancia)" << endl;
    cout << "[";
    for(int i = 0; i < nVertices; i++) {
        cout << "(" << filaVertices.front() << "," << filaOrdem.front() << "," << filaDistancias.front() << ")";
        filaVertices.pop();
        filaOrdem.pop();
        filaDistancias.pop();
        if(!(i == nVertices-1))
            cout << ",";
    }
    cout << "]";
}
void Prim(const vector<vector<int>> &matrizDist, int n, ofstream &output_file) {
    // Vetor para armazenar os pais dos vértices na árvore geradora mínima
    vector<int> pais(n, -1);
    // Vetor para armazenar o peso mínimo de cada vértice até a árvore geradora mínima
    vector<int> pesoMinimo(n, INT_MAX);
    // Vetor para marcar se um vértice está incluído na árvore geradora mínima
    vector<bool> incluido(n, false);

    // Inicializa o peso mínimo do primeiro vértice como 0
    pesoMinimo[0] = 0;

    // Cria uma fila de prioridade (min heap) para escolher a próxima aresta de menor peso
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridade; // greater: Comparador usado para garantir que os elementos sejam organizados na fila de prioridade em ordem crescente com base no primeiro elemento do par (o peso da aresta).
    filaPrioridade.push({0, 0}); // {Peso, Vértice}

    while (!filaPrioridade.empty()) {
        int atual = filaPrioridade.top().second; // Vértice associado à menor aresta
        filaPrioridade.pop();

        incluido[atual] = true;

        for (int v = 0; v < n; v++) {
            if (matrizDist[atual][v] != 0 && matrizDist[atual][v] != 999 && !incluido[v] && matrizDist[atual][v] < pesoMinimo[v]) {
                pesoMinimo[v] = matrizDist[atual][v];
                pais[v] = atual;
                filaPrioridade.push({pesoMinimo[v], v});
            }
        }
    }

    // Imprime a árvore geradora mínima
    for (int i = 1; i < n; i++) {
        cout << pais[i] << " -> " << i << " | Peso: " << pesoMinimo[i] << endl;
        output_file << pais[i] << " -> " << i << " | Peso: " << pesoMinimo[i] << endl;
    }
}
