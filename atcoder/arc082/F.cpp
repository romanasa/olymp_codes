#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;
int r[dd], t[dd];
int ans[dd], cur[dd];
int ind[dd];
map<int, vector<pair<int, int> > > ask;
int X, K;

void go(int l, int rt, int st) {
	cur[l] = st;
	for (int i = l; i < rt; i++) {
		if (cur[i] < 0) cur[i] = 0;
		if (cur[i] > X) cur[i] = X;
		cur[i + 1] = cur[i] + (i % 2 ? r[i] : -r[i]);
	}
	if (cur[rt] < 0) cur[rt] = 0;
	if (cur[rt] > X) cur[rt] = X;
}

int main() {
	scanf("%d", &X);
	scanf("%d", &K);
	
	for (int i = 0; i < K; i++) scanf("%d", &t[i]);
	for (int i = 0; i < K; i++) r[i] = t[i] - (i ? t[i - 1] : 0);
	
	for (int i = 0; i < K; i++) err("%d, ", r[i]); err("\n");	
	
	int q;
	scanf("%d", &q);
	for (int it = 0; it < q; it++) {
		int t, a;
		scanf("%d %d", &t, &a);
		ask[a].push_back({ t, it });
	}
	
	go(0, K, X);
	err("cur = "); for (int i = 0; i <= K; i++) err("%d, ", cur[i]); err("\n");
	err("r = "); for (int i = 0; i <= K; i++) err("%d, ", r[i]); err("\n");
	
	ind[0] = 0;
	for (int i = 1; i <= K; i++) {
		ind[i] = ind[i - 1];
		if (cur[i] < cur[ind[i]]) ind[i] = i;
	}

	err("ind = "); for (int i = 0; i <= K; i++) err("%d, ", ind[i]); err("\n");
	
	int last = K;
	int curX = X;
	int add = 0;
	
	while (last >= 0) {
		int pos = ind[last];
		int val = cur[pos] - add;

		int nadd = add;
		
		add += val;
		int nX = curX - val;	
		
		err("ask [%d; %d]\n", nX, curX);
		err("add = %d, last = %d\n", nadd, last);
		err("cur = "); for (int i = 0; i <= K; i++) err("%d, ", cur[i]); err("\n");
		for (auto it = ask.lower_bound(nX); it != ask.end() && it->first <= curX; ++it) {
		
			int a = it->first;
		
			for (auto c : it->second) {
			
				int ind = upper_bound(t, t + K, c.first) - t - 1;
				
				err("ind = %d, c.second = %d\n", ind, c.second);
				
				int q = c.first - (ind >= 0 ? t[ind] : 0);
				
				if (ind + 1 > last)
					ans[c.second] = cur[ind + 1] + (ind % 2 ? -q : q);
				else
					ans[c.second] = (cur[ind + 1] - nadd) - (curX - a) + (ind % 2 ? -q : q);
					
				if (ans[c.second] < 0) ans[c.second] = 0;
				if (ans[c.second] > X) ans[c.second] = X;
				
			}
		}
		go(pos, last, 0);
		last = pos - 1;
		curX = nX;
	}
	
	for (int i = 0; i < q; i++) printf("%d\n", ans[i]);

	return 0;
}