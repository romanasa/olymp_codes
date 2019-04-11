#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <bitset>
#include <cassert>


using namespace std;


int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    vector<bitset<3>> colors(n, 7);

    char c;
    for (int i = 0; i < n; ++i) {
        cin >> c;

        if (c == 'R') {
            colors[i][0] = 0;
        } else if (c == 'G') {
            colors[i][1] = 0;
        } else {
            colors[i][2] = 0;
        }
    }

    int from, to;
    for (int i = 0; i < m; ++i) {
        cin >> from >> to;
        --from;
        --to;

        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    vector<int> used(n), cused;

    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            continue;
        }

        int gcan = false;
        for (int j = 0; j < 3; ++j) {
            if (!colors[i][j]) {
                continue;
            }

            vector<bitset<3>> curcolor = colors;
            curcolor[i][j] = 0;

            cused = used;

            queue<int> bfs({i});
            cused[i] = true;

            bool can = true;
            while (!bfs.empty()) {
                int cur = bfs.front();
                bfs.pop();

                for (int v : graph[cur]) {
                    curcolor[v] &= curcolor[cur].flip();
                    curcolor[cur].flip();

                    if (curcolor[v].none()) {
                        can = false;

                        break;
                    }

                    if (!cused[v] && curcolor[v].count() == 1) {
                        bfs.push(v);
                        cused[v] = true;
                    }
                }

                if (!can) {
                    break;
                }
            }

            if (can) {
                gcan = true;
                colors = curcolor;
                used = cused;

                break;
            }
        }

        if (!gcan) {
            cout << "Impossible";

            return 0;
        }
    }
	
    string ans;
    for (bitset<3> b : colors) {
        if (b[0]) {
            ans += 'R';
        } else if (b[1]) {
            ans += 'G';
        } else {
            ans += 'B';
        }
    }
    
    for (int i = 0; i < n; i++) {
  		for (int to : graph[i]) {
  			assert(ans[i] != ans[to]);
  		}
    }
    
    cout << "Possible"; return 0;
    for (bitset<3> b : colors) {
        if (b[0]) {
            cout << 'R';
        } else if (b[1]) {
            cout << 'G';
        } else {
            cout << 'B';
        }
    }

    return 0;
}