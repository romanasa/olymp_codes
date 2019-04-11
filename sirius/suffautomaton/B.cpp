#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e6 + 1;

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

int n;

void upd(int &l1, int &r1, int l2, int r2) {
    if (l2 > r2)
        return;

    int t1 = r1 - l1 + 1 - max(l1, n - r1 - 1);
    int t2 = r2 - l2 + 1 - max(l2, n - r2 - 1);

    if (t1 < t2) 
        l1 = l2, r1 = r2;
    if (t1 == t2 && make_pair(l2, r2) < make_pair(l1, r1))
        l1 = l2, r1 = r2;
}


int main() {
	for (int i = 0; i < dd; i++) fill(go[i], go[i] + 31, -1);
	fill(suf, suf + dd, -1);

	scanf("%s", s);
	scanf("%s", t);

	n = strlen(s);
	int m = strlen(t);
	
	for (int i = 0; i < m; i++) {
		add(t[i] - 'a');
	}
	
	int cur = 0;
	int sz = 0;
	
	int L = -1, R = -1;
	for (int i = 0; i < n; i++) {
		
		while (cur && go[cur][s[i] - 'a'] == -1) {
			cur = suf[cur], sz = len[cur];
		}
		if (go[cur][s[i] - 'a'] != -1) cur = go[cur][s[i] - 'a'], sz++;
		
		upd(L, R, i - sz + 1, i);
	}
	printf("%d %d\n", L, R);
	return 0;
}