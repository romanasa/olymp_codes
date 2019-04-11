n, l, r = [int(i) for i in input().split()]
for x in range(1, n + 1):
	for j in range(l, r + 1):
		if (x % j == 0):
			break
	else:
		print(x, end = ' ')
	