import sys
sys.stdin = open('tickets.in')
sys.stdout = open('tickets.out', 'w')

n = int(input())
C, D, P = [int(i) for i in input().split()]


def calc(s):
	dp = []
	for i in range(15):
		dp.append([[0] * 2 for i in range(15)])	

	dp[0][0][0] = 1
	
	ind = len(s)
	
	for i in range(ind):
		for j in range(i + 1):
			for t in range(2):
				maxc = 9
				if (t == 0): maxc = ord(s[i]) - ord('0')
				
				for c in range(0, maxc + 1):
					dp[i + 1][j + (c == D)][t | (c < maxc)] += dp[i][j][t]
	
	ans = 0
	for cnt in range(ind + 1):
		cost = C
		
		cost *= (100 - P) ** cnt
		cost //= 100 ** cnt
		
		ans += cost * (dp[ind][cnt][0] + dp[ind][cnt][1])
	return ans
				

for it in range(n):
	a, b = input().split()
	
	cur = calc(b) - calc(a)
	
	cnt = 0
	for c in a:
		if (ord(c) - ord('0') == D):
			cnt += 1
	
	cost = C * (100 - P) ** cnt
	cost //= 100 ** cnt
	print(cur + cost)
	