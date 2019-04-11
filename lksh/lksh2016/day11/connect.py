import sys
sys.setrecursionlimit(100500)
sys.stdin = open('connect.in')
sys.stdout = open('connect.out', 'w')

def dfs(v, c):
	global color
	color[v] = c

	for to in e[v]:
		if (not color[to]):
			dfs(to, c)

n = int(input())
e = [[] for i in range(n)]
color = [0] * n

for i in range(n):
	e[i] = list(map(lambda x : int(x) - 1, input().split()))[1:]

cur = 1
for i in range(n):
	if not color[i]:
		dfs(i, cur)
		cur += 1
print(cur - 1)
print(*color)