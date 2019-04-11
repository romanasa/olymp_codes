n = int(input())
ans, cur = 0, 0
for x in input().split():
	cur += int(x)
	ans = max(ans, cur)
print(ans)