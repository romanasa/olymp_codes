#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

#define TASK "army"

const int dd = (int)1e5 + 1;

int dp[dd][5][5];
int p[dd][5][5];

int k, x, y, tmp;
	
int get(int msk, int bit) {
	return (msk >> bit) & 1;
}

bool checkL(int msk1, int msk2) {
	int ok = 1;
	int cnt1 = get(msk2, 0) + get(msk1, 1); 
	
	if ((msk1 & 1) && ((x != -1 && cnt1 != x) || (y != -1 && 2 - cnt1 != y))) ok = 0;
	if ((msk1 & 1) == 0 && (x == -1 || cnt1 == x) && (y == -1 || 2 - cnt1 == y)) ok = 0;
		
	int cnt2 = get(msk1, 0) + get(msk2, 1);
	
	if ((msk1 & 2) && ((x != -1 && cnt2 != x) || (y != -1 && 2 - cnt2 != y))) ok = 0;
	if ((msk1 & 2) == 0 && (x == -1 || cnt2 == x) && (y == -1 || 2 - cnt2 == y)) ok = 0;
	
	//err("cnt1 = %d, cnt2 = %d, x = %d, y = %d\n", cnt1, cnt2, x, y);
	//err("%d, %d, %d\n", msk1, msk2, ok);
	
	return ok;
}

