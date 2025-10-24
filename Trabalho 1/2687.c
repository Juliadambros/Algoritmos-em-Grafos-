#include <stdio.h>

#define MAX 15

int L;
int grid[MAX][MAX];
int visitado[MAX][MAX];

// Movimentos possíveis: cima, baixo, esquerda, direita
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y) {
    if (x < 0 || y < 0 || x >= L || y >= L) return;
    if (visitado[x][y] || grid[x][y] == 1) return;

    visitado[x][y] = 1;

    for (int i = 0; i < 4; i++) {
        dfs(x + dx[i], y + dy[i]);
    }
}

int main() {
    int Q;
    scanf("%d", &Q);

    while (Q--) {
        scanf("%d", &L);

        for (int i = 0; i < L; i++)
            for (int j = 0; j < L; j++) {
                scanf("%d", &grid[i][j]);
                visitado[i][j] = 0;
            }

        int perimetro = 0;

        // Contar o perímetro (todas as bordas 1)
        for (int i = 0; i < L; i++)
            for (int j = 0; j < L; j++)
                if (grid[i][j] == 1)
                    perimetro++;

        // Marcar os zeros externos com DFS (começando pelas bordas)
        for (int i = 0; i < L; i++) {
            if (grid[i][0] == 0) dfs(i, 0);
            if (grid[i][L - 1] == 0) dfs(i, L - 1);
        }
        for (int j = 0; j < L; j++) {
            if (grid[0][j] == 0) dfs(0, j);
            if (grid[L - 1][j] == 0) dfs(L - 1, j);
        }

        // Contar zeros internos (não visitados)
        int internos = 0;
        for (int i = 0; i < L; i++)
            for (int j = 0; j < L; j++)
                if (grid[i][j] == 0 && !visitado[i][j])
                    internos++;

        double area = (perimetro + internos) / 2.0;
        printf("%.2lf\n", area);
    }

    return 0;
}
