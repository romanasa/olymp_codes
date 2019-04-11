#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)

using namespace std;

const int dd = (int)2e5 + 7;

pair<int, int> T[dd];
set<pair<ll, int> > P;

vector<int> find_subset(int l, int u, vector<int> w) {
    int n = (int)w.size();

    for (int i = 0; i < n; i++)
        T[i] = { w[i], i };

    sort(T, T + n);

    ll cur = 0;

    for (int i = 0; i < n; i++) {
        P.insert({ cur, i });
        cur += T[i].first;

        auto it = P.lower_bound({ cur - u, 0 });
        if (it != P.end() && cur - it->first >= l) {
            vector<int> ans;
            for (int j = it->second; j <= i; j++) {
                ans.push_back(T[j].second);
            }
            return ans;
        }
    }
	return vector<int>(0);
}
