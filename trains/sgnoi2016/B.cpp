#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

char s[4007];
char a[2007][2007];
int up[2007];

int st[2007];
int val[2007];

int main() {
	
	int n, m, k;
	scanf("%d %d %d\n", &n, &m, &k);
		
	for (int i = 0; i < n; i++) {
		gets(s);
		for (int j = 0; j < m; j++) a[i][j] = s[2 * j] - '0';
	}
	
	if (k == 1) {
	
		ll ans = 0;
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < m; j++) {
    			if (a[i][j]) up[j] = 0;
    			else up[j]++;
    		}
    		
    		int sz = 0;
    		ll cur = 0;
    		
    		for (int j = m - 1; j >= 0; j--) {
    			if (sz && val[sz - 1] == up[j]) {
    				cur += up[j];
    				ans += cur;
    				continue;
    			}
    			
    			int ind = j;
    			while (up[j] < val[sz - 1]) {
    				cur -= (st[sz - 1] - ind) * val[sz - 1];
    				ind = st[sz - 1];
    				sz--;
    			}
    			
    			st[sz] = ind;
    			val[sz] = up[j];
    			sz++;
    			
    			cur += up[j] * (ind - j + 1);
    			ans += cur;
    		}
    	}
    	printf("%lld\n", ans);
		return 0;
	}
	
	
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j]) up[j] = 0;
			else up[j]++;
		}
		for (int j = 0; j < m; j++) {
			int cur = up[j];
			for (int t = j; t < m; t++) {
				cur = min(cur, up[t]);
				int len = t - j + 1;
				int c = (k + len - 1) / len;
				ans += max(0, cur - c + 1);
			}
		}
	}
	
    printf("%lld\n", ans);
	return 0;
}