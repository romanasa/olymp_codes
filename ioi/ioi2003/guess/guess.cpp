#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

char A[51][11];
int used[51];

int main() {
	int n, p;
	cin >> n >> p;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			cin >> A[i][j];
		}
	}
	
	
	for (int i = 0; i < n; i++) {
		
		int cur = (int)1e9;
		int aski = -1, askm = -1;
		
		for (int j = 0; j < p; j++) {
			for (int msk = 1; msk < 8; msk++) {
				int cnt1 = 0, cnt2 = 0;
				for (int k = 0; k < n; k++) if (!used[k]) {
					int ok = 0;
					for (int c = 0; c < 3; c++) if ((msk >> c) & 1) {
						ok |= (A[k][j] == (char)('X' + c));
					}
					(ok ? cnt1 : cnt2)++;
				}	
				if (max(cnt1, cnt2) < cur) {
					cur = max(cnt1, cnt2);
					aski = j, askm = msk;
				}
			}
		}
		
		cout << "Q " << aski + 1 << " ";
		for (int c = 0; c < 3; c++) if ((askm >> c) & 1) cout << (char)('X' + c) << " ";
		cout << endl;
	
		int ans;
		cin >> ans;
		
		for (int k = 0; k < n; k++) if (!used[k]) {
			int ok = 0;
			for (int c = 0; c < 3; c++) if ((askm >> c) & 1) {
				ok |= (A[k][aski] == (char)('X' + c));
			}
			if (ans ^ ok) used[k] = 1;
		}
		
		int cnt = 0, pos =-1;
		for (int k = 0; k < n; k++) if (!used[k]) {
			cnt++, pos = k;
		}
		
		if (cnt == 1) {
			cout << "C " << pos + 1 << endl;
			break;
		}
	}
	
	return 0;
}