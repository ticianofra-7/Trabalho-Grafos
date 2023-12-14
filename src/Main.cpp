#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <climits>
#include <stack>

#include "TabelaIncidencia.h"

using namespace std;

// Parte 1 - Base
void LerMatriz(ifstream &input_file, vector<vector<int>> &matriz, int n);
vector<vector<int>> CriarMatrizAdjacencia(vector<vector<int>> &matrizDist, int tipoGrafo);
vector<vector<int>> CriarMatrizIncidencia(const vector<vector<int>> &matrizDist, int tipoGrafo);
TabelaIncidencia CriarTabelaIncidencia(const vector<vector<int>> &matrizInc);
void ImprimirMatrizNxN(const vector<vector<int>> &matriz, int n, ofstream &output_file);
void ImprimirMatrizIncidencia(const vector<vector<int>> &matrizInc, int n, ofstream &output_file);
void Imprimir(const vector<vector<int>> &matrizDist, const vector<vector<int>> &matrizAdj, const vector<vector<int>> &matrizInc, TabelaIncidencia *tabelaInc, int n, ofstream &output_file);

//Parte 2 - Algoritmos
void BuscaEmLargura(const vector<vector<int>> &matrizAdj, int verticeInicial, ofstream &output_file);

void BuscaEmProfundidade_Aux(const vector<vector<int>> &matrizAdj, int verticeInicial, vector<bool> &visitados, ofstream &output_file);
void BuscaEmProfundidade(const vector<vector<int>> &matrizAdj, int n, int verticeInicial, ofstream &output_file);

void CaminhoMinimo(vector<vector<int>> &matrizDist, int verticeInicial, int nVertices, ofstream &output_file);

void Prim(const vector<vector<int>>& matrizDist, int n, ofstream &output_file);

void OrdenacaoTopologica_Aux(const vector<vector<int>> &matrizAdj, int vertice, vector<bool> &visitados, stack<int> &pilha);
void OrdenacaoTopologica(const vector<vector<int>> &matrizAdj, ofstream &output_file);

