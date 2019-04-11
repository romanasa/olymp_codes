n, k, s = [int(i) for i in input().split()]
a = [int(i) for i in input().split()]
ans = 0

a.sort()
a.reverse()

def go(i, cur, curs):
	global ans
	if (i == n):
		if (cur == k and curs == s):
			ans += 1
	else:
		if (curs + a[i] * (n - i) < s):
			return
	
		go(i + 1, cur, curs)
		if cur + 1 <= k and curs + a[i] <= s: 
			go(i + 1, cur + 1, curs + a[i])

go(0, 0, 0)
print(ans)
	