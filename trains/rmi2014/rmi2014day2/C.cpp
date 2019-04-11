#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)5e3 + 1;
struct pt { ll x, y; int ind; };

ll dist(pt A, pt B) { return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y); }
double dist2(pt A, pt B) { return sqrt(dist(A, B)); }

mt19937 rnd(1);

vector<pair<ll, pair<int, int> > > G;

double ans = 0;
int n, k;
	
bool check(int i) {
	int add = 0;
	double cur = 0;
	
	for (auto c : G) {
		if (c.second.first == i || c.second.second == i) continue;
		cur += sqrtl(c.first);
		if (cur > ans) return true;
		add++;
		if (add == k) break;	
	}
	return false;
}

#define TASK "segments"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	scanf("%d %d", &n, &k);
	
	vector<pt> P(n);
	for (int i = 0; i < n; i++) { scanf("%I64d %I64d", &P[i].x, &P[i].y); P[i].ind = i; }
	
	int C = 10;
	
	for (int it = 0; it < 11; it++) {
		ll A = rnd(), B = rnd();
		sort(P.begin(), P.end(), [&A, &B](pt m, pt n) {
			return (A * m.x + B * m.y) < (A * n.x + B * n.y);
		});	
		for (int i = 0; i < (int)P.size(); i++) {
			for (int j = max(0, i - C); j < min((int)P.size(), i + C); j++) if (P[i].ind < P[j].ind) {
				G.push_back({ dist(P[i], P[j]), { P[i].ind, P[j].ind } });
			}
		}	
	}
	
	sort(G.begin(), G.end());
	G.resize(unique(G.begin(), G.end()) - G.begin());
	
	//err("G = "); for (auto c : G) err(" (%I64d, = (%d)-(%d) ), ", c.first, c.second.first, c.second.second);
	
	for (int i = 0; i < k; i++) ans += sqrtl(G[i].first);
	
	printf("%.6f\n", ans);
	for (int i = 0; i < n; i++) if (check(i)) printf("%d\n", i);
	
	return 0;
}