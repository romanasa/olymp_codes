from decimal import *
getcontext().prec = 100


A, B = [Decimal(int(i)) for i in input().split()]
C, D = [Decimal(int(i)) for i in input().split()]


dx = [ 0, 1, 0, -1 ]
dy = [ 1, 0, -1, 0 ]

def ok(x, y):
	j = (x - 2 * y) // 5
	i = y + 2 * j
	return 2 * i + j == x and i - 2 * j == y

	
for i in range(4):
	na = A + dx[i]
	nb = B + dy[i]
	if (ok(na, nb)):
		A = na
		B = nb
		break
		

for i in range(4):
	nc = C + dx[i]
	nd = D + dy[i]
	if (ok(nc, nd)):
		C = nc
		D = nd
		break
	
	
a = A - C
b = B - D


t1 = (Decimal(3).sqrt() * a + b).copy_abs()
t2 = (Decimal(3).sqrt() * b - a).copy_abs()
x = (t1 + t2) / (Decimal(2) * Decimal(5).sqrt())
print(x.to_integral_exact())
