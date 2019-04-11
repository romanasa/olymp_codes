#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int LOG = 60;

const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
	char *res = mem + mpos;
	mpos += n;
	return (void *)res;
}
inline void operator delete ( void * ) { } 

struct ev { 
	int tp;
	ll x;
	int y, ind; 
	bool operator < (const ev &b) const {
		return x == b.x ? tp < b.tp : x < b.x;
	}
};

const int dd = (int)2e5 + 1;

int ans[dd];

struct fen {
	int T[dd];
	void upd(int v, int val) {
		for (int i = v + 1; i < dd; i += (i&-i)) T[i] += val;
	}
	int get(int v) {
		int res = 0;
		for (int i = v + 1; i; i -= (i&-i)) res += T[i];
		return res;
	}
} F;

vector<ll> tmp;


struct Q {
	vector<pair<pair<ll, ll>, int>> cur;
	vector<ll> Gy;
	vector<ev> E;
	
	void add(ll x, ll y, int v) {
		cur.push_back({ { x, y }, v });
	}
	
	void build() {
		for (auto c : cur) {
			Gy.push_back(c.first.second);
		}
		sort(Gy.begin(), Gy.end()); 
		Gy.resize(unique(Gy.begin(), Gy.end()) - Gy.begin());	
		for (auto c : cur) {
			int x = c.first.first;
			int y = lower_bound(Gy.begin(), Gy.end(), c.first.second) - Gy.begin();
			int v = c.second;
			E.push_back({ 0, x, y, v });
		}
	}

	void addq(ll a, ll b, int ind) {
		ll x = a;
		int y = upper_bound(Gy.begin(), Gy.end(), b) - Gy.begin() - 1;
		if (y < 0) return;
		E.push_back({ 1, x, y, ind });
	}	
	
	void calc() {
		stable_sort(E.begin(), E.end());	
		for (auto &c : E) {
			if (c.tp == 0) F.upd(c.y, c.ind);
			else ans[c.ind] += F.get(c.y);
		}
		for (auto &c : E) {
			if (c.tp == 0) F.upd(c.y, -c.ind);
		}
	}
};

map<pair<ll, ll>, Q> M[LOG][LOG];

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	
	for (int i = 0; i < n; i++) {
		ll x, y, v, px, py;
		scanf("%lld %lld %lld", &x, &y, &v);
		
		px = 0;
		while ((1ll << px) <= x) px++;
		px--;
		
		py = 0;
		while ((1ll << py) <= y) py++;
		py--;
		
		M[px][py][{ x % (1ll << px), y % (1ll << py) }].add(x, y, v);
	}
	
	for (int i = 0; i < LOG; i++) {
		for (int j = 0; j < LOG; j++) {
			for (auto &c : M[i][j]) {
				c.second.build();
			}
		}
	}
	
	for (int ii = 0; ii < q; ii++) {
		ll x, y;
		scanf("%lld %lld", &x, &y);
		
		for (int i = 0; i < LOG; i++) {
			for (int j = 0; j < LOG; j++) {
				ll mx = x & ((1ll << i) - 1);
				ll my = y & ((1ll << j) - 1);
				
				auto it = M[i][j].find(make_pair(mx, my));
				if (it == M[i][j].end()) continue;
				
				it->second.addq(x, y, ii);
			}
		}
	}
	
	for (int i = 0; i < LOG; i++) {
		for (int j = 0; j < LOG; j++) {
			for (auto &c : M[i][j]) {
				c.second.calc();
			}
		}
	}
	
	for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
	return 0;
}