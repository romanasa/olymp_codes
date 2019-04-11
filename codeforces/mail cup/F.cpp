// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx") 
#pragma GCC optimize("O3")

#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e6 + 1;

vector<vector<pair<int, ll>>> E;
ll p[dd];


void dfs(int v, int pr, ll cur) {
	p[v] = cur;
	for (auto c : E[v]) if (c.first != pr)
		dfs(c.first, v, cur ^ c.second);
}

pair<ll, int> res[dd], T[dd], Q[dd];
int ires = 0;
int n;

void mySort(pair<ll, int> *A, int j, ll msk) {
	ires = 0;
	for (int i = 0; i < n; ) {
		int pos = i;
		while (pos < n && (A[pos].first & msk) == (A[i].first & msk)) {
			pos++;
		}
		for (int t = i; t < pos; t++) if (((A[t].first >> j) & 1) == 0) {
			res[ires++] = A[t];
		}
		for (int t = i; t < pos; t++) if ((A[t].first >> j) & 1) {
			res[ires++] = A[t];
		}
		i = pos;
	}
	for (int i = 0; i < ires; i++) A[i] = res[i];
}

ll calc(pair<ll, int> *A, pair<ll, int> *B, ll k) {

	int i = 0, j = 0;
	ll res = 0;
	while (i < n) {
	 
		int posA = i;
		ll cA = 0;
		
		while (i < n && A[i].first == A[posA].first) cA++, i++;
		
		ll cB = 0;
		
		while (j < n && B[j].first < A[posA].first) j++;
		while (j < n && B[j].first == A[posA].first) cB++, j++;
		
		res += cA * cB;
		
		if (i == n || j == n) break;
		if (res >= k) break;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	ll k;
	cin >> n >> k;
	
	E.resize(n);
	
	for (int i = 0; i + 1 < n; i++) {
		int p;
		ll w;
		cin >> p >> w;
		E[p - 1].push_back({ i + 1, w });
	}
	
	dfs(0, -1, 0ll);
	
	for (int i = 0; i < n; i++) T[i] = { 0, i };
	for (int i = 0; i < n; i++) Q[i] = { 0, i };
	
	ll f = 0;
	ll msk = 0;
	for (int j = 61; j >= 0; j--) {
		
		for (int i = 0; i < n; i++) {
			int ind = T[i].second;
			if ((p[ind] >> j) & 1) T[i].first ^= (1ll << j);
		}
		// sort(T, T + n);
		mySort(T, j, msk);
		
		for (int i = 0; i < n; i++) {
			int ind = Q[i].second;
			if (((p[ind] ^ f) >> j) & 1) Q[i].first ^= (1ll << j);
		}
		// sort(Q, Q + n);
		mySort(Q, j, msk);
		
		ll x = calc(Q, T, k);
		if (k > x) {
			k -= x;
			f ^= (1ll << j);
			for (int i = 0; i < n; i++) Q[i].first ^= (1ll << j);
			// sort(Q, Q + n);
			mySort(Q, j, msk);
		}
		msk ^= (1ll << j);
	}
	
	cout << f << "\n";
	return 0;
}
