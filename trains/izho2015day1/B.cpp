#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)4007;
const int mod = (int)1e9 + 7;

char a[dd][dd], b[dd][dd];
int up[dd], st[dd], val[dd];
int n;

void add(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

void sub(int &a, int b) {
	a -= b;
	if (a < 0) a += mod;
}

void calc(int T[][dd]) {
	fill(up, up + n, 0);
	for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		if (!a[i][j]) up[j] = 0;
    		else up[j]++;
    	}
    	
    	int sz = 0;
    	int cur = 0;
    	
    	for (int j = 0; j < n; j++) {
    		if (sz && val[sz - 1] == up[j]) {
    			add(cur, up[j]);
    			T[i][j] = cur;
    			continue;
    		}
    		
    		int ind = j;
    		while (up[j] < val[sz - 1]) {
    			cur -= abs(ind - st[sz - 1]) * val[sz - 1];
    			if (cur < 0) cur += mod;
    			
    			ind = st[sz - 1];
    			sz--;
    		}
    		st[sz] = ind;
    		val[sz] = up[j];
    		sz++;
    		
    		add(cur, up[j] * (abs(j - ind) + 1));
    		T[i][j] = cur;
    	}
    }
}

void calc2(int T[][dd]) {
	fill(up, up + n, 0);
	for (int i = n - 1; i >= 0; i--) {
    	for (int j = 0; j < n; j++) {
    		if (!a[i][j]) up[j] = 0;
    		else up[j]++;
    	}
    	
    	int sz = 0;
    	int cur = 0;
    	
    	for (int j = n - 1; j >= 0; j--) {
    		if (sz && val[sz - 1] == up[j]) {
    			add(cur, up[j]);
    			T[i][j] = cur;
    			continue;
    		}
    		
    		int ind = j;
    		while (up[j] < val[sz - 1]) {
    			cur -= abs(ind - st[sz - 1]) * val[sz - 1];
    			if (cur < 0) cur += mod;
    			
    			ind = st[sz - 1];
    			sz--;
    		}
    		st[sz] = ind;
    		val[sz] = up[j];
    		sz++;
    		
    		add(cur, up[j] * (abs(j - ind) + 1));
    		T[i][j] = cur;
    	}
    }
}

int T[dd][dd];
int Q[dd][dd];

int get(int i1, int j1, int i2, int j2, int S[][dd]) {
	int t = 0;

	add(t, S[i2][j2]);
	if (i1) sub(t, S[i1 - 1][j2]);
	if (j1) sub(t, S[i2][j1 - 1]);
	if (i1 && j1) add(t, S[i1 - 1][j1 - 1]);
	
	return t;
}

#define TASK "matrix"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	scanf("%d\n", &n);
	
	for (int i = 0; i < n; i++) {
		gets(a[i]);
		for (int j = 0; j < n; j++) a[i][j] -= '0';
	}

	
    int ans = 0;
	
	for (int it = 0; it < 2; it++) {
	
    	calc(T);
    	calc2(Q);
        
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < n; j++) {
    			add(T[i][j], (i ? T[i - 1][j] : 0));
    			add(T[i][j], (j ? T[i][j - 1] : 0));
    			sub(T[i][j], (i && j ? T[i - 1][j - 1] : 0));
    			
    			
    			add(Q[i][j], (i ? Q[i - 1][j] : 0));
    			add(Q[i][j], (j ? Q[i][j - 1] : 0));
    			sub(Q[i][j], (i && j ? Q[i - 1][j - 1] : 0));
    		}
    	}
    	
    	if (it == 0) for (int i = 0; i + 1 < n; i++) {
    		int t1 = get(0, i, n - 1, i, T);
    		int t2 = get(0, i + 1, n - 1, n - 1, Q);
    		add(ans, 1ll * t1 * t2 % mod);	
    	}
    	
    	if (it == 0) for (int i = 0; i + 1 < n; i++) {
    		int t1 = get(i, 0, i, n - 1, T);
    		int t2 = get(i + 1, 0, n - 1, n - 1, Q);
    		add(ans, 1ll * t1 * t2 % mod);
    	}
    	
    	for (int i = 0; i + 1 < n; i++) {
    		for (int j = 0; j + 1 < n; j++) {
    			int t1 = get(i, j, i, j, T);
    			int t2 = get(i + 1, j + 1, n - 1, n - 1, Q);
    			sub(ans, 1ll * t1 * t2 % mod);
    		}
    	}
    	
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < n; j++) {
    			b[j][n - 1 - i] = a[i][j];
    		}
    	}
    	for (int i = 0; i < n; i++)
    		for (int j = 0; j < n; j++)
    			a[i][j] = b[i][j];
	}
			
	printf("%d\n", ans * 2 % mod);
	
    //for (int i = 0; i < n; i++)
    //	for (int j = 0; j < n; j++) err("%d%c", Q[i][j], " \n"[j == n - 1]);
    
	return 0;
}