#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const ll maxC = (1ll << 32);

struct edge {
	int v, to;
	ll f, c, w, back;
};

vector<vector<edge> > E;

void add(int a, int b, ll c, ll w) {
	int ia = (int)E[b].size();
	int ib = (int)E[a].size();
	E[a].push_back({ a, b, 0, c, w, ia });
	E[b].push_back({ b, a, 0, 0, -w, ib });
	
	//err("%d--->%d, c = %I64d, w = %I64d\n", a, b, c, w);
	
}

int N;

ll fb(int s, int t) {
    vector<ll> d(N, (ll)8e18);
    vector<int> used(N, false);
    vector<pair<int, int> > p(N, {-1, -1 });

    queue<int> q;

    q.push(s);
    used[s] = true;
    d[s] = 0;

    while (q.size()) {
        int v = q.front();

        used[v] = false;
        q.pop();

        for (int i = 0; i < (int)E[v].size(); i++) {

            auto &e = E[v][i];

            if (e.f < e.c && d[e.to] > d[v] + e.w ) {

                p[e.to] = { v, i };
                d[e.to] = d[v] + e.w;

                if (!used[e.to]) {
                    q.push(e.to);
                    used[e.to] = true;
                }
            }
        }
    }

    //err("d[t] = %I64d\n", d[t]);
	//err("p[t] = %d, %d\n", p[t].first, p[t].second);
    
	if (d[t] == (ll)8e18) return -1;
	
    ll add = maxC;
    ll cost = 0;

    for (int i = t; p[i].first != -1; i = p[i].first) {
        add = min(add, E[p[i].first][p[i].second].c - E[p[i].first][p[i].second].f);
    }
    
    //err("add = %I64d\n", add);

    for (int i = t; p[i].first != -1; i = p[i].first) {
        auto &e = E[p[i].first][p[i].second];
        cost += 1ll * add * e.w;
        e.f += add;
        E[e.to][e.back].f -= add;
    }
   
    return cost;
}

ll findflow(int s, int t) {
    ll cost = 0;
    while (1) {
        ll dc = fb(s, t);
        if (dc == -1) break;
        cost += dc;
    }
    return cost;
}

int main() {
	int n, m;
	cin >> n >> m;
	
	N = n + 5;
	int S = n + 4;
	int T = n + 3;
	
	E.resize(N);
	
	vector<ll> a(n + 1);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		//cout << a[i] << " ";
	}
	
	add(0, T, a[0], 0);
	for (int i = 1; i <= n; i++) {
		if (a[i - 1] < a[i]) add(i, T, a[i] - a[i - 1], 0);
		else add(S, i, a[i - 1] - a[i], 0);
	}
	
	for (int i = 0; i + 1 <= n; i++) add(i, i + 1, maxC, 0);
	
	for (int i = 0; i < m; i++) {
		ll l, r, c;
		cin >> l >> r >> c;
		l--, r--;
		add(r + 1, l, maxC, c);
	}
	cout << findflow(S, T);
	return 0;
}