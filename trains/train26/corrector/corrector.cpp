#include "grader.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int p = 31;
//const int mod = (int)1e9 + 7;

const int dd = (int)1e5 + 7;

unordered_map<ull, int> M[dd];
ll P[dd];

void solve (char* text, int wn, char** words, int qn, query_t* q, long long* ans) {
	int n = strlen(text);	
	
	for (int i = 0; i < wn; i++) {
		int len = strlen(words[i]);
		ull h = 0;
		for (int j = 0; j < len; j++) h = (h * p + words[i][j] - 'a' + 1);// % mod;
		M[len][h]++;
	}
	
	int cnt = 0;
	
	for (int len = 1; len <= n; len++) if (M[len].size()) {
	
		ull curP = 1;
		for (int it = 0; it < len - 1; it++) curP = curP * p;// % mod;
	
		ull h = 0;
		for (int i = 0; i < len; i++) h = (h * p + text[i] - 'a' + 1);// % mod;	
		
		for (int i = 0; i + len <= n; i++) {
			auto it = M[len].find(h);
		
			ll t = (i ? P[i - 1] : 0);
			if (it != M[len].end()) t += it->second;
			
			P[i] = t;
			
			if (i + len == n) continue;
			
			h -= 1ll * (text[i] - 'a' + 1) * curP;// % mod;
			//if (h < 0) h += mod;
			h = (h * p + text[i + len] - 'a' + 1);// % mod;
		}
		
		for (int i = 0; i < qn; i++) {
			int l = q[i].l - 1;
			int r = q[i].r - len;
			if (l <= r) ans[i] += P[r] - (l ? P[l - 1] : 0);
		}		
	}
}
