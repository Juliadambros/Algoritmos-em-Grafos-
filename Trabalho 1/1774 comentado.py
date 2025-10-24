def CRIA_CONJUNTO(pai, nivel, v):
    pai[v] = v #cada vértice é pai de si mesmo
    nivel[v] = 0 #inicializa o altura da árvore como 0

#função para encontrar a raiz de um conjunto 
def ENCONTRA_CONJUNTO(pai, v):
    if pai[v] != v:
        pai[v] = ENCONTRA_CONJUNTO(pai, pai[v])  # atualiza pai[v] para a raiz
    return pai[v]


def UNIAO(pai, nivel, raiz1, raiz2):
    if nivel[raiz1] < nivel[raiz2]:
        pai[raiz1] = raiz2
    elif nivel[raiz1] > nivel[raiz2]:
        pai[raiz2] = raiz1
    else:
        pai[raiz2] = raiz1
        nivel[raiz1] += 1

def AGM_KRUSKAL(V, E):
    pai = [0] * V #vetor pai para os conjuntos disjuntos
    nivel = [0] * V #vetor de nível para o union
    A = [] #lista para armazenar os pesos das arestas escolhidas

    # Inicializa cada vértice como um conjunto separado
    for v in range(V):
        CRIA_CONJUNTO(pai, nivel, v)
    print("Após criar conjuntos:", pai, nivel)

    #ordena as arestas pelo peso (crescente)
    E.sort(key=lambda x: x[2])
    print("Arestas ordenadas por peso:", E)

    #itera pelas arestas e adiciona à AGM se não formar ciclo
    for (u, v, peso) in E:
        raiz_u = ENCONTRA_CONJUNTO(pai, u)
        raiz_v = ENCONTRA_CONJUNTO(pai, v)
        print(f"Avaliando aresta ({u+1}, {v+1}) com peso {peso}, raízes: {raiz_u}, {raiz_v}")
        
        if raiz_u != raiz_v: #adicionar se não estiverem no mesmo conjunto
            A.append(peso)
            UNIAO(pai, nivel, raiz_u, raiz_v)
            print(f"Aresta adicionada. Conjuntos atualizados: {pai}, Níveis: {nivel}")
        else:
            print("Aresta descartada (formaria ciclo)")

    #custo total
    return sum(A)

R, C = map(int, input("Digite R e C: ").split())  
E = []

for _ in range(C):
    v, w, p = map(int, input("Digite V W P: ").split())
    E.append((v - 1, w - 1, p))  # subtrai 1 para usar índices base 0

print("Custo total da rede otimizada:", AGM_KRUSKAL(R, E))

