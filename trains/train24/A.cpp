#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define TASK "color"

vector<vector<int> > E, ER;

void add(int a, int b) {

    //cerr << a << " | " << b << endl;

    E[a ^ 1].push_back(b);
    E[b ^ 1].push_back(a);

    ER[b].push_back(a ^ 1);
    ER[a].push_back(b ^ 1);
}

const int dd = (int)1e5 + 7;
int used[dd];
int comp[dd];


vector<int> cur;

void dfs(int v) {
    used[v] = 1;
    for (int to : E[v]) {
        if (!used[to]) dfs(to);
    }
    cur.push_back(v);
}

void mark(int v, int c) {
    comp[v] = c;
    for (int to : ER[v]) {
        if (comp[to] == -1) mark(to, c);
    }
}

char CC[] = { 'R', 'G', 'B' };

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN
    int n, m;
    cin >> n >> m;

    E.resize(6 * n);
    ER.resize(6 * n);

    string col;
    cin >> col;

    for (int i = 0; i < n; i++) {
        int a = -1, b = -1;
        int v = i;

        if (col[i] == 'R') a = 3 * v + 1, b = 3 * v + 2;
        if (col[i] == 'G') a = 3 * v, b = 3 * v + 2;
        if (col[i] == 'B') a = 3 * v, b = 3 * v + 1;

        add(2 * a, 2 * b);
    }

    for (int v = 0; v < n; v++) {

        {
            int a = 3 * v, b = 3 * v + 1;
            add(2 * a + 1, 2 * b + 1);
        }
        {
            int a = 3 * v, b = 3 * v + 2;
            add(2 * a + 1, 2 * b + 1);
        }
        {
            int a = 3 * v + 1, b = 3 * v + 2;
            add(2 * a + 1, 2 * b + 1);
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        for (int d = 0; d < 3; d++) {
            int ca = 3 * a + d, cb = 3 * b + d;
            add(2 * ca + 1, 2 * cb + 1);
        }
    }


    for (int i = 0; i < 6 * n; i++)if (!used[i]) dfs(i);

    reverse(cur.begin(), cur.end());


    int cc = 0;

    fill(comp, comp + 6 * n, -1);
    for (int v : cur) {
        if (comp[v] == -1) {
            mark(v, cc++);
        }
    }

    for (int v = 0; v < 3 * n; v++) {
        if (comp[2 * v] == comp[2 * v + 1]) return 0 * puts("Impossible");
    }

    for (int v = 0; v < n; v++) {
        for (int d = 0; d < 3; d++) {
            int a = 3 * v + d;
            if (comp[2 * a] > comp[2 * a + 1]) cout << CC[d];
        }
    }
    cout << "\n";

    return 0;
}

