#include <cstdio>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;

const int maxC = (int)1e6 + 7;
#ifdef HOME
	const int dd = (int)3e2 + 7;
#else
	const int dd = (int)3e5 + 7;
#endif

const int MAXMEM = (int)2e8;
char MEM[MAXMEM];
int mpos;

inline void* operator new(size_t n) {
	char *res = MEM + mpos;
	mpos += n;
	return (void*)res;
}

inline void operator delete(void*) {}

//vector<pair<int, int> > E[maxC];
ll cnt[maxC];
const int mod = (int)1e9 + 9;

vector<pair<int, pair<int, int> > > E;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> megaset;

struct dsu {
	int P[dd];
	megaset S[dd];
	
	dsu() { for (int i = 0; i < dd; i++) P[i] = i, S[i].insert(i); }
	
	int get(int v) { return P[v] == v ? v : P[v] = get(P[v]); }
	
	int cnt(int v) { return (int)S[v].size(); }
	
	void un(int a, int b) {
		if (cnt(a) < cnt(b)) swap(a, b);
		
		while (S[b].size()) {
			S[a].insert(*S[b].begin());
			S[b].erase(S[b].begin());
		}
		P[b] = a;
	}
	
	int getG(int v, int x) { return (int)S[v].size() - S[v].order_of_key(x + 1); }
	int getC(int v, int x) { return S[v].find(x) != S[v].end(); }
	
} J;

ll bp(ll a, ll n) {
	if (!n) return 1;
	if (n & 1) return bp(a, n - 1) * a  % mod;
	ll t = bp(a, n / 2);
	return t * t % mod;
}

int calculate(int n, int m, int *a, int *b, int *c) {

	for (int i = 0; i < n - 1; i++) {
		E.push_back({ c[i], { min(a[i], b[i]) - 1, max(a[i], b[i]) - 1 } });
	}
	
	ll cur = 0;
	
	sort(E.begin(), E.end());
	int j = 0;
	
	for (int x = 1; x <= m; x++) {
		cnt[x] = cur;
	
		while (j < (int)E.size() && E[j].first == x) {
			auto c = E[j];
			int a = c.second.first, b = c.second.second;
			int pa = J.get(a), pb = J.get(b);
			
			cur += (1ll * J.cnt(pa) * J.cnt(pb) - 1);
			
			if (J.getC(pa, a)) cnt[x] += J.getG(pb, b);
			if (J.getC(pb, a)) cnt[x] += J.getG(pa, b);
			cnt[x] += 1ll * J.getG(pa, a) * J.getG(pb, a);
			
			J.un(pa, pb);
			j++;
		}
	}
	
	ll ans = 1;
	for (int x = 1; x <= m; x++) {
		ans *= bp(m - x + 1, cnt[x] - cnt[x - 1]);
		ans %= mod;
	}
	if (cnt[m] < 1ll * (n - 2) * (n - 1) / 2) return 0;
	
    return (int)ans;
}
