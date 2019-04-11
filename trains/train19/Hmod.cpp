#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = 786433;
const int root = 8;

const int LOG = 17;
const int N = 1 << LOG;
const int maxC = (int)5e4 + 7;

int rev[N];
int p[N], Q[N], res[N], tmp[N];
int sum[maxC];

int bp(int a, int n) {
	if (!n) return 1;
	if (n & 1) return 1ll * bp(a, n - 1) * a % mod;
	int t = bp(a, n / 2);
	return 1ll * t * t % mod;
}

void calc() {
	for (int i = 0; i < N; i++) {
		rev[i] = 0;
		for (int j = 0; j < LOG; j++) if ((i >> j) & 1)
			rev[i] ^= 1 << (LOG - j - 1);
	}
}

void fft(int *A, bool inv = false) {
    for (int i = 0; i < N; i++) if (i < rev[i]) swap(A[i], A[rev[i]]);
    for (int l = 2; l <= N; l *= 2) {
        int t = l / 2;
 		int wn = bp(root, N / l);
 		if (inv) wn = bp(wn, mod - 2);
        for (int i = 0; i < N; i += l) {
            int w = 1;
            for (int j = 0; j < t; j++) {
                int u = A[i + j];
                int v = 1ll * A[i + j + t] * w % mod;
                A[i + j] = (u + v) % mod;
                A[i + j + t] = (u - v + mod) % mod;
                w = 1ll * w * wn % mod;
            }
        }
    }
    if (inv) {
    	int revn = bp(N, mod - 2);
    	for (int i = 0; i < N; i++) A[i] = 1ll * A[i] * revn % mod;
    }
}
 
void mul(int *A, int *B) {
    copy(B, B + N, tmp);
    fft(A);
    fft(tmp);
    for (int i = 0; i < N; i++) A[i] = 1ll * A[i] * tmp[i] % mod;
    fft(A, true);
 	for (int i = maxC; i < N; i++) A[i] = 0;
}


int main() {
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    calc();
     
    int n, k, q;
    cin >> n >> k >> q;
 
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        Q[t]++;
    }
 
    copy(Q, Q + N, p);
    copy(Q, Q + N, res);

    k--;
 
    while (k) {
        if (k & 1) mul(res, p);
        mul(p, p);
        k /= 2;
    }
    
	//for (int i = 0; i < 10; i++) cout << res[i] << " ";
	//cout << "\n";
    
    for (int i = 0; i + 1 < maxC; i++) {
        sum[i + 1] = sum[i] + res[i];
        if (sum[i + 1] >= mod) sum[i + 1] -= mod;
    }
 
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << (sum[r + 1] - sum[l] + mod) % mod << "\n";
    }
 
 
	
	return 0;
}