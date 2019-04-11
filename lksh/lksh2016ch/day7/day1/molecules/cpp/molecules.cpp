#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)
using namespace std;

vector<int> find_subset(int l, int u, vector<int> w) {
	int n = (int)w.size();
	
	vector<pair<int, int> > T(n);
	for (int i = 0; i < n; i++)
		T[i] = { w[i], i };
		
	sort(T.begin(), T.end());
	
	ll t = 0;
	
	multiset<pair<int, int> > S;
	vector<int> used(n);
	
	for (int i = 0; i < n; i++) {
		if (T[i].first + t <= u) {
			t += T[i].first;
			S.insert(T[i]);
			used[T[i].second] = 1;
		}
	}
	
	
	/*
	err("S :");
	for (auto c : S)
		err("(%d; %d), ", c.first, c.second);
	err("\n");
	*/
	
	for (int i = n - 1; i >= 0; i--) {
		
		if (used[T[i].second])
			continue;
			
		ll x = t + T[i].first - u;
		auto it = S.lower_bound(make_pair(x, -1));
		
		//err("%d ---> (%d; %d)\n", T[i].first, it->first, it->second);
		
		if (it != S.end() && T[i].first > it->first) {
		
			used[it->second] = 0;
			used[T[i].second] = 1;
		
			t = t + T[i].first - it->first;
			S.erase(it);
			S.insert(T[i]);			
		}
		/*
		err("S :");
		for (auto c : S)
			err("(%d; %d), ", c.first, c.second);
		err("\n");*/
	}
	
	
	if (t < l)
    	return vector<int>(0);
    vector<int> ans;
	for (auto c : S)
		ans.push_back(c.second);
	return ans;
}
