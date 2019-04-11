def gcd(a, b):
	while (b):
		a, b = b, a % b
	return a

n, m, k, c, l = [int(i) for i in input().split()]
 	
cnt = [[0] * 131 for i in range(n)]

for i in range(n):
	s = input()
	for v in s:                            
		cnt[i][ord(v) - ord('A')] += 1

num = 0
den = 1

allnum = m ** n
allden = m ** n

for i in range(c):
	comb, cost = input().split()
	cost = int(cost) - 1

	curn = 1
	curd = 1
	for j in range(n):
		v = comb[j]
		if (v != '*'):
			curn *= cnt[j][ord(v) - ord('A')]
			curd *= m
		else:
			curn *= m
			curd *= m
                     

	allnum -= curn
                
	curn *= cost

	num = num * curd + den * curn
	den = curd * den
                             
allnum *= -1

num = num * allden + den * allnum
den = allden * den

p = gcd(num, den)
num //= p
den //= p
if (num <= 0):
	print(0, 1, sep = '/')
	print(0)
else:
	print(num, den, sep = '/')
	print(1)
	print(1)