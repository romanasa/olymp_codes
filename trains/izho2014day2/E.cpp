#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
int a[dd], dp1[dd], dp2[dd];
pair<int, int> st[dd];

#define TASK "blocks"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n, k;
	cin >> n >> k;
	
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		dp1[i] = max(a[i], dp1[i - 1]);
	}
	
	for (int it = 2; it <= k; it++) {
		int sz = 0;
		
		for (int i = 1; i <= n; i++) {
            int ans = (it <= i ? dp1[i - 1] : (int)1e9);
            dp1[i - 1] = dp2[i - 1];
            while(sz and a[i] >= st[sz - 1].first)
                ans = min(ans, st[--sz].second);
            if(!sz or a[i] + ans < st[sz - 1].first + st[sz - 1].second)
                st[sz++] = make_pair(a[i], ans);
            dp2[i] = st[sz - 1].first + st[sz - 1].second;
        }
		dp1[n] = dp2[n];
	}
	cout << dp1[n] << "\n";
	return 0;
}