#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int get(char c) {
	if ('0' <= c && c <= '9') return c - '0';
	return 10 + c - 'a';
}

int geth(string s) {
	int h = 0;
	for (char c : s) h = h * 36 + get(c);
	return h;
}

const int maxC = (int)1.7e6 + 7;
ll cnt[16][maxC];
ll C[16];
ll G[5];

int main() {
	int n, d;
	cin >> n >> d;
	
	ll ans = 0;
	
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		
		for (int msk = 1; msk < 16; msk++) {
			string cur;
			for (int pos = 0; pos < 4; pos++) if ((msk >> pos) & 1)
				cur += s[pos];
			cnt[msk][geth(cur)]++;
		}		
	}
	
	C[0] = 1ll * n * (n - 1) / 2;
	for (int i = 1; i < 16; i++) {
		for (int j = 0; j < maxC; j++) if (cnt[i][j]) {
			C[i] += 1ll * (cnt[i][j] - 1) * cnt[i][j] / 2;
		}
	}
	
	//for (int i = 0; i < 16; i++) err("C[%d] = %d\n", i, C[i]);
	
	for (int msk = 0; msk < 16; msk++) {
		int cnt = 0;
		for (int i = 0; i < 4; i++) if ((msk >> i) & 1)
			cnt++;
		G[cnt] += C[msk];
	}
	
	if (d == 4) {
		cout << G[0] - G[1] + G[2] - G[3] << "\n";
		return 0;
	}
	if (d == 3) {
		cout << G[1] - 2 * G[2] + 3 * G[3] << "\n";
		return 0;
	}
	if (d == 2) {
		cout << G[2] - 3 * G[3] << "\n";
		return 0;
	}
	
	if (d == 1) {
		cout << G[3] << "\n";		
		return 0;
	}
	return 0;
}