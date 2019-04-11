#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

vector<vector<int> > E, ER;
vector<int> was, us;
int len = (int)1e9;

int minc, maxc;

void dfs(int v, int c) {
	minc = min(minc, c);
	maxc = max(maxc, c);
    was[v] = 1, us[v] = c;
    for (int to : E[v])  {
        int nxt = c + 1;
        if (!was[to]) dfs(to, nxt);
        else {
        	if (us[to] != nxt) len = min(len, abs(us[to] - nxt));
        }
    }
    for (int to : ER[v])  {
        int nxt = c - 1;
        if (!was[to]) dfs(to, nxt);
        else {
        	if (us[to] != nxt) len = min(len, abs(us[to] - nxt));
        }
    }
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;

    E.resize(n);
    ER.resize(n);
    was.resize(n), us.resize(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        E[a - 1].push_back(b - 1);
        ER[b - 1].push_back(a - 1);
    }

    int s = 0;
    
    for (int i = 0; i < n; i++) if (!was[i]) {
    	minc = (int)1e9;
    	maxc = -(int)1e9;
    	dfs(i, 0);
    	s += (maxc - minc + 1);
    }

    
    int ok = 1;
    for (int v = 0; v < n; v++) {
  		for (int to : E[v]) {
  			if ((us[v] + 1 - us[to]) % len != 0) ok = 0;
  		}
    }
    
    if (!ok || len < 3) {
    	return 0 * puts("-1 -1");
   	} 
    if (len == (int)1e9) {
    	//cout << n << " "<< m << "\n";
        if (s < 3) cout << "-1 -1\n";
        else cout << s << " " << 3 << "\n";
    } else {
        cout << len << " ";
        for (int x = 3; x <= len; x++) {
            if (len % x == 0) {
                cout << x << "\n";
                break;
            }
        }
    }

    return 0;
}
