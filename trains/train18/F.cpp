#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()
//236695ZVSVG

using namespace std;

typedef long long ll;
typedef double db;


const int dd = (int)1e5 + 7;
vector<vector<int> > E;

ll sumP[dd], sumS[dd];
int p[dd];
int P[dd], S[dd];

void dfs(int v) {
    sumP[v] = P[v];
    sumS[v] = S[v];

    for (int to : E[v]) {
        dfs(to);
        sumP[v] += sumP[to];
        sumS[v] += sumS[to];
    }
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN

    int n;
    scanf("%d", &n);

    E.resize(n);

    int root = -1;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &p[i], &P[i], &S[i]);
        if (p[i] == 0) root = i;
        else E[p[i] - 1].push_back(i);
    }

    dfs(root);

    ll ans = -1e18;
    int ind = -1;
    for (int i = 0; i < n; i++) {
        if (sumS[i] - sumP[i] > ans) {
            ans = sumS[i] - sumP[i];
            ind = i;
        }
    }
    printf("%d\n", ind + 1);
    return 0;
}

