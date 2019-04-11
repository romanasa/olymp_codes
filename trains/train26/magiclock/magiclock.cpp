#include <stdint.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include "grader.h"

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int ok;

const ll maxC = (ll)5e18 + 7;
ll C[41];

void precalc(int n) {
	ok = 1;
	C[0] = 1;
	for (int i = 1; i <= n; i++) {
		C[i] = 0;
		for (int j = 0; j < i; j++) {
			if (C[i] == maxC) continue;
			double tmp = 1.0 * C[j] * C[i - j - 1] + C[i];
			if (tmp >= maxC) C[i] = maxC;
			else C[i] += C[j] * C[i - j - 1];
		}
		//err("C[%d] = %I64d\n", i, C[i]);
	}
}

void go(int l, int r, ll k, int *ans) {
	if (l > r) return;
	/*if (l + 1 == r) {
		ans[l] = r;
		ans[r] = l;
		return; 
	}*/
	
	int len = (r - l + 1) / 2;
	for (int j = l + 1; j <= r; j += 2) {
		int t = (j - l) / 2;
		double tmp = C[t] * C[len - 1 - t];
		
		ll cur;
		if (tmp >= maxC) cur = maxC;
		else cur = C[t] * C[len - 1 - t];
		
		if (cur > k) {
			ans[l] = j, ans[j] = l;

			go(l + 1, j - 1, k / C[len - 1 - t], ans);
			go(j + 1, r, k % C[len - 1 - t], ans);
			break;
		} else {
			k -= cur;
		}
	}
}

void solve (int n, int64_t k, int *answer) {
	precalc(n);
	go(1, 2 * n, k - 1, answer);
}
