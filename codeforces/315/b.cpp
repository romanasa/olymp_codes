#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:66777216")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>
#include <unordered_set>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (ll i = 0; i < (ll)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "kthsubstr"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int inf = (int)2e9 + 1;
const ll linf = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int n, m;
vector<vector<int> > e;

vector<int> bfs(int st) {
	vector<int> d(n, inf);
	d[st] = 0;
	queue<int> q;
	q.push(st);
	while (q.size()) {
		int v = q.front();
		q.pop();

		for (int to: e[v]) 
			if (d[to] > d[v] + 1) {
				d[to] = d[v] + 1;
				q.push(to);
			}
	}
	return d;
}

struct req {
	int x, tp, ind;
	req() {}
	req(int x, int tp, int ind) : x(x), tp(tp), ind(ind) {}
	bool operator < (req b) const {
		if (x == b.x) {
			if (tp == b.tp)
				return ind < b.ind;
			return tp < b.tp;
		}
		return x < b.x;
	}
};


int main() {
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
  	cin >> n >> m;
  	e.resize(n);
  	vector<pair<int, int> > al;
  	forn(i, m) {
  		int a, b;
  		cin >> a >> b;
  		e[a - 1].pk(b - 1);
  		e[b - 1].pk(a - 1);
  		al.pk({a - 1, b - 1});

    }
    auto d = bfs(0);
	
	for(int x: d)
		cerr << x << " ";
	cerr << "\n";

	vector<req> pt;
	vector<int> inn(n), out(n), good(m);
                            
	forn(i, m) {
		int a = al[i].first, b = al[i].second;
		if (d[a] > d[b])
			swap(a, b);
		if (d[a] == d[b])
			continue;
		pt.pk(req(d[a], 1, i));
		pt.pk(req(d[b], 0, i));
		inn[d[a]]++, out[d[b]]++;
		cerr << d[a] << " - " << d[b] << "\n";
	}

	sort(all(pt));
	                     	              
    int op = 0, cl = 0, ans = 0;
	forn(i, pt.size() - 1) {
		
		cerr << pt[i].ind << " " << pt[i].tp << " " << pt[i].x << "\n";
		if (op == cl && pt[i].ind == pt[i + 1].ind && inn[pt[i].x] == 1 && out[pt[i + 1].x] == 1)
			good[pt[i].ind] = 1, ans++;
                          
		op += pt[i].tp;
		cl += 1 - pt[i].tp;
	}

	cout << ans << "\n";
	forn(i, m) {           		
		if (good[i])
			cout << i + 1 << " ";
	}
}
