#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	int A, B, C;
	scanf("%d %d %d", &A, &B, &C);
	
	ll t;
	scanf("%I64d", &t);
	
	vector<int> st(m);
	multiset<int> S;
	for (int i = 0; i < m; i++) scanf("%d", &st[i]);
	
	int ans = 0;
	
	for (int i = 0; i + 1 < m; i++) {
		ll cur = 1ll * (st[i] - 1) * B;
		
		if (cur > t) break;
	
		int nxt = min(1ll * st[i + 1] - 1, st[i] + (t - cur) / A);

		ans += nxt - st[i] + 1;
		//err("i = %d, += %d\n", i, nxt - st[i] + 1);
		for (int j = 0; j < k; j++) {
			if (nxt + 1 >= st[i + 1]) break;
			
			ll q = cur + 1ll * (nxt + 1 - st[i]) * C;
			
			if (q > t) break;
			int w = min(1ll * st[i + 1] - 1, nxt + 1 + (t - q) / A);
			S.insert(w - nxt);
		
			nxt = w;
		}	
	}
	
	if (1ll * (n - 1) * B <= t) ans++;
	
	for (int i = m; i < k && S.size(); i++) {
		//err("+= %d\n", *S.rbegin());
		ans += *S.rbegin(); 
		S.erase(--S.end());
	}	
	
	printf("%d\n", ans - 1);
	return 0;
}