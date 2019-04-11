#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
struct edge { 
    int to, ind, tim; 
    edge() {}
    edge(int to, int ind, int tim): to(to), ind(ind), tim(tim) {}
    bool operator < (const edge &b) const { return tim < b.tim; }
};
 
vector<vector<edge> > E;
int n;
int m;

const int C = 450;
 
const int dd = (int)1e5 + 7;
pair<int, int> go[dd];
 

pair<int, int> get(int v, int cur) {
	int it = lower_bound(E[v].begin(), E[v].end(), edge(-1, -1, cur)) - E[v].begin();
	if (it == (int)E[v].size()) return { v, (int)2e9 };
	return { E[v][it].to, E[v][it].tim };
}

void calc() {
    for (int i = 0; i < n; i++) sort(E[i].begin(), E[i].end());
     
    for (int i = 0; i < n; i++) {
        for (auto c : E[i]) {
            
        
        	int st = c.tim;
        	
        	int v = c.to, cur = c.tim;
        	while (1) {
        		auto p = get(v, cur);
        		if (cur > st + C) {
        			go[c.ind] = p;
        			break;
        		}
        		v = p.first;
        		cur = p.second;
        	}
        }
    }
}
 
void init(int n, int m, const int *t, const int *a, const int *b) {
    ::n = n, ::m = m;
    E.resize(n);
    for (int i = 0; i < m; i++) if (a[i] != b[i]) E[a[i]].push_back({ b[i], i, t[i] });
    calc();
}
 
int get(int t1, int t2, int a) {
    int cur = t1, v = a;
    while (1) {
    	int it = lower_bound(E[v].begin(), E[v].end(), edge(-1, -1, cur)) - E[v].begin();    
        if (it == (int)E[v].size()) return v;
        if (E[v][it].tim >= t2) return v;
		int num = E[v][it].ind;
		if (go[num].second < t2) {
			v = go[num].first;
			cur = go[num].second;
		} else {
            cur = E[v][it].tim;
            v = E[v][it].to;
        }
    }
}
 
void add(int t, int a, int b) {
	if (a == b) return;
    E[a].push_back({ b, m++, t });
    calc();
}