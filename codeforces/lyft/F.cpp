#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int maxC = (int)2e6 + 7;
ll cnt[maxC];

const int dd = (int)1e5 + 7;
ll ans[dd];

int G[13][3];
int w, n, m;

void go(int i, int cur, int ind) {
	if (i == w) {
		ans[ind] += cnt[cur];
	} else {
		for (int j = 0; j < 2; j++) if (G[i][j] != -1) {
			go(i + 1, cur * 3 + G[i][j], ind);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
		
	cin >> w >> n >> m;
	
	map<int, int> M;
	
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		M[x]++;
	}
	
	vector<string> T(m);
	for (int i = 0; i < m; i++) cin >> T[i];
	
	for (auto cc : M) {
		for (auto dd : M) {
			int cur = 0;
			int c = cc.first, d = dd.first;
			for (int i = 0; i < w; i++) {
				int a = (c >> (w - i - 1)) & 1;
				int b = (d >> (w - i - 1)) & 1;
				
				if (a > b) swap(a, b);
				
				if (a == 0 && b == 0) cur = cur * 3 + 0;
				if (a == 0 && b == 1) cur = cur * 3 + 1;
				if (a == 1 && b == 1) cur = cur * 3 + 2;
				
			}
			cnt[cur] += 1ll * cc.second * dd.second;
		}
	}
	
	for (int i = 0; i < m; i++) {
		string s = T[i];
		for (int j = 0; j < w; j++) {
			if (s[j] == 'A') {
    			G[j][0] = 0; 
    			G[j][1] = 1;
    		} else if (s[j] == 'O') {
    			G[j][0] = 0;
    			G[j][1] = -1;
    		} else if (s[j] == 'X') {
    			G[j][0] = 0; 
    			G[j][1] = 2;
    		} else if (s[j] == 'a') {
    			G[j][0] = 2;
    			G[j][1] = -1;
    		} else if (s[j] == 'o') {
    			G[j][0] = 1;
    			G[j][1] = 2;
    		} else if (s[j] == 'x') {
    			G[j][0] = 1;
    			G[j][1] = -1;
    		}
		}
		go(0, 0, i);
		cout << ans[i] << "\n";
	}
	
	return 0;
}