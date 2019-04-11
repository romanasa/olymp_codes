#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = 501;
int c1[dd], c2[dd], r1[dd], r2[dd], cnt[dd];

int pos[dd], used[10 * dd];
vector<int> go[10 * dd];

int N;

struct edge {
    int v, to, c, f, w, back;
};

vector<vector<edge> > E;

void add(int a, int b, int c, int w) {
    int ia = E[b].size(), ib = E[a].size();

    edge cur{ a, b, c, 0,  w, ia };
    edge rev{ b, a, 0, 0, -w, ib };

    E[a].push_back(cur);
    E[b].push_back(rev);
}

ll fb(int s, int t) {
    vector<int> d(N, (int)1e9);
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

    int add = (int)1e9;
	int flow = 0;
	
    for (int i = t; p[i].first != -1; i = p[i].first) {
        add = min(add, E[p[i].first][p[i].second].c - E[p[i].first][p[i].second].f);
    }
	
    for (int i = t; p[i].first != -1; i = p[i].first) {
        auto &e = E[p[i].first][p[i].second];
        e.f += add;
        flow = add;
        E[e.to][e.back].f -= add;
    }

    return flow;
}

ll findflow(int s, int t) {
    ll cost = 0;
    while (1) {
        ll dc = fb(s, t);
        if (!dc) break;
        cost += dc;
    }
    return cost;
}


int main() {
	int n;
	scanf("%d", &n);
	
	int m;
	scanf("%d", &m);
	
	for (int i = 0; i < m; i++) scanf("%d", &r1[i]);
	for (int i = 0; i < m; i++) scanf("%d", &r2[i]);
	for (int i = 0; i < m; i++) scanf("%d", &c1[i]);
	for (int i = 0; i < m; i++) scanf("%d", &c2[i]);
	for (int i = 0; i < m; i++) scanf("%d", &cnt[i]);
	
	N = 3 * n + 2 * m + 7;
	E.resize(N);
	
	int s = 3 * n + 2 * m + 1;
	int t = 3 * n + 2 * m + 2;
	
	for (int i = 0; i < n; i++) {
		add(s, i, 1, 0);
		for (int j = 0; j < m; j++) if (r1[j] <= i && i <= r2[j])
			add(i, n + 2 * j, 1, 0);
		add(i, n + 2 * m + i, 1, 1);
	}
	
	for (int i = 0; i < m; i++) {
		add(n + 2 * i, n + 2 * i + 1, cnt[i], -1);
		for (int j = c1[i]; j <= c2[i]; j++) {
			add(n + 2 * i + 1, 2 * n + 2 * m + j, 1, 0);
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int ok = 0;
			for (int t = 0; t < m; t++) ok |= (r1[t] <= i && i <= r2[t] && c1[t] <= j && j <= c2[t]);
			if (!ok) {
				add(n + 2 * m + i, 2 * n + 2 * m + j, 1, 0);
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		add(2 * n + 2 * m + i, t, 1, 0);
	}	
	
	int f = findflow(s, t);
	
	/*for (int i = 0; i < N; i++) {
		for (auto &e : E[i]) {
			if (e.f > 0 && e.c == e.f) {
				err("%d --%d--> %d\n", i, e.f, e.to);
			}
		}
	}*/
	
	fill(pos, pos + n, -1);
	
	for (int i = 0; i < n; i++) {
		for (auto &e : E[i]) {
			if (e.f > 0 && e.f == e.c) {
				go[e.to].push_back(i);
			}
		}
	}
	
	for (int i = 0; i < m; i++) {
		if (go[n + 2 * i].empty()) continue;
		
		for (auto &e : E[n + 2 * i + 1]) {
			if (e.f > 0 && e.f == e.c) {
				pos[go[n + 2 * i].back()] = e.to - 2 * n - 2 * m;
				//err("1, i = %d, j = %d\n", go[n + 2 * i].back(), e.to - 2 * n - 2 * m);
				go[n + 2 * i].pop_back();
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (auto &e : E[n + 2 * m + i]) {
			if (e.f > 0 && e.f == e.c) {
				pos[i] = e.to - 2 * n - 2 * m;
				//err("2, i = %d, j = %d\n", i, e.to - 2 * n - 2 * m);
			}
		}
	}
	
	//for (int i = 0; i < n; i++) err("%d, ", pos[i]);
	//err("\n");
	
	for (int i = 0; i < n; i++) if (pos[i] == -1) return 0 * puts("-1");
	
	for (int i = 0; i < n; i++) for (int j = 0; j < i; j++) assert(pos[i] != pos[j]);
	
	for (int t = 0; t < m; t++) {
		int q = 0;
		for (int i = 0; i < n; i++) q += (r1[t] <= i && i <= r2[t] && c1[t] <= pos[i] && pos[i] <= c2[t]);
		//err("q = %d, cnt = %d\n", q, cnt[t]);
		if (q != cnt[t]) return 0 * puts("-1");
	}
	
	for (int i = 0; i < n; i++) for (int j = 0; j < i; j++) assert(pos[i] != pos[j]);
	
	for (int i = 0; i < n; i++) printf("%d ", pos[i]);
	return 0;
}