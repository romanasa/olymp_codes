#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

int n;
vector<vector<int> > E;

int findc(int v, int pr, int &center) {
    int sz = 1;
    for (int to : E[v]) if (to != pr) {
        sz += findc(to, v, center);
    }
    if (center == -1 && sz * 2 >= n) center = v;
    return sz;
}

vector<int> T;

void dfs(int v, int pr) {
    int c = 0;
    for (int to : E[v]) if (to != pr) {
        dfs(to, v), c++;
    }
    if (c == 0) T.push_back(v);
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    cin >> n;

    E.resize(n);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        cin >> a >> b;
        E[a - 1].push_back(b - 1);
        E[b - 1].push_back(a - 1);
    }

    int center = -1;
    findc(0, -1, center);
    assert(center != -1);

    for (int to : E[center]) dfs(to, center);
    if (T.size() % 2) T.push_back(T[0]);

    cout << (int)T.size() / 2 << "\n";
    for (int i = 0; i < (int)T.size() / 2; i++) cout << T[i] + 1 << " " << T[i + (int)T.size() / 2] + 1 << "\n";
    return 0;
}
