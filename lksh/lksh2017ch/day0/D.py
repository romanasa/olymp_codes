n = int(input())
a = [[] for i in range(n)]

for i in range(n):
	a[i] = [int(i) for i in input().split()]
	
ans = float('-inf')

for s in range(0, n + n):	
	cur = 0
	ok = 0
	for i in range(0, n):
		j = s - i
		if j >= 0 and j < n: 
			cur += a[i][j]
			ok = 1
	if not ok:
		continue
	ans = max(ans, cur);
	
for s in range(-n - n, n + n):	
	cur = 0
	ok = 0
	for i in range(0, n):
		j = i - s
		if j >= 0 and j < n: 
			cur += a[i][j]
			ok = 1
	if not ok: 
		continue
	ans = max(ans, cur);
		
print(ans)