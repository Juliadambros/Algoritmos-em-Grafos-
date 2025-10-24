def dfs(x, y, L, grid, visitado):
    if x < 0 or y < 0 or x >= L or y >= L:
        return
    if visitado[x][y] or grid[x][y] == 1:
        return

    visitado[x][y] = True

    for dx, dy in [(-1,0),(1,0),(0,-1),(0,1)]:
        dfs(x + dx, y + dy, L, grid, visitado)

Q = int(input())

for _ in range(Q):
    L = int(input())
    grid = [list(map(int, input().split())) for _ in range(L)]
    visitado = [[False]*L for _ in range(L)]

    perimetro = sum(grid[i][j] == 1 for i in range(L) for j in range(L))

    # Marcar zeros externos
    for i in range(L):
        if grid[i][0] == 0: dfs(i, 0, L, grid, visitado)
        if grid[i][L-1] == 0: dfs(i, L-1, L, grid, visitado)
    for j in range(L):
        if grid[0][j] == 0: dfs(0, j, L, grid, visitado)
        if grid[L-1][j] == 0: dfs(L-1, j, L, grid, visitado)

    internos = sum(grid[i][j] == 0 and not visitado[i][j] for i in range(L) for j in range(L))
    area = (perimetro + internos) / 2.0

    print(f"{area:.2f}")
