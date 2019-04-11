import sys
sys.setrecursionlimit(100500)

def F(n):
	return (k**n - 1) // (k - 1)

l = 0
def go(x, n):
	global l
	if (x == 1): return
	x -= 1
	t = F(n)
	c = ((x - 1) // t)
	print(c + 1, end = ' ')
	go(x - c * t, n - 1)


k, n = [int(i) for i in input().split()]

if k % 2 == 0:
	print(k // 2, end = ' ')
	for i in range(n - 1):
		print(k, end = ' ')
	exit()

res = F(n) * k
go((res + 1) // 2 + 1, n)
	