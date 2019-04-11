#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)4007;

int ans;
string A[dd];
short R[dd][dd];
int sz[dd], st[dd], ind[dd];

int len;
int pos;

void add(int val, int pos) {
	while (len && st[len - 1] >= val) len--;			
	st[len] = val;
	ind[len] = pos;
	len++;
}

void upd(int i) {
	int pos = lower_bound(st, st + len, 1 + 2 * i) - st;
	//pos = min(pos, len - 1);
	//while (pos < len && st[pos] < 1 + 2 * i) pos++;
	int cur = (pos ? ind[pos - 1] : -1);
	ans = max(ans, i - cur);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	getline(cin, A[0]);
	
	for (int i = 0; i < n; i++) {
		getline(cin, A[i]);
		sz[i] = (int)A[i].size();
	}
	
	
	for (int j = 2 * n - 2; j >= 0; j--) {
		for (int i = n - 1; i >= 0; i--) {
			if (j >= sz[i] || A[i][j] == ' ') continue;
			R[i][j] = (A[i][j] == '-' ? 1 + R[i][j + 1] : 0);
		}
	}
	
	for (int t = 0; t < 2 * n; t++) {
		len = 0, pos = 0;
		for (int i = 0, j = t, cnt = 0; i < n; i++, j++, cnt++) {
			if (j >= sz[i] || A[i][j] == ' ') { cnt = -1; continue; }
			add(R[i][j] + 2 * cnt, cnt);
			if (A[i][j] == '-' && ((i + j) & 1) == 0) upd(cnt);
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2 * n - 1; j++) {
			if (j >= sz[i] || A[i][j] == ' ') continue;
			R[i][j] = (A[i][j] == '-' ? 1 + (j ? R[i][j - 1] : 0) : 0);
		}
	}
	for (int t = 0; t < 2 * n; t++) {
		len = 0, pos = 0;
		for (int i = n - 1, j = i + t, cnt = 0; i >= 0; i--, j--, cnt++) {
			if (j >= sz[i] || A[i][j] == ' ') { cnt = -1; continue; }
			add(R[i][j] + 2 * cnt, cnt);
			if (A[i][j] == '-' && ((i + j) & 1)) upd(cnt);
		}
	}
	
	printf("%d\n", ans * ans);
	return 0;
}