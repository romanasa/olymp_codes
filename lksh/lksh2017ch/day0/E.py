n = int(input())
while n > 9:
	n = sum([int(x) for x in str(n)])
print(n)
