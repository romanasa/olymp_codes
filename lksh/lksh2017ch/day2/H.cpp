#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxS = 100 * 1000 + 7;
const int dd = 107;

int dpA[maxS], dpB[maxS];
int A[dd], B[dd];

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#endif
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> A[i];

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) cin >> B[i];

    fill(dpA, dpA + maxS, (int)1e9);
    fill(dpB, dpB + maxS, (int)1e9);

    dpA[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = maxS - 1; j >= A[i]; j--) {
            dpA[j] = min(dpA[j], dpA[j - A[i]] + 1);
        }
    }

    dpB[0] = 0;
    for (int i = 0; i < m; i++) {
        for (int j = maxS - 1; j >= B[i]; j--) {
            dpB[j] = min(dpB[j], dpB[j - B[i]] + 1);
        }
    }

    int ans = (int)1e9;
    for (int i = 1; i < maxS; i++) {
        ans = min(ans, dpA[i] + dpB[i]);
    }
    if (ans == (int)1e9) puts("impossible");
    else cout << ans << "\n";

    return 0;
}
