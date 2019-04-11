a, b, c = [int(i) for i in input().split()]
a -= 1
b -= 1
c -= 1

ans = 0    
while a > 0:
	ans += 1
	a //= 2

while b > 0:
	ans += 1
	b //= 2

while c > 0:
	ans += 1
	c //= 2
print(ans)
