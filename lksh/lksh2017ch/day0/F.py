n = int(input())
g = [[] for i in range(n)]
p = [int(i) for i in input().split()]

for i in range(1, n):
	g[p[i - 1] - 1].append(i)
	
ans = []
	
def dfs(v, pr, h):
	if (h % 2):
		ans.append(v + 1)
	for to in g[v]:
		if pr != to:
			dfs(to, v, h + 1)
	
dfs(0, 0, 0)

ans.sort()
print(len(ans))
print(*ans)