#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int LOG = 18;
const int dd = (int)2e5 + 7;

int up[LOG][dd];
int h[dd];
int lca(int a, int b) {

    for (int i = LOG - 1; i >= 0; i--) if (h[up[i][a]] >= h[b]) a = up[i][a];
    for (int i = LOG - 1; i >= 0; i--) if (h[up[i][b]] >= h[a]) b = up[i][b];

    if (a == b) return a;

    for (int i = LOG - 1; i >= 0; i--) {
        if (up[i][a] != up[i][b]) {
            a = up[i][a], b = up[i][b];
        }
    }

    return up[0][a];
}

int dist(int a, int b) {
    int t = lca(a, b);
    return h[a] + h[b] - 2 * h[t];
}

int main() {
#ifdef WIN
    freopen("input.txt", "r", stdin);
#endif
    int n;
    scanf("%d", &n);

    for (int i = 0; i < LOG; i++) up[i][0] = 0;

    int A = 0, B = 0;
    int cur = 0;

    for (int i = 1; i < n; i++) {
        int p;
        scanf("%d", &p);
        p--;

        h[i] = h[p] + 1;
        up[0][i] = p;
        for (int t = 1; t < LOG; t++) up[t][i] = up[t - 1][up[t - 1][i]];

        int tmp;
        if ((tmp = dist(A, i)) > cur) B = i, cur = tmp;
        if ((tmp = dist(i, B)) > cur) A = i, cur = tmp;
        printf("%d ", cur);
    }
	return 0;
}

