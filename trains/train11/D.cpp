#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;
typedef double ld;

const int dd = (int)1e5 + 1;

int s[dd], w[dd];
ld ans[dd];

#define TASK "downloading"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, v;
	scanf("%d %d", &n, &v);
	
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &s[i], &w[i]);
	}
	
	s[n] = (int)2e9 + 1, w[n] = 0;
	
	set<pair<ld, int> > S;
	
	S.insert({ w[0], 0 });
	ld q = 0, lst = s[0];
	int i = 1;
	
	while (i < n || S.size()) {
		//err("i = %d, q = %.3f\n", i, q);
		while (S.size() && fabs(q - S.begin()->first) <= 1e-9) {
			ans[S.begin()->second] = lst;
			S.erase(S.begin());
		}
		
		if (S.empty()) q = 0;
		ld have = (i < n ? s[i] - lst : 1e9);
		
		//err("i = %d, have = %.3f, lst = %.3f, sz = %d\n", i, have, lst, (int)S.size());
		
		if (S.size() && have * v * 1.0 >= (S.begin()->first - q) * (int)S.size()) {
			//err("1\n");
			lst = ans[S.begin()->second] = lst + (S.begin()->first - q) / (v * 1.0 / (int)S.size());
			q += (S.begin()->first - q);
			S.erase(S.begin());
			if (S.empty()) q = 0;
		} else {
			//err("2\n");
			//err("q += (%d - %.1f) / (%d / %d)\n", s[i], lst, v, (int)S.size()); 
			if (S.size()) q += (s[i] - lst) * (v * 1.0 / (int)S.size());
			else q = 0;
			
			lst = s[i];
			if (i < n) S.insert({ w[i] + q, i });
			i++;
		}
	}
	for (int i = 0; i < n; i++) printf("%.10f\n", (double)ans[i]);
	return 0;
}