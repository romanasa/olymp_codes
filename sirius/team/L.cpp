#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E;

int used[12345];

void dfs(int v) {
    used[v] = 1;
    for (int to : E[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    E.resize(n);

    if (m != (n - 1)) {
        return 0 * puts("no");
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        E[a - 1].push_back(b - 1);
        E[b - 1].push_back(a - 1);
    }
    dfs(0);
    puts(accumulate(used, used + n, 0) == n ? "yes" : "no");
	return 0;
}
