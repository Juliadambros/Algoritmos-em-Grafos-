def CRIA_CONJUNTO(pai, nivel, v):
    pai[v] = v
    nivel[v] = 0

def ENCONTRA_CONJUNTO(pai, v):
    while pai[v] != v:
        v = pai[v]
    return v

def UNIAO(pai, nivel, raiz1, raiz2):
    if nivel[raiz1] < nivel[raiz2]:
        pai[raiz1] = raiz2
    elif nivel[raiz1] > nivel[raiz2]:
        pai[raiz2] = raiz1
    else:
        pai[raiz2] = raiz1
        nivel[raiz1] += 1

def AGM_KRUSKAL(V, E):
    pai = [0] * V
    nivel = [0] * V
    A = []

    for v in range(V):
        CRIA_CONJUNTO(pai, nivel, v)

    E.sort(key=lambda x: x[2])  

    for (u, v, peso) in E:
        raiz_u = ENCONTRA_CONJUNTO(pai, u)
        raiz_v = ENCONTRA_CONJUNTO(pai, v)
        if raiz_u != raiz_v:
            A.append(peso)
            UNIAO(pai, nivel, raiz_u, raiz_v)

    return sum(A)

R, C = map(int, input().split())  
E = []

for _ in range(C):
    v, w, p = map(int, input().split())
    E.append((v - 1, w - 1, p))  

print(AGM_KRUSKAL(R, E))
