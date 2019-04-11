import sys
#sys.stdin = open('tickets.in')
#sys.stdout = open('tickets.out', 'w')

n, m = [int(i) for i in input().split()]

def gcd(a, b):
	while b: a, b = b, a % b
	return a

p = [0] * (n * m)
p1 = [0] * (n * m)
p2 = [0] * (n * m)
p3 = [0] * (n * m)
p4 = [0] * (n * m)

def gethash(p):
	h = 0
	for x in p:
		h = (h * 239017 + x + 1) % (2**64 + 7)
	return h
	
def mult(a, b):
	c = a.copy()
	for i in range(len(a)):
		a[i] = c[b[i]]
	
def get(p):
	t = p.copy()
	c = 0
	for i in range(len(t)):
		if t[i] != -1:
			c += 1
			j = i
			while t[j] != -1:
				nj = t[j]
				t[j] = -1
				j = nj
	return c
			

for i in range(n * m):
	p[i] = i
	p1[i] = (i % n + 1) % n + (i // n) * n
	p2[i] = ((i // n) + 1) % m * n + i % n
	p3[i] = (m - 1 - i // n) * n + (n - 1 - i % n)
	if n == m:
		ni = (i % n)
		nj = n - 1 - i // n
		p4[i] = ni * n + nj
	
s, c = 0, 0
S = set()

for i in range(n):
	for j in range(m):
		if n != m:
			for k in range(2):
				if not gethash(p) in S:
					S.add(gethash(p))
					c += 1
					s += 2 ** get(p)
				mult(p, p3)
		else:
			for k in range(4):
				if not gethash(p) in S:
					S.add(gethash(p))
					c += 1
					s += 2 ** get(p)
				mult(p, p4)
		mult(p, p2)
	mult(p, p1)

ans = s // c
print(ans)
