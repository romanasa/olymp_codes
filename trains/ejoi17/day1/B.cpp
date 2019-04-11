#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

//#ifdef HOME
//	const int maxC = 100;
//#else
	const int maxC = 32e6;
//#endif

const int mod = (int)1e9 + 7;

bitset<maxC> F;
int A[123], ind;
int C[(1 << 8) + 123];
vector<int> god[(1 << 8) + 123];

void add(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

int ans, len;
int G[66];

void go(int pos, int cur) {
	if (pos) add(ans, cur);
	
	for (int x = 1; x < len; x++) if (G[x] <= 1) {	
		int cnt = 0;
		for (int y : god[x]) cnt += G[y];
		
		if (cnt <= 1) {
			G[x]++;
			go(pos + 1, 1ll * cur * C[x] % mod);
			G[x]--;
		}
	}
} 

int main() {
	ll N;
	cin >> N;
	
	for (int i = 2; i < maxC; i++) F[i] = 1;
	
	for (int i = 2; i * i < maxC; i++) if (F[i]) {
		for (int j = i * i; j < maxC; j += i) F[j] = 0;
	}
	
	for (int i = 0; i < maxC; i++) if (F[i]) {
		int cnt = 0;
		while (N % i == 0) {
			cnt++;
			N /= i;
		}
		if (cnt) A[ind++] = cnt;
	}
	if (N > 1) A[ind++] = 1;
	
	//err("ind = %d\n", ind);
	len = (1 << ind);
	
	for (int i = 1; i < len; i++) {
		C[i] = 1;
		for (int j = 0; j < ind; j++) if ((i >> j) & 1) {
			C[i] = 1ll * C[i] * A[j] % mod;
		}
		for (int y = 1; y < len; y++) if (i & y)
			god[i].push_back(y);
	}

	go(0, 1);
	
	cout << ans << "\n";
	return 0;
}