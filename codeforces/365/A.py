n = int(input())

t1, t2 = 0, 0

for i in range(n):
	a, b = map(int, input().split())
	t1 += (a >= b)
	t2 += (b >= a)
	
if (t1 > t2):
	print('Mishka')
elif (t1 == t2):
	print('Friendship is magic!^^')
else:
	print('Chris')
