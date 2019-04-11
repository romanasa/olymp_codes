#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
string s, ans;
int n;
 
const int dd = (int)3e6 + 7;
int P[dd], S[dd];
 
int get(int c) {
    assert((c&-c) == c);
    for (int i = 0; ; i++) {
        if ((1ll << i) == c) return i;
    }
}
 
int check(int x) { return x == (x&-x); }

char need;
 
void go(int l, int r) {
 
	int c1 = 0, c2 = 0;
	for (int i = l; i <= r; i++) {
		if (s[i] == '{') c1++;
		if (s[i] == '}') c2++;
	}
	int x = get(max(c1, c2));

    if (s[r] != '}') {
        assert(l == r);
        for (int i = 0; i <= l; i++) ans[i] = s[i];
        ans[l + 1] = '}';
        for (int i = l + 1; i < n; i++) ans[i + 1] = s[i];
        return;
    }
     
    if (s[l] != '{') {
        assert(l == r);
        for (int i = 0; i < l; i++) ans[i] = s[i];
        ans[l] = '{';
        for (int i = l; i < n; i++) ans[i + 1] = s[i];
        return;
    }
    
    if (need == '}') {
    
		int lastL = l + 1;
		int bal = 0;
		int cnt = 0;
		
		for (int i = l + 1; i < r; i++) {
			if (s[i] == '{') bal++;
			if (s[i] == '}') bal--;
			if (s[i] == ',' && bal == 0) lastL = i + 1, cnt++;
		}
		
		bal = 0;
		int lastR = r - 1;
		for (int i = r - 1; i > l; i--) {
			if (s[i] == '}') bal++;
			if (s[i] == '{') bal--;
			if (s[i] == ',' && bal == 0) lastR = i - 1, cnt++;
			if (cnt == x - 1) break;
		}
		go(lastL, lastR);
		return;
	} else {
		int lastR = r - 1;
		int bal = 0, cnt = 0;
		
		for (int i = r - 1; i > l; i--) {
			if (s[i] == '}') bal++;
			if (s[i] == '{') bal--;
			if (s[i] == ',' && bal == 0) lastR = i - 1, cnt++;
		}
		
		bal = 0;
		int lastL = l + 1;
		for (int i = l + 1; i < r; i++) {
			if (s[i] == '{') bal++;
			if (s[i] == '}') bal--;
			if (s[i] == ',' && bal == 0) lastL = i + 1, cnt++;
			if (cnt == x - 1) break;
		}
		go(lastL, lastR);
		return;
	}
}
 
void fix(const char* s, char* q) {
    n = strlen(s);
    for (int i = 0; i < n; i++) ::s += s[i], ans += '.';
 
     
    int c1 = 0, c2 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '{') c1++;
        if (s[i] == '}') c2++;
    }
     
    if (c1 == c2) {
        for (int i = 0; i + 1 < n; i++) {
            if (s[i] == '}' && s[i + 1] == '{') {
                for (int j = 0; j <= i; j++) q[j] = s[j];
                q[i + 1] = ',';
                for (int j = i + 1; j < n; j++) q[j + 1] = s[j];
                return;
            }
        }
        assert(0);
    }
    need = (c1 < c2 ? '{' : '}');
    go(0, n - 1);
    for (int i = 0; i <= n; i++) q[i] = ans[i];
}