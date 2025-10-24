#include <iostream>
#include <iomanip>
using namespace std;

int L;
int grid[15][15];      // Matriz fixa para o grid (bactéria)
int visitado[15][15];  // Matriz fixa para marcação de visitados

// Movimentos possíveis: cima, baixo, esquerda, direita
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Função recursiva DFS para marcar zeros externos
void dfs(int x, int y) {
    // Verifica se está fora dos limites do grid
    if (x < 0 || y < 0 || x >= L || y >= L) return;

    // Se já foi visitado ou é borda (1), interrompe
    if (visitado[x][y] || grid[x][y] == 1) return;

    // Marca como visitado
    visitado[x][y] = 1;

    // Explora as quatro direções
    for (int i = 0; i < 4; i++)
        dfs(x + dx[i], y + dy[i]);
}

int main() {
    int Q; // Quantidade de bactérias
    cin >> Q;

    while (Q--) {
        cin >> L; // Lê o tamanho do grid

        // Leitura do grid e inicialização de visitado
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < L; j++) {
                cin >> grid[i][j];
                visitado[i][j] = 0;
            }
        }

        // Conta o perímetro (número de células com 1)
        int perimetro = 0;
        for (int i = 0; i < L; i++)
            for (int j = 0; j < L; j++)
                if (grid[i][j] == 1)
                    perimetro++;

        // Marca os zeros externos com DFS
        for (int i = 0; i < L; i++) {
            if (grid[i][0] == 0) dfs(i, 0);         // Borda esquerda
            if (grid[i][L - 1] == 0) dfs(i, L - 1); // Borda direita
        }
        for (int j = 0; j < L; j++) {
            if (grid[0][j] == 0) dfs(0, j);         // Borda superior
            if (grid[L - 1][j] == 0) dfs(L - 1, j); // Borda inferior
        }

        // Conta os zeros internos (não visitados)
        int internos = 0;
        for (int i = 0; i < L; i++)
            for (int j = 0; j < L; j++)
                if (grid[i][j] == 0 && !visitado[i][j])
                    internos++;

        // Calcula a área dominada
        double area = (perimetro + internos) / 2.0;

        // Exibe com duas casas decimais
        cout << fixed << setprecision(2) << area << endl;
    }

    return 0;
}
