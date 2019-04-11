#include <bits/stdc++.h>
#ifdef SIR
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#else
#define err(...) 42
#endif

typedef long long ll;

using namespace std;

const int dd = (int)1e5 + 7;

int P[dd], R[dd], cnt[dd];
ll sum[dd];

int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }

int ans = 0;

void un(int a, int b, int e) {
    a = get(a), b = get(b);
    assert(a != b);

    if (R[b] > R[a]) swap(a, b);
    R[a] += R[b], P[b] = a;
    sum[a] += sum[b];

    if (e <= sum[a]) {
        ans += cnt[a] + 1 + cnt[b];
        cnt[a] = 0;
    } else {
        cnt[a] = cnt[a] + 1 + cnt[b];
    }
}

struct edge { int a, b, c; };

void solve() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) P[i] = i, R[i] = 1, cnt[i] = 0;
    for (int i = 0; i < n; i++) cin >> sum[i];

    vector<edge> E(m);
    for (int i = 0; i < m; i++) cin >> E[i].a >> E[i].b >> E[i].c;
    sort(E.begin(), E.end(), [](edge a, edge b) {
        return a.c < b.c;
    });

    for (int i = 0; i < m; i++) {
        int a = E[i].a - 1;
        int b = E[i].b - 1;
        int c = E[i].c;

        if (get(a) == get(b)) {
            if (c <= sum[get(a)]) ans++;
            else cnt[get(a)]++;
        } else {
            un(a, b, c);
        }
    }
    cout << m - ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef SIR
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
}