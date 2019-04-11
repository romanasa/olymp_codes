#include <bits/stdc++.h>
#define x first
#define y second
#define mp make_pair
#define all(a) a.begin(), a.end()
#define pub push_back
#define ll long long
using namespace std;
#include "simurgh.h"
 
struct vert{
	int pred, r;
};

struct cnm{
	vert t[505];
	cnm(){ for (int i = 0; i < 505; i++) t[i].pred = i, t[i].r = 0; }

	void clear(){ for (int i = 0; i < 505; i++) t[i].pred = i, t[i].r = 0; }

	int get(int v){
		if (t[v].pred == v) return v;
		t[v].pred = get(t[v].pred);
		return t[v].pred;
	}

	void merge(int a, int b){
		a = get(a), b = get(b);
		if (a != b){
			if (t[a].r < t[b].r) swap(a, b);
			t[b].pred = a;
			if (t[a].r == t[b].r) t[a].r++;
		}
	}
};

int zz = 0;
int ask(vector<int> a){
	zz++;
	if (zz > 8200 - 10) assert(0);
	return count_common_roads(a);
}

int n, m;
cnm tt;
vector<pair<int, int> > g[505];
vector<pair<int, int> > g2[505];
vector<int> q;
int startVal;
int type[505 * 505];
vector<int> w1, w2;

vector<int> st, now;
void dfs(int v, int pred, int find){
	if (v == find) now = st;
	for (auto to : g[v]) if (to.x != pred){
		st.pub(to.y);
		dfs(to.x, v, find);
		st.pop_back();
	}	
}	

map<pair<int, int>, int> ma;

int getDelta(int a, int b){
	if (ma.find(mp(a, b)) != ma.end()) return ma[mp(a, b)];
	vector<int> gg;
	for (int x : q) if (x != a) gg.pub(x);
	gg.pub(b);
	int vvv = ask(gg) - startVal;
	ma[mp(a, b)] = vvv;
	return vvv;
}

int getCount(vector<int> a){
	vector<int> gg;
	int sum = 0;
	tt.clear();

	for (int x : a){
		int a = w1[x], b = w2[x];
		tt.merge(a, b);
		gg.pub(x);
	}

	for (int x : q){
		int a = w1[x], b = w2[x];
		if (tt.get(a) != tt.get(b)) {
			sum += type[x];
			tt.merge(a, b);
			gg.pub(x);
		}
	}

	return ask(gg) - sum;
}	

int getNext(int v, int l, int r){
	vector<int> now;
	for (int i = l; i <= r; i++) now.pub(g2[v][i].y);
	if (getCount(now) == 0) return -1;

	int vl = l - 1, vr = r + 1;
	while(vl + 1 < vr){
		int vm = (vl + vr) >> 1;
		vector<int> now;
		for (int i = l; i <= vm; i++) now.pub(g2[v][i].y);
		if (getCount(now) == 0)
			vl = vm;
		else
			vr = vm;
	}
	if (vr == r + 1) return -1;
	return vr;
}

vector<int> find_roads(int N, vector<int> ww1, vector<int> ww2){
	n = N, m = ww1.size(); w1 = ww1, w2 = ww2;

	for (int i = 0; i < m; i++){
		int a = w1[i], b = w2[i];
		g2[a].pub(mp(b, i));
		//g2[b].pub(mp(a, i));
		if (tt.get(a) != tt.get(b)){
			tt.merge(a, b);
			q.pub(i);
			g[a].pub(mp(b, i));
			g[b].pub(mp(a, i));
		}
	}

	for (int i = 0; i < m; i++) type[i] = -1;

	startVal = ask(q);

	for (int i = 0; i < m; i++){
		bool f = 0;
		for (int x : q) if (x == i) f = 1;
		if (f) continue;

		int a = w1[i], b = w2[i];

		dfs(a, -1, b);

		f = 0;
		for (int x : now) if (type[x] == -1) f = 1;
		if (!f) continue;

		type[i] = 0;
		for (int x : now){
			int val = getDelta(x, i);	
			if (type[x] != -1){
				type[i] = type[x] ^ abs(val);
				break;
			}
			if (val == 1) type[i] = 1;
			if (val != 0) break;
		}

		for (int x : now) if (type[x] == -1) {
			type[x] = type[i] ^ abs(getDelta(x, i));
		}
	}

	for (int x : q) if (type[x] == -1) type[x] = 1;

	//==============================================================

	for (int i = 0; i < n; i++){
		int l = 0, r = (int)g2[i].size() - 1;
		while(1){
			if (l > r) break;
			int v = getNext(i, l, r);
			//cout << i << "=====" << v << ' ' << l << ' ' << r << endl;
			if (v == -1) break;
			type[g2[i][v].y] = 1;
			l = v + 1;
		}
	}

	//==============================================================

	vector<int> ans;

	for (int i = 0; i < m; i++) if (type[i] == 1) ans.pub(i);

	sort(all(ans));
	return ans;
}
