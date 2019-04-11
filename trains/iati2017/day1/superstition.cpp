#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = (int)1e9 + 7;
const int maxN = 81;
const int T = (int)1e4 + 1;

int dp[maxN][T];

void add(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

int G[301][301];
int res[301][301];

int tmp[301][301];
int tmp2[301][301];

int nv;

void mul(int A[][301], int B[][301]) {
    for (int i = 0; i < nv; i++) {
        copy(A[i], A[i] + nv, tmp[i]);
        copy(B[i], B[i] + nv, tmp2[i]);
    }

    for (int i = 0; i < nv; i++) {
        for (int j = 0; j < nv; j++) {
            A[i][j] = 0;
            for (int k = 0; k < nv; k++)
                add(A[i][j], 1ll * tmp[i][k] * tmp2[k][j] % mod);
        }
    }
}

void bp(int p) {
    for (int i = 0; i < nv; i++) res[i][i] = 1;

    for ( ; p; p >>= 1) {
        if (p & 1) mul(res, G);
        mul(G, G);
    }
}



int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
	int n, m, d, k;
	cin >> n >> m >> d >> k;

    vector<vector<pair<int, int> > > E(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        E[a - 1].push_back({ b - 1, c });
        E[b - 1].push_back({ a - 1, c });
    }

	if (n > 30) {
        for (int i = 0; i < n; i++) dp[i][0] = 1;
        for (int len = 0; len < k; len++)
            for (int v = 0; v < n; v++)
                for (auto &e : E[v]) if (len + e.second <= k)
                    add(dp[e.first][len + e.second], dp[v][len]);
        int ans = 0;
        for (int v = 0; v < n; v++)
            for (int i = d; i <= k; i += d)
                add(ans, dp[v][i]);
        cout << ans << "\n";
        return 0;
	}

	nv = n;

	for (int v = 0; v < n; v++) if (E[v].size()) {
        int len = 0;
        for (auto &e : E[v]) len = max(len, e.second);

        if (len > 1) {
            G[v][nv] = 1;
            for (int i = 0; i + 2 < len; i++) {
                G[nv + i][nv + i + 1] = 1;
            }
        }

        for (auto &e : E[v]) if (e.second == 1) {
            G[v][e.first] = 1;
        }


        for (auto &e : E[v]) if (e.second > 1) {
            G[nv + e.second - 2][e.first] = 1;
        }
        nv += len - 1;
	}
	bp(d);

	for (int i = 0; i < nv; i++)
        for (int j = 0; j < n; j++) add(res[nv][i], res[j][i]);
	res[nv][nv] = 1;
    nv++;

    for (int i = 0; i < nv; i++) {
        for (int j = 0; j < nv; j++) {
            G[i][j] = res[i][j];
            res[i][j] = 0;
        }
    }

    bp(k / d);

    int ans = 0;
    for (int i = 0; i < n; i++) add(ans, res[nv - 1][i]);

    cout << ans << "\n";
	return 0;
}
