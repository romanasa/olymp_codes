p = [1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67]


def rec(d, res, m):
	global mx, x
	if (d >= len(p)):
		return
		
	if (res > mx or (res == mx and m < x)):
		mx = res
		x = m
	pw = 1
	r = p[d]
	while (m * r <= n and m * r > 0):
		rec(d + 1, res * (pw + 1), m * r)
		r *= p[d]
		pw += 1
		
n = int(input())
mx = 0
x = 0
rec(1, 1, 1)
print(mx, x)
