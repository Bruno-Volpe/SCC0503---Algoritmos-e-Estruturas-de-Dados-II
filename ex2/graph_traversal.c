#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int vertices[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Grafo;

// Função para inicializar o grafo
void inicializaGrafo(Grafo *grafo, int numVertices) {
    grafo->numVertices = numVertices;

    // Inicializa a matriz de adjacências com 0's
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            grafo->vertices[i][j] = 0;
        }
    }
}

// Função para adicionar uma aresta ao grafo
void adicionaAresta(Grafo *grafo, int origem, int destino) {
    grafo->vertices[origem][destino] = 1;
}

// Função para DFS (Busca em Profundidade) recursivo
void DFS(Grafo *grafo, int vertice, int visitado[]) {
    printf("visited %d \n", vertice);
    visitado[vertice] = 1;

    for (int i = 0; i < grafo->numVertices; i++) {
        if (grafo->vertices[vertice][i] && !visitado[i]) {
            DFS(grafo, i, visitado);
        }
    }
}

// Função para BFS (Busca em Largura)
void BFS_aux(Grafo *grafo, int visitado[], int fila[], int *frente, int *tras) {
    if (*frente == *tras) {
        return;
    }

    int verticeAtual = fila[(*frente)++];
    for (int i = 0; i < grafo->numVertices; i++) {
        if (grafo->vertices[verticeAtual][i] && !visitado[i]) {
            printf("visited %d \n", i);
            visitado[i] = 1;
            fila[(*tras)++] = i;
        }
    }

    BFS_aux(grafo, visitado, fila, frente, tras);
}

void BFS(Grafo *grafo, int verticeInicial) {
    int visitado[MAX_VERTICES] = {0};
    int fila[MAX_VERTICES];
    int frente = 0, tras = 0;

    printf("visited %d \n", verticeInicial);
    visitado[verticeInicial] = 1;
    fila[tras++] = verticeInicial;

    BFS_aux(grafo, visitado, fila, &frente, &tras);
}

int main() {
    int numVertices, origem, destino;
    Grafo grafo;

    // Leitura do número de vértices
    scanf("%d", &numVertices);
    inicializaGrafo(&grafo, numVertices);

    // Leitura das arestas
    while (scanf("%d %d", &origem, &destino) == 2) {
        adicionaAresta(&grafo, origem, destino);
    }

    printf("DFS\n");
    int visitadoDFS[MAX_VERTICES] = {0};
    for (int i = 0; i < numVertices; i++) {
        if (!visitadoDFS[i]) {
            DFS(&grafo, i, visitadoDFS);
        }
    }

    printf("BFS\n");
    BFS(&grafo, 0);

    return 0;
}
