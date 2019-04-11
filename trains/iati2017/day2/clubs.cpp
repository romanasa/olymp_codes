#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int n, m;
int C[31][31];
int pos, cur;
int p[31], cnt[31];

const int dd = (int)4e5 + 7;
bool A[dd][31];

int val[dd];
int ind[dd];

void gen(int i, int st) {
	if (i == cur) {
		
		int msk = 0;
		for (int c = 0; c < cur; c++) {
			A[pos][p[c]] = 1;
			msk |= (1 << p[c]);
			cnt[p[c]]++;
		}
		ind[msk] = pos;
		val[pos] = msk;
		pos++;
	} else {
		for (int c = st; c < m; c++) {
			p[i] = c;
			gen(i + 1, c + 1);
			if (pos > n) return;
		}
	}
}

int main() {
	cin >> n;
	
	m = ceil(log2(n));
	
	for (int i = 0; i < 31; i++) C[0][i] = 0;
	for (int i = 0; i < 31; i++) C[i][0] = 1;
	
	for (int i = 1; i < 31; i++) {
		for (int j = 1; j < 31; j++) {
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	}
	
	pos = 2;
	cur = 1;
	
	while (pos + C[m][cur] <= n) {
		gen(0, 0);
		cur++;
	}
	int st = pos;
	gen(0, 0);
	
	
	while (1) {
		int i1 = min_element(cnt, cnt + m) - cnt;
		int i2 = max_element(cnt, cnt + m) - cnt;
		
		if (cnt[i2] - cnt[i1] <= 1) break;
		
		for (int i = st; i <= n; i++) if (A[i][i2] && !A[i][i1]) {
			int a = val[i], b = val[i];
			
			a ^= (1 << i1);
			a ^= (1 << i2);
			
			if (ind[a] == 0) {
				A[i][i2] = 0, A[i][i1] = 1;
				val[i] = a;	
				ind[b] = 0, ind[a] = i;
				cnt[i1]++, cnt[i2]--;
				if (cnt[i2] - cnt[i1] <= 1) break;
			}
		}
	}
	
	cout << m << " " << *max_element(cnt, cnt + m) << "\n";
	for (int i = 0; i < m; i++) {
		cout << cnt[i] << " ";
		for (int j = 1; j <= n; j++) if (A[j][i]) cout << j << " ";
		cout << "\n";
	}
	
	return 0;
}