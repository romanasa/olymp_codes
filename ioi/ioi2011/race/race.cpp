#include <bits/stdc++.h>
#define ll long long

#ifdef HOME
	#include "race.h"
#else
	#include "grader.h"
#endif

using namespace std;

vector<vector<pair<ll, ll> > > E;

ll len;
ll ans = (ll)1e9 + 1;

struct ev {
	ll push = 0, push2 = 0;
	map<ll, ll> M;
};

ev dfs(ll v, ll pr) {
	ev cur;
	cur.M[0] = 0;
	cur.push = cur.push2 = 0;
	
	for (auto c : E[v]) {
		if (c.first == pr) continue;
		
		ev t = dfs(c.first, v);
		
		t.push += c.second;
		t.push2++;
		
		if (t.M.size() > cur.M.size()) {
			swap(t.push, cur.push);
			swap(t.push2, cur.push2);
			swap(t.M, cur.M);
		}
		
		
		
		for (auto c : t.M) {
			auto it = cur.M.find(len - (c.first + t.push) - cur.push);
			if (it != cur.M.end()) {
				ans = min(ans, c.second + t.push2 + it->second + cur.push2);
			}
		}
		
		for (auto c : t.M) {
			
			ll a = (c.first + t.push) - cur.push;
			ll b = (c.second + t.push2) - cur.push2;
			
			if (a + cur.push > len) continue;
			
			auto it = cur.M.find(a);
			if (it != cur.M.end())
				it->second = min(it->second, b);
			else
				cur.M[a] = b;
		}
	}
	return cur;
} 

int best_path(int N, int K, int H[][2], int L[]) {
	
	E.resize(N);
	len = K;
	
	for (int i = 0; i < N - 1; i++) {
		E[H[i][0]].push_back({ H[i][1], L[i] });
		E[H[i][1]].push_back({ H[i][0], L[i] });
	}
	dfs(0, -1);
	return (ans == (ll)1e9 + 1 ? -1 : ans);
}