void CicloEuleriano(const vector<vector<int>> &matrizInc, ofstream &output_file);

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
    vector<vector<int>> matrizInc;
    TabelaIncidencia tabelaInc;

    int tipoGrafo; // 1 - Simples (matriz lida = distância), 2 - Digrafo valorado (matriz lida = distância)
    int opcaoAlgoritmo;
    int verticeInicial; // Para algoritmos BFS, DFS e Caminho Mínimo

    cout << "Escolha o tipo de grafo:" << endl;
    cout << "[1] Grafo Simples, valorado" << endl;
    cout << "[2] Digrafo Simples, valorado" << endl << endl;
    cin >> tipoGrafo;
    cout << endl;

    if(tipoGrafo == 1){
        matrizAdj = CriarMatrizAdjacencia(matriz, tipoGrafo);
        matrizInc = CriarMatrizIncidencia(matrizAdj, tipoGrafo);
        tabelaInc = CriarTabelaIncidencia(matrizInc);
        Imprimir(matriz, matrizAdj, matrizInc, &tabelaInc, n, output_file);

        do{
            cout << endl << "Escolha um algoritmo:" << endl;
            cout << "[1] Busca em Largura (BFS)" << endl;
            cout << "[2] Busca em Profundidade (DFS)" << endl;
            cout << "[3] Árvore Geradora Mínima (Prim)" << endl;
            cout << "[4] Caminho Mínimo (Dijkstra)" << endl;
            cout << "[5] Ciclo Euleriano" << endl;
            cout << "[6] Sair" << endl << endl;
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
                BuscaEmProfundidade(matrizAdj, n, verticeInicial, output_file);                    
                break;
            
            case 3:
                cout << endl << "Árvore Geradora Mínima (Prim): " << endl;
                output_file << endl << "Árvore Geradora Mínima (Prim): " << endl;
                Prim(matriz, n, output_file);                
                break;

            case 4:
                cout << endl << "Informe o vértice inicial: ";
                cin >> verticeInicial;
                output_file << endl << "Vértice inicial: " << verticeInicial << endl;
                cout << endl << "Caminho mínimo (Dijkstra): ";
                output_file << endl << "Caminho mínimo (Dijkstra): ";
                CaminhoMinimo(matriz, verticeInicial, n, output_file);
                break;
            case 5:
                cout << endl << "Ciclo euleriano: ";
                output_file << endl << "Ciclo euleriano: ";
                CicloEuleriano(matrizInc, output_file);
                break;
            
            default:
                cout << endl << "Nenhum algoritmo selecionado. Saindo..." << endl;
                break;
            }
        }while(opcaoAlgoritmo != 6);
    }
    else if(tipoGrafo == 2){
        matrizAdj = CriarMatrizAdjacencia(matriz, tipoGrafo);
        matrizInc = CriarMatrizIncidencia(matrizAdj, tipoGrafo);
        tabelaInc = CriarTabelaIncidencia(matrizInc);
        Imprimir(matriz, matrizAdj, matrizInc, &tabelaInc, n, output_file);

        do{
            cout << endl << "Escolha um algoritmo:" << endl;
            cout << "[1] Busca em Largura (BFS)" << endl;
            cout << "[2] Busca em Profundidade (DFS)" << endl;
            cout << "[3] Árvore Geradora Mínima (Prim)" << endl;
            cout << "[4] Ordenação Topológica" << endl;
            cout << "[5] Sair" << endl << endl;
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
                BuscaEmProfundidade(matrizAdj, n, verticeInicial, output_file);                    
                break;
            
            case 3:
                cout << endl << "Árvore Geradora Mínima (Prim):" << endl;
                output_file << endl << "Árvore Geradora Mínima (Prim):" << endl;
                Prim(matriz, n, output_file);                
                break;
            
            case 4:
                cout << endl << "Ordenação Topológica:" << endl;
                output_file << endl << "Ordenação Topológica:" << endl;
                OrdenacaoTopologica(matrizAdj, output_file);
                break;
            
            default:
                cout << endl << "Nenhum algoritmo selecionado. Saindo..." << endl;
                break;
            }
        }while(opcaoAlgoritmo != 5);
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

void BuscaEmProfundidade_Aux(const vector<vector<int>> &matrizAdj, int verticeInicial, vector<bool> &visitados, ofstream &output_file)
{

    visitados[verticeInicial] = true;
    cout << verticeInicial << " ";
    output_file << verticeInicial << " ";

    for (int i = 0; i < matrizAdj.size(); i++)
    {
        if (matrizAdj[verticeInicial][i] == 1 && !visitados[i])
        {
            BuscaEmProfundidade_Aux(matrizAdj, i, visitados, output_file);
        }
    }
}

void BuscaEmProfundidade(const vector<vector<int>> &matrizAdj, int n, int verticeInicial, ofstream &output_file)
{
    vector<bool> visitados(n, false);

    BuscaEmProfundidade_Aux(matrizAdj, verticeInicial, visitados, output_file);      
    
    cout << endl;
    output_file << endl;
}