bool check(int msk1, int msk2, int msk3) {
	int ok = 1;
	int cnt1 = get(msk1, 0) + get(msk2, 1) + get(msk3, 0);
	int cnt2 = get(msk1, 1) + get(msk2, 0) + get(msk3, 1);
	
	if (get(msk2, 0) == 1 && ((x != -1 && cnt1 != x) || (y != -1 && 3 - cnt1 != y))) ok = 0;
	if (get(msk2, 0) == 0 && (x == -1 || cnt1 == x) && (y == -1 || 3 - cnt1 == y)) ok = 0;
	
	if (get(msk2, 1) == 1 && ((x != -1 && cnt2 != x) || (y != -1 && 3 - cnt2 != y))) ok = 0;
	if (get(msk2, 1) == 0 && (x == -1 || cnt2 == x) && (y == -1 || 3 - cnt2 == y)) ok = 0;
	
	return ok;
}

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	scanf("%d %d %d", &k, &x, &y);
	
	if (k == 1) {
		
		int t1 = (int)1e9, a1 = -1;
		int t2 = -1, a2 = -1;
		
		for (int msk = 0; msk < 4; msk++) {
			int cnt1 = (msk >> 1) & 1;
			int cnt2 = (msk & 1);
			
			int ok = 1;
			
			if (get(msk, 0) == 1 && ((x != -1 && cnt1 != x) || (y != -1 && 1 - cnt1 != y))) ok = 0;
			if (get(msk, 0) == 0 && (x == -1 || cnt1 == x) && (y == -1 || 1 - cnt1 == y)) ok = 0;
			
			
			if (get(msk, 1) == 1 && ((x != -1 && cnt2 != x) || (y != -1 && 1 - cnt2 != y))) ok = 0;
			if (get(msk, 1) == 0 && (x == -1 || cnt2 == x) && (y == -1 || 1 - cnt2 == y)) ok = 0;
			
			if (!ok) continue;
			
			if (t1 > cnt1 + cnt2) {
				t1 = cnt1 + cnt2;
				a1 = msk;
			}
			if (t2 < cnt1 + cnt2) {
				t2 = cnt1 + cnt2;
				a2 = msk;
			}
		}
		
		if (t2 == -1) return 0 * puts("-1");
		
		printf("%d\n%d\n%d\n", t1, get(a1, 0), get(a1, 1));
		printf("%d\n%d\n%d\n", t2, get(a2, 0), get(a2, 1));
	
		return 0;
	}
	
	//checkL(0, 1);
	//return 0;
	
	for (int i = 0; i <= k; i++) 
		for (int k = 0; k < 4; k++)
			for (int j = 0; j < 4; j++)
				dp[i][k][j] = (int)1e9 + 1;
	
	for (int msk1 = 0; msk1 < 4; msk1++) {
		for (int msk2 = 0; msk2 < 4; msk2++) {
			if (!checkL(msk1, msk2)) continue;
			dp[2][msk1][msk2] = get(msk1, 0) + get(msk1, 1);
		}
	}
	
	for (int i = 2; i < k; i++) {
		for (int msk1 = 0; msk1 < 4; msk1++) {
			for (int msk2 = 0; msk2 < 4; msk2++) {
				if (dp[i][msk1][msk2] == (int)1e9 + 1) continue;
				
				for (int msk3 = 0; msk3 < 4; msk3++) {
					if (!check(msk1, msk2, msk3)) continue;		
					if (dp[i + 1][msk2][msk3] > (tmp = dp[i][msk1][msk2] + get(msk2, 0) + get(msk2, 1))) {
						dp[i + 1][msk2][msk3] = tmp;
						p[i + 1][msk2][msk3] = msk1;
					}
				}
			}
		}
	}
	
	
	int ans = (int)1e9 + 1, a = -1, b = -1;
	
	for (int msk1 = 0; msk1 < 4; msk1++) {
		for (int msk2 = 0; msk2 < 4; msk2++) {
			if (!checkL(msk2, msk1) || dp[k][msk1][msk2] == (int)1e9 + 1) continue;
			if (ans > (tmp = dp[k][msk1][msk2] + get(msk2, 0) + get(msk2, 1))) {
				ans = tmp;
				a = msk1;
				b = msk2;
			}
		}
	}
	
	if (ans == (int)1e9 + 1) {
		return 0 * puts("-1");
	}
	
	printf("%d\n", ans);
	deque<int> cur;
	cur.push_front(b);
	
	for (int i = k - 1; i; i--) {
		cur.push_front(a);
		int pm = p[i + 1][a][b];
		b = a, a = pm;
	}
	
	for (int i = 0; i < 2; i++) {
		for (int x : cur) putchar('0' + ((x >> i) & 1));
		putchar('\n');
	}
	
	
	
	
	for (int i = 0; i <= k; i++) 
		for (int k = 0; k < 4; k++)
			for (int j = 0; j < 4; j++)
				dp[i][k][j] = -1;
	
	for (int msk1 = 0; msk1 < 4; msk1++) {
		for (int msk2 = 0; msk2 < 4; msk2++) {
			if (!checkL(msk1, msk2)) continue;
			dp[2][msk1][msk2] = get(msk1, 0) + get(msk1, 1);
		}
	}
	
	for (int i = 2; i < k; i++) {
		for (int msk1 = 0; msk1 < 4; msk1++) {
			for (int msk2 = 0; msk2 < 4; msk2++) {
				if (dp[i][msk1][msk2] == -1) continue;
				
				for (int msk3 = 0; msk3 < 4; msk3++) {
					if (!check(msk1, msk2, msk3)) continue;		
					if (dp[i + 1][msk2][msk3] < (tmp = dp[i][msk1][msk2] + get(msk2, 0) + get(msk2, 1))) {
						dp[i + 1][msk2][msk3] = tmp;
						p[i + 1][msk2][msk3] = msk1;
					}
				}
			}
		}
	}
	
	
	ans = -1, a = -1, b = -1;
	
	for (int msk1 = 0; msk1 < 4; msk1++) {
		for (int msk2 = 0; msk2 < 4; msk2++) {
			if (!checkL(msk2, msk1) || dp[k][msk1][msk2] == -1) continue;
			if (ans < (tmp = dp[k][msk1][msk2] + get(msk2, 0) + get(msk2, 1))) {
				ans = tmp;
				a = msk1;
				b = msk2;
			}
		}
	}
	
	
	printf("%d\n", ans);
	cur.clear();
	cur.push_front(b);
	
	for (int i = k - 1; i; i--) {
		cur.push_front(a);
		int pm = p[i + 1][a][b];
		b = a, a = pm;
	}
	
	for (int i = 0; i < 2; i++) {
		for (int x : cur) putchar('0' + ((x >> i) & 1));
		putchar('\n');
	}
	
	
	return 0;
}