#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;
const int mod = (int)1e9 + 7;

#define TASK "subsequences"

int P[dd], A[dd];

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	
    map<int, int> pos;
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        P[i + 1] = P[i] * 2 + 2;
        while (P[i + 1] >= mod) P[i + 1] -= mod;
        if (pos.count(A[i])) P[i + 1] -= P[pos[A[i]]] + 1;
        while (P[i + 1] < 0) P[i + 1] += mod;
        pos[A[i]] = i;
        ans += P[i + 1];
        if (ans >= mod) ans -= mod;
    }
	
	printf("%d\n", ans);
	return 0;
}