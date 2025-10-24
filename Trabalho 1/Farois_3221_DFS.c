#include <stdio.h>
#include <math.h>

#define MAX 1000
#define MAX_malha 50   

typedef struct { double x, y; } Ponto;
typedef struct { double x, y, r; } Circulo;

Ponto farois[MAX];
Circulo montanhas[MAX];

int N, M;

int tam;
Circulo *malha[MAX_malha][MAX_malha][MAX];
int malha_2D[MAX_malha][MAX_malha];

double xmin, ymin, xmax, ymax;
double cel_w, cel_h;

int grafo[MAX][MAX];     // matriz de adjacência (1 = visível)
int visitado[MAX];

// -------------------------------------------------------
// Funções auxiliares geométricas
// -------------------------------------------------------
static inline int bloqueado(Ponto A, Ponto B, Circulo C) {
    double vx = B.x - A.x, vy = B.y - A.y;
    double ux = C.x - A.x, uy = C.y - A.y;

    double vv = vx*vx + vy*vy;
    double t = (vx*ux + vy*uy) / vv;
    if (t < 0.0) t = 0.0;
    else if (t > 1.0) t = 1.0;

    double px = A.x + t * vx;
    double py = A.y + t * vy;

    double dx = px - C.x, dy = py - C.y;
    double d2 = dx*dx + dy*dy;
    return d2 < C.r*C.r;
}

static inline int x_i(double x) {
    int res = (int)((x - xmin) / cel_w);
    if (res < 0) res = 0;
    if (res >= tam) res = tam - 1;
    return res;
}

static inline int y_j(double y) {
    int res = (int)((y - ymin) / cel_h);
    if (res < 0) res = 0;
    if (res >= tam) res = tam - 1;
    return res;
}

void adiciona_malha(Circulo *c) {
    int x0 = x_i(c->x - c->r), x1 = x_i(c->x + c->r);
    int y0 = y_j(c->y - c->r), y1 = y_j(c->y + c->r);
    for (int i = x0; i <= x1; i++)
        for (int j = y0; j <= y1; j++)
            malha[i][j][malha_2D[i][j]++] = c;
}

// -------------------------------------------------------
// DFS para contar componentes conexos
// -------------------------------------------------------
void dfs(int u) {
    visitado[u] = 1;
    for (int v = 0; v < N; v++) {
        if (grafo[u][v] && !visitado[v])
            dfs(v);
    }
}

// -------------------------------------------------------
// Programa principal
// -------------------------------------------------------
int main() {
    scanf("%d %d", &N, &M);
    xmin = ymin = 1e9;
    xmax = ymax = -1e9;

    // Leitura dos faróis
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &farois[i].x, &farois[i].y);
        if (farois[i].x < xmin) xmin = farois[i].x;
        if (farois[i].x > xmax) xmax = farois[i].x;
        if (farois[i].y < ymin) ymin = farois[i].y;
        if (farois[i].y > ymax) ymax = farois[i].y;
    }

    // Leitura das montanhas
    for (int i = 0; i < M; i++) {
        scanf("%lf %lf %lf", &montanhas[i].x, &montanhas[i].y, &montanhas[i].r);
        if (montanhas[i].x - montanhas[i].r < xmin) xmin = montanhas[i].x - montanhas[i].r;
        if (montanhas[i].x + montanhas[i].r > xmax) xmax = montanhas[i].x + montanhas[i].r;
        if (montanhas[i].y - montanhas[i].r < ymin) ymin = montanhas[i].y - montanhas[i].r;
        if (montanhas[i].y + montanhas[i].r > ymax) ymax = montanhas[i].y + montanhas[i].r;
    }

    // Inicializa malha
    tam = 50;
    cel_w = (xmax - xmin) / tam + 1e-9;
    cel_h = (ymax - ymin) / tam + 1e-9;
    for (int i = 0; i < tam; i++)
        for (int j = 0; j < tam; j++)
            malha_2D[i][j] = 0;

    for (int i = 0; i < M; i++)
        adiciona_malha(&montanhas[i]);

    // ---------------------------------------------------
    // Construção da lista de visibilidade (grafo)
    // ---------------------------------------------------
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int visivel = 1;

            double dx = farois[i].x - farois[j].x;
            double dy = farois[i].y - farois[j].y;
            double distAB2 = dx*dx + dy*dy;

            int fx0 = x_i(fmin(farois[i].x, farois[j].x));
            int fx1 = x_i(fmax(farois[i].x, farois[j].x));
            int fy0 = y_j(fmin(farois[i].y, farois[j].y));
            int fy1 = y_j(fmax(farois[i].y, farois[j].y));

            for (int fx = fx0; fx <= fx1 && visivel; fx++) {
                for (int fy = fy0; fy <= fy1 && visivel; fy++) {
                    for (int k = 0; k < malha_2D[fx][fy]; k++) {
                        Circulo *c = malha[fx][fy][k];
                        double dxC = c->x - farois[i].x;
                        double dyC = c->y - farois[i].y;
                        if (dxC*dxC + dyC*dyC > distAB2 + 4*(c->r)*(c->r))
                            continue;
                        if (bloqueado(farois[i], farois[j], *c)) {
                            visivel = 0;
                            break;
                        }
                    }
                }
            }

            if (visivel) {
                grafo[i][j] = grafo[j][i] = 1; // cria aresta
            }
        }
    }

    // ---------------------------------------------------
    // Contagem de componentes com DFS
    // ---------------------------------------------------
    int componentes = 0;
    for (int i = 0; i < N; i++) visitado[i] = 0;

    for (int i = 0; i < N; i++) {
        if (!visitado[i]) {
            dfs(i);
            componentes++;
        }
    }

    printf("%d\n", componentes - 1);
    return 0;
}