void CaminhoMinimo(vector<vector<int>> &matrizDist, int verticeInicial, int nVertices, ofstream &output_file) {

    int verticeAtual, menor, temporario, distancia;
    vector<bool> visitados(nVertices, true);
    vector<int> distancias(nVertices, 999);
    queue<int> filaVertices;
    vector<queue<int>> listaFilaVertices(nVertices-1);

    verticeAtual = verticeInicial;

    //Convertendo os valores da matriz de distância de 0 para 999 e armazenando numa nova matriz de distância
    for(int i = 0; i < nVertices; i++)
        for(int j = 0; j < nVertices; j++)
            if(matrizDist[i][j] == 0)
                matrizDist[i][j] = 999;

    //Verifica qual vértice não possui aresta ligada a ele
    for(int i = 0; i < nVertices; i++) {
        for(int j = 0; j < nVertices; j++) {
            if(matrizDist[i][j] != 999 || matrizDist[j][i] != 999) {
                visitados[i] = false;
                break;
            }
        }
    }

    //Algoritmo

    //Verifica se o vertice escolhido possui arestas ou não ligados a ele
    if(!visitados[verticeInicial]) {
        //condição: varre todos os vértices caso seja um grafo conexo ou varre todos os vértices do subgrafo conexo
        for(int i = 0; i < nVertices && visitados[verticeAtual] == false; i++) {
            visitados[verticeAtual] = true;
            if(i == 0) {
                filaVertices.push(verticeInicial);
                for(int j = 0; j < listaFilaVertices.size(); j++) {
                    listaFilaVertices[j] = filaVertices;
                }
            }
            for(int j = 0; j < nVertices; j++) {
                //Verifica se o vértice já está inserido na árvore
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
                            listaFilaVertices[j-1].push(verticeAtual);
                        }
                        else if(distancias[j] != 999 && distancia != 999) {
                            temporario = distancias[verticeAtual] + distancia;
                            if(temporario < distancias[j]) {
                                distancias[j] = temporario;
                                listaFilaVertices[j-1].push(verticeAtual);
                            }
                        }
                    }
                }
            }
            menor = distancias[verticeInicial];
            verticeAtual = verticeInicial;
            for(int j = 0; j < distancias.size(); j++) {
                if(distancias[j] < menor && visitados[j] == false) {
                    menor = distancias[j];
                    verticeAtual = j;
                }
            }
            listaFilaVertices[verticeAtual-1].push(verticeAtual);
        }

        //Impressão
        cout << endl;
        for(int i = 0; i < listaFilaVertices.size(); i++) {
            cout << "Caminho do vertice inicial (" << verticeInicial << ") até o vertice (" << i+1 << ") : ";
            while(!listaFilaVertices[i].empty()) {
                cout << listaFilaVertices.front().front();
                listaFilaVertices.front().pop();
                if(!listaFilaVertices.front().empty()) {
                    cout << ",";
                }
            }
            cout << endl;
        }
    } else {
        //Impressão
        cout << "\n\n";
        cout << "O vertice escolhido como vertice inicial nao possui arestas e, portanto, seu caminho minimo e 0." << endl;
        output_file << "O vertice escolhido como vertice inicial nao possui arestas e, portanto, seu caminho minimo e 0." << endl;
    }   
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
    filaPrioridade.push({0, 0}); // {Peso, Vértice}                                                 // vector<pair<int, int>>: Tipo do contêiner subjacente à fila de prioridade. Neste caso, é um vetor de pares de inteiros.

    while (!filaPrioridade.empty()) {
        int atual = filaPrioridade.top().second; // Vértice associado à menor aresta
        filaPrioridade.pop();

        incluido[atual] = true;

        for (int v = 0; v < n; v++) {
            if (matrizDist[atual][v] != 0 && matrizDist[atual][v] != 999 && !incluido[v] && matrizDist[atual][v] < pesoMinimo[v]) {
                pesoMinimo[v] = matrizDist[atual][v]; // Peso mínimo do vértice atual para algum adjacente v
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

void OrdenacaoTopologica_Aux(const vector<vector<int>> &matrizAdj, int vertice, vector<bool> &visitados, stack<int> &pilha) {
    visitados[vertice] = true;

    for (int i = 0; i < matrizAdj.size(); i++) {
        if (matrizAdj[vertice][i] == 1 && !visitados[i]) {
            OrdenacaoTopologica_Aux(matrizAdj, i, visitados, pilha);
        }
    }

    pilha.push(vertice);
}

void OrdenacaoTopologica(const vector<vector<int>> &matrizAdj, ofstream &output_file) {
    int n = matrizAdj.size();
    vector<bool> visitados(n, false);
    stack<int> pilha;

    for (int i = 0; i < n; i++) {
        if (!visitados[i]) {
            OrdenacaoTopologica_Aux(matrizAdj, i, visitados, pilha);
        }
    }

    // Imprime a ordenação topológica
    while (!pilha.empty()) {
        cout << pilha.top() << " ";
        output_file << pilha.top() << " ";
        pilha.pop();
    }

    cout << endl;
    output_file << endl;
}

void CicloEuleriano(const vector<vector<int>> &matrizInc, ofstream &output_file) {

    int verticeInicial, verticeAtual, arestaAtual, nArestas;
    bool matrizVazio, linhaVazio;
    vector<vector<int>> matrizCiclo;
    queue<int> ciclo, cicloEuleriano;
    queue<queue<int>> ciclosNormais;

    matrizCiclo = matrizInc;
    nArestas = 0;

    for(int i = 0; i < matrizCiclo.size(); i++) {
        for(int j = 0; j < matrizCiclo[i].size(); j++) {
            if(matrizCiclo[i][j] == 1)
                nArestas++;
        }
        if(nArestas % 2 == 1)
            break;
    }

    if(nArestas % 2 == 0) {
        do {
            verticeInicial = 0;
            verticeAtual = 0;
            matrizVazio = true;
            linhaVazio = true;

            while(!ciclo.empty()) {
                ciclo.pop();
            }

            for(int i = 0; i < matrizCiclo.size(); i++) {
                for(int j = 0; j < matrizCiclo[i].size(); j++) {
                    if(matrizCiclo[i][j] == 1) {
                        verticeInicial = i;
                        verticeAtual = i;
                        linhaVazio = false;
                        break;
                    }
                }
                if(!linhaVazio)
                    break;
            }

            do {
                ciclo.push(verticeAtual);
                for(int i = 0; i < matrizCiclo[verticeAtual].size(); i++) {
                    if(matrizCiclo[verticeAtual][i] == 1)
                        arestaAtual = i;
                }
                matrizCiclo[verticeAtual][arestaAtual] = 0;
                for(int i = 0; i < matrizCiclo.size(); i++) {
                    if(matrizCiclo[i][arestaAtual] == 1)
                        verticeAtual = i;
                }
                matrizCiclo[verticeAtual][arestaAtual] = 0;
                if(verticeAtual == verticeInicial)
                    ciclo.push(verticeAtual);
            } while(verticeAtual != verticeInicial);

            ciclosNormais.push(ciclo);

            for(int i = 0; i < matrizCiclo.size(); i++) {
                for(int j = 0; j < matrizCiclo[i].size(); j++) {
                    if(matrizCiclo[i][j] == 1) {
                        matrizVazio = false;
                        break;
                    }
                }
                if(matrizVazio == false)
                    break;
            }
            
            if(ciclosNormais.size() > 1) {
                while(!ciclosNormais.front().empty()) {
                    if(ciclosNormais.front().front() == ciclosNormais.back().front() && ciclosNormais.back().empty() == false) {
                        while(!ciclosNormais.back().empty()) {
                            cicloEuleriano.push(ciclosNormais.back().front());
                            ciclosNormais.back().pop();
                        }
                        ciclosNormais.front().pop();
                    }
                    cicloEuleriano.push(ciclosNormais.front().front());
                    ciclosNormais.front().pop();
                }
                while(!ciclosNormais.empty()) {
                    ciclosNormais.pop();
                }
                ciclosNormais.push(cicloEuleriano);
            }

        } while(!matrizVazio);

        cout << "(";
        while(!cicloEuleriano.empty()) {
                cout << cicloEuleriano.front();
                output_file << cicloEuleriano.front();
            if(cicloEuleriano.size() != 1) {
                cout << ",";
                output_file << ",";
            }
            cicloEuleriano.pop();
        }
        cout << ")";
    } else {
        cout << "O grafo possui algum vertice que nao tem grau de incidencia par e, portanto, nao e possivel executar o algoritmo." << endl;
        output_file << "O grafo possui algum vertice que nao tem grau de incidencia par e, portanto, nao e possivel executar o algoritmo." << endl;
    }
}