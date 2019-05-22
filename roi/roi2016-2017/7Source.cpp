#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <queue>

using namespace std;
typedef long long ll;

int solve();

#define TASK "anti"

int main() {
#ifndef HOM
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

const int dd = (int)2e6 + 1;
ll l[dd], r[dd], c[dd];
ll dp[dd];

void upd(ll &a, ll b) { if (a < b) a = b; }

struct qq {
	deque<ll> q;

	void push(ll x) {
		while (q.size() && q.back() > x) q.pop_back();
		q.push_back(x);
	}

	void pop(ll x) {
		if (q.front() == x) q.pop_front();
	}
} Q[107];

int solve() {
	int n, a;
	scanf("%d %d", &n, &a);

	for (int i = 0; i < n; i++) {
		scanf("%lld %lld %lld", &l[i], &r[i], &c[i]);
	}
	
	for (int w = a; w >= 0; w--) {
		dp[w] = w * (ll)1e9;
	}
	
	for (int w = a; w >= 0; w--) {
		for (int i = 0; i < n; i++) {
			if (w + r[i] > a) {
				continue;
			}
			dp[w] = max(dp[w], Q[i].q.front() - c[i]);
		}		
		for (int i = 0; i < n; i++) {
			if (w + r[i] > a) {
				if (w + l[i] - 1 <= a) Q[i].push(dp[w + l[i] - 1]);
				continue;
			}
			Q[i].pop(dp[w + r[i]]);
			Q[i].push(dp[w - 1 + l[i]]);
		}
	}
	printf("%lld\n", dp[0]);

	return 0;
}