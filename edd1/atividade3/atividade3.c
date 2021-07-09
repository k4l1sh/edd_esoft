#include <stdio.h>
#include <stdlib.h>

char *departamento[10] = {  "Alice",
                            "João",
                            "Berenice",
                            "Juliete",
                            "Romeu",
                            "Paulo",
                            "Henrique",
                            "Nilza",
                            "Lúcia",
                            "Andréia"};

struct no {
    int vertice;
    struct no* proximo;
};
struct no* criarNo(int v);
struct Grafo {
    int numVertices;
    int* visitado;
    struct no** adjacente;
};
struct no* criarNo(int v) {
    struct no* novono = malloc(sizeof(struct no));
    novono->vertice = v;
    novono->proximo = NULL;
    return novono;
}
struct Grafo* criarGrafo(int vertices) {
    struct Grafo* grafo = malloc(sizeof(struct Grafo));
    grafo->numVertices = vertices;
    grafo->adjacente = malloc(vertices * sizeof(struct no*));
    grafo->visitado = malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        grafo->adjacente[i] = NULL;
        grafo->visitado[i] = 0;
    }
    return grafo;
}

void adicionarConexao(struct Grafo* grafo, int src, int dest) {
    struct no* novono = criarNo(dest);
    novono->proximo = grafo->adjacente[src];
    grafo->adjacente[src] = novono;
    novono = criarNo(src);
    novono->proximo = grafo->adjacente[dest];
    grafo->adjacente[dest] = novono;
}

void BuscaEmProfundidade(struct Grafo* grafo, int vertice) {
    struct no* adjList = grafo->adjacente[vertice];
    struct no* temp = adjList;
    grafo->visitado[vertice] = 1;
    printf(" -> %s", departamento[vertice]);
    while (temp != NULL) {
        int verticeConectado = temp->vertice;
        if (grafo->visitado[verticeConectado] == 0) {
            BuscaEmProfundidade(grafo, verticeConectado);
        }
        temp = temp->proximo;
    }
}

void main() {
    struct Grafo* grafo = criarGrafo(10);
    // 0 - Alice
    // 1 - João
    // 2 - Berenice
    // 3 - Juliete
    // 4 - Romeu
    // 5 - Paulo
    // 6 - Henrique
    // 7 - Nilza
    // 8 - Lúcia
    // 9 - Andréia
    adicionarConexao(grafo, 0, 1);
    adicionarConexao(grafo, 0, 2);
    adicionarConexao(grafo, 1, 3);
    adicionarConexao(grafo, 1, 4);
    adicionarConexao(grafo, 2, 5);
    adicionarConexao(grafo, 2, 6);
    adicionarConexao(grafo, 3, 7);
    adicionarConexao(grafo, 5, 8);
    adicionarConexao(grafo, 5, 9);
    printf("Visitados:");
    BuscaEmProfundidade(grafo, 0);
    printf("\n");
}