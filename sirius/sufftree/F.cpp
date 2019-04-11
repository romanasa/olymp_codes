#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)2e5 + 1;
 
char s[dd], t[dd];
 
int go[dd][31];
int suf[dd], len[dd], last;
int nv = 1;
 
int clone(int a) {
    int cur = nv++;
    copy(go[a], go[a] + 31, go[cur]);
    return cur;
}
 
void add(int c) {
    int nlast = nv++;
    len[nlast] = len[last] + 1;
     
    int p = last;
    while (p != -1 && go[p][c] == -1) go[p][c] = nlast, p = suf[p];
     
    if (p == -1) {
        suf[nlast] = 0;
    } else {
        int q = go[p][c];
        if (len[q] == len[p] + 1) {
            suf[nlast] = q;
        } else {
            int r = clone(q);
             
            suf[r] = suf[q];
            suf[q] = r;
            suf[nlast] = r;
             
            len[r] = len[p] + 1;
             
            while (p != -1 && go[p][c] == q) go[p][c] = r, p = suf[p];
        }
    }
    last = nlast;
}

#define TASK "common"

int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
    for (int i = 0; i < dd; i++) fill(go[i], go[i] + 31, -1);
    fill(suf, suf + dd, -1);
 
    scanf("%s", s);
    scanf("%s", t);

	int n = strlen(s);
	int m = strlen(t);
    
    for (int i = 0; i < n; i++) {
        add(s[i] - 'a');
    }
     
    /*for (int i = 0; i < nv; i++) {
        for (int j = 0; j < 31; j++) if (go[i][j] != -1) {
            cout << i + 1 << " " << go[i][j] + 1 << " " << (char)('a' + j) << "\n";
        }
    }*/
     
    int cur = 0;
    int ans = 0, ii = -1, jj = -1;
    int sz = 0;
     
    for (int i = 0; i < m; i++) {
         
        while (cur && go[cur][t[i] - 'a'] == -1) {
            cur = suf[cur], sz = len[cur];
        }
         
        if (go[cur][t[i] - 'a'] != -1) cur = go[cur][t[i] - 'a'], sz++;
         
        if (sz > ans) {
            ans = sz;
            jj = i;
            ii = jj - sz + 1;
        }
    }
     
    for (int i = ii; i <= jj; i++) putchar(t[i]); putchar('\n');
    return 0;
}