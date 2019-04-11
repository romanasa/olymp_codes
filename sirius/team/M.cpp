#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<int> > E;
int n, m;

pair<int, int> bfs(int v) {
    vector<int> d(n, (int)1e9);
    d[v] = 0;
    queue<int> q;
    q.push(v);

    while (q.size()) {
        int v = q.front();
        q.pop();

        for (int to : E[v]) {
            if (d[to] > d[v] + 1) {
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
    }
    int ind = max_element(d.begin(), d.end()) - d.begin();
    return { d[ind], ind };
}

int main() {
    cin >> n >> m;

    E.resize(n);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        cin >> a >> b;
        E[a - 1].push_back(b - 1);
        E[b - 1].push_back(a - 1);
    }
    auto c = bfs(0);
    cout << bfs(c.second).first << "\n";
	return 0;
}

