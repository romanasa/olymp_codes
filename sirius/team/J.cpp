#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const ll P = (int)8e8 + 7;
const ll mod = (int)1e9 + 11;

int n, k;
int used[123];

vector<vector<int> > E;

ll calcH(vector<int> Q) {
    sort(Q.begin(), Q.end());
    ll s1 = 0, s2 = 0, h = 0;
    for (auto c : Q) {
        s1 += c * c;
        s2++;
        h = (h * P + c + 1) % mod;
    }
    return (h + s1 + s2) % mod;
}

ll dfs(int v) {
    used[v] = 1;
    vector<ll> Q;
    for (int to : E[v]) {
        if (!used[to]) {
            Q.push_back(dfs(to));
        }
    }
    return calcH(Q);
}

ll calc(vector<pair<int, int> > A) {
    E.resize(0);
    E.resize(n);

    for (auto c : A) {
        E[c.first].push_back(c.second);
        E[c.second].push_back(c.first);
    }

    fill(used, used + n, 0);

    vector<ll> Q;

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            Q.push_back(dfs(i));
        }
    }
    return calcH(Q);
}

int main() {
#ifdef WIN
    freopen("input.txt", "r", stdin);
#endif
    int z;
    scanf("%d", &z);

    while (z--) {
        scanf("%d %d", &n, &k);

        vector<vector<pair<int, int> > > Q(k);
        vector<ll> T;

        for (int i = 0; i < k; i++) {
            int x;
            scanf("%d", &x);
            Q[i].resize(x);

            for (int j = 0; j < x; j++) {
                int a, b;
                scanf("%d %d", &a, &b);
                Q[i][j] = { a - 1, b - 1 };
            }
            T.push_back(calc(Q[i]));
        }

        ll H = calcH(T);



    }

	return 0;
}

