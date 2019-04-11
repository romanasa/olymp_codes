#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e6 + 7;
int a[dd], l[dd], r[dd];
int nxt[dd];
map<int, vector<int> > M;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) cin >> a[i];
	
	
	fill(r, r + n, n);
	fill(l, l + n, -1);
	
	vector<int> st;
	for (int i = 0; i < n; i++) {
		while (st.size() && a[st.back()] >= a[i]) r[st.back()] = i, st.pop_back();
		st.push_back(i);
	}
	
	st.clear();
	for (int i = n - 1; i >= 0; i--) {
		while (st.size() && a[st.back()] <= a[i]) l[st.back()] = i, st.pop_back();
		st.push_back(i);
	}
	
	for (int i = 0; i < n; i++) M[a[i] - i].push_back(i);
	
    fill(nxt, nxt + n, -1);
    	
	for (auto c : M) {
		vector<pair<pair<int, int>, int> > E;
    	for (int i : c.second) {
    		int a = lower_bound(c.second.begin(), c.second.end(), i + 1) - c.second.begin();
    		int b = upper_bound(c.second.begin(), c.second.end(), r[i] - 1) - c.second.begin() - 1;
    		if (a <= b) {
    			E.push_back({ { c.second[a], -1 }, i });
    			E.push_back({ { c.second[b], 1 }, i });
    		}
    	}
    	
    	sort(E.begin(), E.end());
    	int j = 0;
    	
    	set<int> S;
    	for (int i : c.second) {
    		while (j < (int)E.size() && E[j].first.first == i && E[j].first.second == -1)
    			S.insert(E[j].second), j++;
    		while (S.size() && l[i] < *S.rbegin()) {
    			nxt[*S.rbegin()] = i;
    			S.erase(--S.end());
    		}
    		while (j < (int)E.size() && E[j].first.first == i && E[j].first.second == 1)
    			S.erase(E[j].second), j++;
    	}
	}
	
	vector<pair<int, int> > ans, t;
	for (int i = 0; i < n; i++) if (nxt[i] != -1) ans.push_back({ i, i }), ans.push_back({ nxt[i], i });
	
	sort(ans.begin(), ans.end());
	for (int i = 0; i < n; i++) if (nxt[i] != -1 && upper_bound(ans.begin(), ans.end(), make_pair(i, i))->second == i)
		t.push_back({ i, nxt[i] });
	
	cout << t.size() << "\n";
	for (auto c : t) cout << c.first + 1 << " " << c.second + 1 << "\n";
	
	return 0;
}