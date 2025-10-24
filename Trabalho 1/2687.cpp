//compila e chora
//Ana Júlia Orlovski,  Jotair Kwiatkowski Jr. e Júlia Dambrós

#include <iostream>
#include <iomanip>
using namespace std;

int L;
int grid[15][15];     
int visitado[15][15]; 

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y) {
    if (x < 0 || y < 0 || x >= L || y >= L) return;

    if (visitado[x][y] || grid[x][y] == 1) return;

    visitado[x][y] = 1;

    for (int i = 0; i < 4; i++)
        dfs(x + dx[i], y + dy[i]);
}

int main() {
    int Q; 
    cin >> Q;

    while (Q--) {
        cin >> L; 

        for (int i = 0; i < L; i++) {
            for (int j = 0; j < L; j++) {
                cin >> grid[i][j];
                visitado[i][j] = 0;
            }
        }

        int perimetro = 0;
        for (int i = 0; i < L; i++)
            for (int j = 0; j < L; j++)
                if (grid[i][j] == 1)
                    perimetro++;

        for (int i = 0; i < L; i++) {
            if (grid[i][0] == 0) dfs(i, 0);         
            if (grid[i][L - 1] == 0) dfs(i, L - 1); 
        }
        for (int j = 0; j < L; j++) {
            if (grid[0][j] == 0) dfs(0, j);         
            if (grid[L - 1][j] == 0) dfs(L - 1, j); 
        }

        int internos = 0;
        for (int i = 0; i < L; i++)
            for (int j = 0; j < L; j++)
                if (grid[i][j] == 0 && !visitado[i][j])
                    internos++;

        double area = (perimetro + internos) / 2.0;

        cout << fixed << setprecision(2) << area << endl;
    }

    return 0;
}
