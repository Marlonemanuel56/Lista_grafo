#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
using namespace std;

class GrafoMatriz {
public:
    int numVertices;
    vector<vector<int>> matrizAdj;

    GrafoMatriz(int n) {
        numVertices = n;
        matrizAdj.resize(n, vector<int>(n, 0));
    }

    void adicionarAresta(int u, int v, int peso) {
        matrizAdj[u][v] = peso;
        matrizAdj[v][u] = peso;
    }

    void exibirMatrizAdj() {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << matrizAdj[i][j] << " ";
            }
            cout << endl;
        }
    }
};

class GrafoLista {
public:
    int numVertices;
    vector<vector<int>> listaAdj;

    GrafoLista(int n) {
        numVertices = n;
        listaAdj.resize(n);
    }

    void adicionarAresta(int u, int v) {
        listaAdj[u].push_back(v);
        listaAdj[v].push_back(u);
    }

    void exibirListaAdj() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << ": ";
            for (int v : listaAdj[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

void carregarGrafo(string nomeArquivo, GrafoMatriz &grafoMatriz, GrafoLista &grafoLista) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo" << endl;
        return;
    }

    int n; 
    arquivo >> n;

    grafoMatriz = GrafoMatriz(n);
    grafoLista = GrafoLista(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int peso;
            arquivo >> peso;
            if (peso != 0) {
                grafoMatriz.adicionarAresta(i, j, peso);
                if (i < j) {
                    grafoLista.adicionarAresta(i, j);
                }
            }
        }
    }

    arquivo.close();
}

bool bfs(const GrafoLista &grafo, int s, int t, vector<int> &caminho) {
    vector<bool> visitado(grafo.numVertices, false);
    vector<int> anterior(grafo.numVertices, -1);
    queue<int> fila;

    visitado[s] = true;
    fila.push(s);

    while (!fila.empty()) {
        int v = fila.front();
        fila.pop();

        if (v == t) {
            for (int at = t; at != -1; at = anterior[at]) {
                caminho.push_back(at);
            }
            reverse(caminho.begin(), caminho.end());
            return true;
        }

        for (int vizinho : grafo.listaAdj[v]) {
            if (!visitado[vizinho]) {
                visitado[vizinho] = true;
                anterior[vizinho] = v;
                fila.push(vizinho);
            }
        }
    }
    return false;
}

void imprimirCaminhoBFS(const GrafoLista &grafo, int s, int t) {
    vector<int> caminho;
    if (bfs(grafo, s, t, caminho)) {
        cout << "Caminho do vertice " << s << " até o vertice " << t << ": ";
        for (int v : caminho) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "Não há caminho entre os vértices " << s << " e " << t << endl;
    }
}

void dfs(const GrafoLista &grafo, int s) {
    vector<bool> visitado(grafo.numVertices, false);
    stack<int> pilha;

    pilha.push(s);

    while (!pilha.empty()) {
        int v = pilha.top();
        pilha.pop();

        if (!visitado[v]) {
            cout << v << " ";
            visitado[v] = true;
        }

        for (int vizinho : grafo.listaAdj[v]) {
            if (!visitado[vizinho]) {
                pilha.push(vizinho);
            }
        }
    }
    cout << endl;
}

void mostrarUso() {
    cout << "Uso: ./programa nome_do_arquivo vertice_inicial vertice_final\n";
    cout << "Exemplo: ./programa grafo.txt 0 4\n";
}

int main(int argc, char* argv[]) {
    GrafoMatriz grafoMatriz(0);
    GrafoLista grafoLista(0);
    
    if (argc != 4) {
        mostrarUso();
        return 1;
    }

    string nomeArquivo = argv[1];
    int s = stoi(argv[2]);
    int t = stoi(argv[3]);

    carregarGrafo(nomeArquivo, grafoMatriz, grafoLista);

    cout << "Matriz de Adjacência:\n";
    grafoMatriz.exibirMatrizAdj();

    cout << "\nLista de Adjacência:\n";
    grafoLista.exibirListaAdj();

    cout << "\nBusca em Largura (BFS):\n";
    imprimirCaminhoBFS(grafoLista, s, t);

    cout << "\nBusca em Profundidade (DFS):\n";
    dfs(grafoLista, s);

    return 0;
}
