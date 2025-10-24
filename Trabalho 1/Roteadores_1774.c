#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int v, w, peso;
} Aresta;

int find_set(int pai[], int x) {
    if (pai[x] != x)
        pai[x] = find_set(pai, pai[x]);
    return pai[x];
}

void uniao(int pai[], int rank[], int x, int y) {
    int raizX = find_set(pai, x);
    int raizY = find_set(pai, y);

    if (raizX != raizY) {
        if (rank[raizX] < rank[raizY])
            pai[raizX] = raizY;
        else if (rank[raizX] > rank[raizY])
            pai[raizY] = raizX;
        else {
            pai[raizY] = raizX;
            rank[raizX]++;
        }
    }
}

void troca(Aresta *a, Aresta *b) {
    Aresta aux = *a;
    *a = *b;
    *b = aux;
}

int particiona(Aresta A[], int inicial, int final) {
    int pivo = A[final].peso;  
    int i = inicial - 1;

    for (int j = inicial; j < final; j++) {
        if (A[j].peso < pivo) {
            i++;
            troca(&A[i], &A[j]);
        }
    }
    troca(&A[i + 1], &A[final]);
    return i + 1;
}

void quicksort(Aresta A[], int inicial, int final) {
    if (inicial < final) {
        int pivo = particiona(A, inicial, final);
        quicksort(A, inicial, pivo - 1);
        quicksort(A, pivo + 1, final);
    }
}

int main() {
    int R, C;
    scanf("%d %d", &R, &C);

    Aresta *arestas = (Aresta *)malloc(C * sizeof(Aresta));
    int *pai = (int *)malloc((R + 1) * sizeof(int));
    int *rank = (int *)malloc((R + 1) * sizeof(int));

    for (int i = 0; i < C; i++) {
        scanf("%d %d %d", &arestas[i].v, &arestas[i].w, &arestas[i].peso);
    }

    quicksort(arestas, 0, C - 1);  

    for (int i = 1; i <= R; i++) {
        pai[i] = i;
        rank[i] = 0;
    }

    int custo_total = 0;
    int arestas_usadas = 0;

    for (int i = 0; i < C && arestas_usadas < R - 1; i++) {
        int v = arestas[i].v;
        int w = arestas[i].w;
        int p = arestas[i].peso;

        if (find_set(pai, v) != find_set(pai, w)) {
            uniao(pai, rank, v, w);
            custo_total += p;
            arestas_usadas++;
        }
    }

    printf("%d\n", custo_total);

    free(arestas);
    free(pai);
    free(rank);

    return 0;
}
