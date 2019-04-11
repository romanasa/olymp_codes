#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<vector<pair<int, char> > > E, ER, G, GR;

const int dd = (int)1e5 + 7;
int used[dd], comp[dd];

vector<int> J;

void dfs(int v) {
	used[v] = 1;
	for (auto c : E[v]) if (!used[c.first]) 
		dfs(c.first);
	J.push_back(v);
}

void mark(int v, int cc) {
	comp[v] = cc;
	for (auto c : ER[v]) if (comp[c.first] == -1)
		mark(c.first, cc);
}

vector<int> D;

void topsort(int v) {
	used[v] = 1;
	for (auto c : G[v]) if (!used[c.first])
		topsort(c.first);
	D.push_back(v);
}

#define TASK "magican"

const int LOG = 17;
int dp[dd][LOG];
int up[dd][LOG];

int dp2[dd][LOG];
int up2[dd][LOG];

const int p = 31;
int P[dd];
int H[dd];

const int mod = (int)8e8 + 7;

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	P[0] = 1;
	for (int i = 1; i < dd; i++) P[i] = 1ll * P[i - 1] * p % mod;
	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	int n, m;
	cin >> n >> m;
	
	E.resize(n);
	ER.resize(n);
	
	for (int i = 0; i < m; i++) {
		int a, b;
		char c;
		cin >> a >> b >> c;
		E[a - 1].push_back({ b - 1, c });
		ER[b - 1].push_back({ a - 1, c });
	}
	
	for (int i = 0; i < n; i++) if (!used[i])
		dfs(i);
		
	reverse(J.begin(), J.end());
	
	int cc = 0;
	fill(comp, comp + n, -1);
	for (int v : J) if (comp[v] == -1)
		mark(v, cc++);
		
	G.resize(cc);
	GR.resize(cc);
		
	vector<int> in(cc);
	
	for (int v = 0; v < n; v++) {
		for (auto c : E[v]) if (comp[v] != comp[c.first]) {
			G[comp[v]].push_back({ comp[c.first], c.second });
			GR[comp[c.first]].push_back({ comp[v], c.second });
			
			//err("%d--%c-->%d\n", comp[v], c.second, comp[c.first]);
			
			in[comp[c.first]]++;
		}
	}
	
	for (int v = 0; v < cc; v++) {
		sort(G[v].begin(), G[v].end());
		G[v].resize(unique(G[v].begin(), G[v].end()) - G[v].begin());
		sort(GR[v].begin(), GR[v].end());
		GR[v].resize(unique(GR[v].begin(), GR[v].end()) - GR[v].begin());
	}
	
	fill(used, used + cc, 0);
	//for (int i = 0; i < cc; i++) if (in[i] == 0)
	//	topsort(i);

	topsort(comp[0]);
	
	reverse(D.begin(), D.end());
	
	vector<int> len(cc), lenR(cc);

	for (int v : D) 
		for (auto c : G[v]) 
			len[c.first] = max(len[c.first], len[v] + 1);
			
	for (int i = (int)D.size() - 1; i >= 0; i--) {
		int v = D[i];
		for (auto c : GR[v]) 
			lenR[c.first] = max(lenR[c.first], lenR[v] + 1);
	}
	
	int maxlen = *max_element(len.begin(), len.end());
	
	
	for (int i = (int)D.size() - 1; i >= 0; i--) {
		int v = D[i];
		
		if (len[v] == maxlen) {
			for (int j = 0; j < LOG; j++) dp[v][j] = 0, up[v][j] = v;
		} else {
			int was = 0;
			for (auto c : G[v]) if (len[v] + 1 + lenR[c.first] == maxlen) {
				if (!was) {
					dp[v][0] = c.second - 'a' + 1;
					up[v][0] = c.first;
					
					for (int j = 1; j < LOG; j++) {
						up[v][j] = up[up[v][j - 1]][j - 1];
						int cur = (1ll * dp[v][j - 1] * P[(1 << (j - 1))] + dp[up[v][j - 1]][j - 1]) % mod;
						dp[v][j] = cur;
					}
					was = 1;
				} else {
				
					int a = up[v][0];
					int b = c.first;
					
					for (int j = LOG - 1; j >= 0; j--) {
						if (dp[a][j] == dp[b][j]) {
							a = up[a][j];
							b = up[b][j];
						}
					}
					
					if (up[b][0] != b && dp[b][0] < dp[a][0]) {
						dp[v][0] = c.second - 'a' + 1;
    					up[v][0] = c.first;
    					
    					for (int j = 1; j < LOG; j++) {
    						up[v][j] = up[up[v][j - 1]][j - 1];
    						int cur = (1ll * dp[v][j - 1] * P[(1 << (j - 1))] + dp[up[v][j - 1]][j - 1]) % mod;
    						dp[v][j] = cur;
    					}
					}
				}
			}
		}
	}
	
	
	for (int v : D) {
		if (v == 0) {
			for (int j = 0; j < LOG; j++) dp2[v][j] = 0, up2[v][j] = v;
		} else {
			int was = 0;
			for (auto c : GR[v]) if (lenR[v] + 1 + len[c.first] == maxlen) {
				if (!was) {
					dp2[v][0] = c.second - 'a' + 1;
					up2[v][0] = c.first;
					
					for (int j = 1; j < LOG; j++) {
						up2[v][j] = up2[up2[v][j - 1]][j - 1];
						int cur = (1ll * dp2[up2[v][j - 1]][j - 1] * P[(1 << (j - 1))] + dp2[v][j - 1]) % mod;
						dp2[v][j] = cur;
					}
					was = 1;
				} else {
				
					int a = up2[v][0];
					int b = c.first;
					
					for (int j = LOG - 1; j >= 0; j--) {
						if (dp2[a][j] == dp2[b][j]) {
							a = up2[a][j];
							b = up2[b][j];
						}
					}
					
					if (up2[b][0] != b && dp2[b][0] < dp2[a][0]) {
						dp2[v][0] = c.second - 'a' + 1;
    					up2[v][0] = c.first;
    					
    					for (int j = 1; j < LOG; j++) {
    						up2[v][j] = up2[up2[v][j - 1]][j - 1];
    						int cur = (1ll * dp2[up2[v][j - 1]][j - 1] * P[(1 << (j - 1))] + dp2[v][j - 1]) % mod;
    						dp2[v][j] = cur;
    					}
					}
				}
			}
		}
	}
	
	int anslen = maxlen;
	int ansv = 0;
	
	
	for (int v = 0; v < cc; v++) if (v && used[v]) {
		
		int clen = maxlen - len[v];
		
		if (clen > 0 && anslen > 0 && dp[ansv][0] > dp[v][0]) {
			ansv = v;
			anslen = clen;
			continue;
		} 
		
		int l = 0, r = maxlen;
		
		while (r - l > 1) {
			int m = (l + r) / 2;
			
			int h1 = 0;
			int h2 = 0;
			
			int a = v;
			int b = ansv;
			
			if (m <= clen) {
				int c1 = 0;
				for (int j = LOG - 1; j >= 0; j--) {
					if (c1 + (1 << j) <= m) {
						h1 = (1ll * P[(1 << j)] * h1 + dp[a][j]) % mod;
						a = up[a][j];
						c1 += (1 << j);
					}
				}
			} else {
				h1 = dp[a][LOG - 1];
				
				int ch1 = 0;
				int c1 = 0;
				for (int j = LOG - 1; j >= 0; j--) {
					if (c1 + (1 << j) <= m - clen) {
						ch1 = (1ll * P[(1 << j)] * dp2[a][j] + ch1) % mod;
						a = up2[a][j];
						c1 += (1 << j);
					}
				}
				h1 = (1ll * h1 * P[m - clen] + ch1) % mod;
			}
			
			if (m <= anslen) {
				int c2 = 0;
				for (int j = LOG - 1; j >= 0; j--) {
					if (c2 + (1 << j) <= m) {
						h2 = (1ll * P[(1 << j)] * h2 + dp[b][j]) % mod;
						b = up[b][j];
						c2 += (1 << j);
					}
				}
			} else {
				h2 = dp[b][LOG - 1];
				
				
				int ch2 = 0;
				int c2 = 0;
				for (int j = LOG - 1; j >= 0; j--) {
					if (c2 + (1 << j) <= m - anslen) {
						ch2 = (1ll * P[(1 << j)] * dp2[b][j] + ch2) % mod;
						b = up2[b][j];
						c2 += (1 << j);
					}
				}
				h2 = (1ll * h2 * P[m - anslen] + ch2) % mod;
			}
			
			if (h1 == h2) l = m;
			else r = m;
		}
		
		
		int a = v, b = ansv;
		int m = l;
		
		int ca, cb;
		
		if (m < clen) {
			int c1 = 0;
			for (int j = LOG - 1; j >= 0; j--) {
				if (c1 + (1 << j) <= m) {
					a = up[a][j];
					c1 += (1 << j);
				}
			}
			ca = dp[a][0];
		} else {
			int QQ = m - clen;
		
			int c1 = 0;
			for (int j = LOG - 1; j >= 0; j--) {
				if (c1 + (1 << j) <= QQ) {
					a = up2[a][j];
					c1 += (1 << j);
				}
			}
			ca = dp2[a][0];
		}
		
		if (m < anslen) {
			int c2 = 0;
			for (int j = LOG - 1; j >= 0; j--) {
				if (c2 + (1 << j) <= m) {
					b = up[b][j];
					c2 += (1 << j);
				}
			}
			cb = dp[b][0];
		} else {
			int c2 = 0;
			for (int j = LOG - 1; j >= 0; j--) {
				if (c2 + (1 << j) <= m - anslen) {
					b = up2[b][j];
					c2 += (1 << j);
				}
			}
			cb = dp2[b][0];
		}
		
		err("ansv = %d, v = %d, m = %d\n", ansv, v, m);
		err("ca = %d, cb = %d\n", (int)ca, (int)cb);
		
		if (ca < cb) {
			ansv = v;
			anslen = clen;
		}
	}
	//cerr << "In = " << In << endl;
	//err("calc ans\n");
	//err("ansv = %d\n", ansv);
	
	//return 0;
	
	string ans;
	int st = ansv;
	int it = 0;
	while (len[st] < maxlen) {
		ans += (char)(dp[st][0] + 'a' - 1);
		st = up[st][0];
		
		assert(++it < 1005);
	}
	
	string ans2;
	st = ansv;
	it = 0;
	while (lenR[st] < maxlen) {
		ans2 += (char)(dp2[st][0] + 'a' - 1);
		st = up2[st][0];
		assert(++it < 1005);
	}
	
	reverse(ans2.begin(), ans2.end());
	cout << ans + ans2 << "\n";
	
	/*
	int i = 0;
	while (ans.size() < maxlen) ans += In[i++];
	cout << ans << "\n";
	*/
	
	/*for (int i = 0; i < cc; i++) {
		cout << i << ": ";
		cout << In[i] << ", " << Out[i] << "\n";
	}*/
	
	return 0;
}