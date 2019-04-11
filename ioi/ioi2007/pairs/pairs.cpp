#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

int b, n, d, m;
	
const int dd = (int)1e5 + 7;
int A[dd];
pair<int, int> B[dd];

const int sz = (int)2e5 + 7;
	
struct FenTree {
	
	int T[sz];
	
	void upd(int pos, int val) {
		for (int i = pos + 1; i < sz; i += (i&-i))
			T[i] += val;
		//err("T[%d] += %d\n", pos, val);
	}
	
	int get(int pos) {
		int res = 0;
		for (int i = pos + 1; i; i -= (i&-i))
			res += T[i];
		return res;
	}
	
	int get(int l, int r) {
		//err("+= sum(%d, %d)\n", l, r);
		return get(r) - get(l - 1);
	}
} F;

const int size = 228;

struct FenTree3D {	
	int T[size][size][size];
	
	void upd(int a, int b, int c, int val) {

		for (int i = a + 1; i < size; i += (i&-i)) {
			for (int j = b + 1; j < size; j += (j&-j)) {
				for (int k = c + 1; k < size; k += (k&-k)) {
					T[i][j][k] += val;
				}
			}
		}	
	}
	
	int get(int a, int b, int c) {
		int res = 0;
		for (int i = a + 1; i; i -= (i&-i)) {
			for (int j = b + 1; j; j -= (j&-j)) {
				for (int k = c + 1; k; k -= (k&-k)) {
					res += T[i][j][k];
				}
			}
		}
		return res;
	}
	
	int get(int x1, int y1, int z1, int x2, int y2, int z2) {
		
		int t22 = get(x2, y2, z2) - get(x2, y2, z1 - 1);
		int t12 = get(x1 - 1, y2, z2) - get(x1 - 1, y2, z1 - 1);
		int t21 = get(x2, y1 - 1, z2) - get(x2, y1 - 1, z1 - 1);
		int t11 = get(x1 - 1, y1 - 1, z2) - get(x1 - 1, y1 - 1, z1 - 1);
		
		return t22 - t12 - t21 + t11;
	}
} Q;

struct ev {
	int a, b, c, d;
	bool operator < (ev Q) const {
		return a < Q.a;
	}
} C[dd];

int main() {
	scanf("%d %d %d %d", &b, &n, &d, &m);

	if (b == 1) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &A[i]);
		}
		
		sort(A, A + n);
		
		ll ans = 0;
		for (int i = 0; i < n; i++) {
			int ind = lower_bound(A, A + n, A[i] - d) - A;
			ans += (i - ind);
		}
		printf("%lld\n", ans);
	}

	if (b == 2) {
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			B[i] = { x + y, x - y + m };
		}
		
		sort(B, B + n);
		
		//err("B = {"); for (int i = 0; i < n; i++) err(" (%d, %d),", B[i].first, B[i].second); err(" }\n");
		
		ll ans = 0;
		int j = 0;
		for (int i = 0; i < n; i++) {
		
			F.upd(B[i].second, 1);
			
			while (j < i && B[i].first - B[j].first > d) {
				F.upd(B[j].second, -1);
				j++;
			}
			
			ans += F.get(max(B[i].second - d, 1), min(B[i].second + d, m + m)) - 1;
		}
		
		printf("%lld\n", ans);	
	}	
	
	if (b == 3) {
		for (int i = 0; i < n; i++) {
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			C[i] = { x + y + z, x + y - z + m, x - y + z + m, x - y - z + m + m };
		}
		sort(C, C + n);
		
		ll ans = 0;
		int j = 0;
		for (int i = 0; i < n; i++) {
			
			Q.upd(C[i].b, C[i].c, C[i].d, 1);
			
			while (j < i && C[i].a - C[j].a > d) {
				Q.upd(C[j].b, C[j].c, C[j].d, -1);
				j++;
			}
			
			int x1 = max(C[i].b - d, 1);
			int x2 = min(C[i].b + d, m + m + m);
			
			int y1 = max(C[i].c - d, 1);
			int y2 = min(C[i].c + d, m + m + m);
			
			int z1 = max(C[i].d - d, 1);
			int z2 = min(C[i].d + d, m + m + m);
		
			ans += Q.get(x1, y1, z1, x2, y2, z2) - 1;
		}
		
		printf("%lld\n", ans);
	}

	return 0;
}