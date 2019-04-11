#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int a[207], b[207], l[207], r[207], c[207];
int T[107];
int A[107];

int ans = (int)1e9;
int n, k;
	
int calc(int x) {
	int cur = 0;
	for (int i = 0; i < k; i++) {
		for (int j = a[i]; j <= b[i]; j++) {
			if (T[j] < l[i] || T[j] > r[i]) {
				cur += c[i];
				if (cur >= x) break;
				break;
			}
		}
	}
	
	if (cur < ans) {
		ans = cur;
		copy(T, T + n + 1, A);
	}
	
	return cur;
}

int main() {
	cin >> n >> k;
	
	for (int i = 0; i < k; i++) cin >> a[i] >> b[i] >> l[i] >> r[i] >> c[i];
	
	for (int it = 0; it < k; it++) {
		for (int i = 0; i + 1 < k; i++) {
			if (c[i] > c[i + 1]) {
				swap(a[i], a[i + 1]);
				swap(b[i], b[i + 1]);
				swap(l[i], l[i + 1]);
				swap(r[i], r[i + 1]);
				swap(c[i], c[i + 1]);
			}
		}
	}
	
	srand(228);
	
	
	fill(T, T + n, 0);
   	for (int j = 0; j < k; j++) {
   		for (int i = a[j]; i <= b[j]; i++) if (T[i] < l[j] || T[i] > r[j]) {
   			T[i] = l[j];
   		}
   	}

	for ( ; ; ) {

		int cur = calc((int)1e9);
		for (int it2 = 0; it2 < 10 * n * n; it2++) {
		
			int i = rand() % n;
			int j = rand() % 10;
			
			int old = T[i];
			
			int k = rand() % n;
			int l = rand() % 10;
			
			int old2 = T[k];
			
			T[i] = j;
			T[k] = l;
			
			int t = calc(cur);
			
			if (t < cur) cur = t;
			else T[i] = old, T[k] = old2;
		}	
		if (clock() > CLOCKS_PER_SEC * 0.5) break;
		
		for (int i = 0; i < n; i++) T[i] = rand() % 10;
	}
	//err("ans = %d\n", ans);
	for (int i = 0; i < n; i++) cout << A[i]; cout << "\n";
	return 0;
}