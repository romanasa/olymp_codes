#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 17;

int n;
char s[dd], t[dd];
int d[(1 << dd) + 7];

int main() {
	scanf("%d", &n);
	scanf("%s", s);
	scanf("%s", t);
	
	int st = 0;
	for (int i = 0; i < n; i++) if (s[i] == '1') st ^= (1 << i);
	
	fill(d, d + (1 << n), (int)1e9);
	
	queue<int> q;
	
	d[st] = 0;
	q.push(st);
	
	while (q.size()) {
		int msk = q.front();
		q.pop();
		
		
		for (int i = 0; i < n; i++) {
			int cur = msk ^ (1 << i);
			if (d[cur] > d[msk] + 1) d[cur] = d[msk] + 1, q.push(cur);
		}
		
		{
			int cur = msk >> 1;
			if (msk & 1) cur ^= (1 << (n - 1));
			if (d[cur] > d[msk] + 1) d[cur] = d[msk] + 1, q.push(cur);
		}
		
		{
			int cur = msk << 1;
			if ((msk >> (n - 1)) & 1) {
				cur ^= (1 << n);
				cur ^= 1;
			}
			if (d[cur] > d[msk] + 1) d[cur] = d[msk] + 1, q.push(cur);
		}
	}
	
	int ans = (int)1e9;
	for (int msk = 0; msk < (1 << n); msk++) {
		int ok = 1;
		for (int i = 0; i < n; i++) if (t[i] != '?') {
			ok &= (t[i] - '0') == ((msk >> i) & 1);
		}
		if (ok) {
			ans = min(ans, d[msk]);
			err("%d\n", msk);
		}
	}
	printf("%d\n", ans);
	
	return 0;
}