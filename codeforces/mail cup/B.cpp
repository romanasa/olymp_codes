#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int p[123456];

int get(int v) { return v == p[v] ? v : p[v] = get(p[v]); }

int c;
int cnt;

void un(int a, int b) {
	a = get(a);
	b = get(b);
	if (a != b) p[b] = a, c++;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, l;
	cin >> n >> m >> l;
	
	c = 0;
	
	for (int i = 0; i <= n; i++) p[i] = i;
	
	vector<ll> a(n + 1);
	
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] > l) cnt++;
		if (i && a[i] > l && a[i - 1] > l) un(i, i - 1);
	}
	
	while (m--) {
		int tp; cin >> tp;
		
		
		if (tp == 0) cout << cnt - c << "\n";
		else {
			int v, d;
			cin >> v >> d;
			v--;
			
			a[v] += d;
			if (a[v] - d <= l && a[v] > l) cnt++;
			if (a[v] > l && a[v + 1] > l) un(v, v + 1);
			if (v && a[v - 1] > l && a[v] > l) un(v - 1, v);
		}
	}
	
	return 0;
}