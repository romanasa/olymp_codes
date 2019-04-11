#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;

typedef tree<pair<ll, int>, null_type, less<pair<ll, int> >, rb_tree_tag, tree_order_statistics_node_update> megaset;

vector<megaset> Q1, Q2;

void initialize(long long n, long long m) {
}

int nv, q;
map<ll, int> M;

int get(ll x) {
	auto it = M.find(x);
	if (it != M.end()) return it->second;
	
	megaset T1, T2;
	Q1.push_back(T1);
	Q2.push_back(T2);
	return M[x] = nv++;
}

void update(long long x, long long y1, long long y2) {
	q++;
	int ind = get(x);
	Q1[ind].insert({ y1 - 1, q });
	Q2[ind].insert({ y2, q });
}

int query(long long x, long long y) {
	int ind = get(x);
	return Q1[ind].order_of_key(make_pair(y, -1)) - Q2[ind].order_of_key(make_pair(y, -1));
}
