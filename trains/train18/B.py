import sys
sys.stdin = open('input.txt')
sys.stdout = open('output.txt', 'w')


n = int(input())

x = [0] * (n + 1)
y = [0] * (n + 1)

for i in range(n + 1):
	x[i], y[i] = [int(x) for x in input().split()]
	
t = float(input())

p1 = [0] * (n + 1)
p2 = [0] * (n + 1)

p1[0] = 1.0
p2[0] = 1.0

for i in range(1, n + 1):
	p1[i] = p1[i - 1] * t
	
for i in range(1, n + 1):
	p2[i] = p2[i - 1] * (1 - t)

sx = 0.0
sy = 0.0
	
C = 1
for i in range(n + 1):
	sx += x[i] * C * p2[n - i] * p1[i]
	sy += y[i] * C * p2[n - i] * p1[i]
	
	C *= n - i
	C //= i + 1
	#if i % 100 == 0: print(C)
	
print("%.10f " % sx)
print("%.10f " % sy)
