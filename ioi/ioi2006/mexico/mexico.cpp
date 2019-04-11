#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int dd = (int)1001;

int G[dd][dd], L[dd][dd], R[dd][dd];
int n, m;

int getR(int, int);
void recR(int, int);

inline int nxt(int x) {
	return (x + 1 == n ? 0 : x + 1);
}

inline int prv(int x) {
	return (x == 0 ? n - 1 : x - 1);
}

int getL(int a, int b) {
	if (a == b) {
		return 1;
	}
	if (L[a][b] != -1)
		return L[a][b];
		
	L[a][b] = 0;
	
	if (getL(a, prv(b)) && G[prv(b)][b])
		L[a][b] = 1;
		
	if (getR(prv(b), a) && G[a][b])
		L[a][b] = 1;
		
	return L[a][b];
}

vector<int> ans;

void recL(int a, int b) {
	//err("recL(%d, %d)\n", a + 1, b + 1);
	if (a == b) {
		ans.push_back(a);
		return;
	}
	if (getL(a, prv(b)) && G[prv(b)][b]) {
		recL(a, prv(b));
	} else if (getR(prv(b), a) && G[a][b]) {
		recR(prv(b), a);
	}
	ans.push_back(b);
}

int getR(int a, int b) {
	if (a == b) {
		return 1;
	}
	if (R[a][b] != -1)
		return R[a][b];
		
	R[a][b] = 0;
	
	if (getR(a, nxt(b)) && G[b][nxt(b)])
		R[a][b] = 1;
		
	if (getL(nxt(b), a) && G[a][b])
		R[a][b] = 1;
		
	return R[a][b];
}

void recR(int a, int b) {
	//err("recR(%d, %d)\n", a + 1, b + 1);
	if (a == b) {
		ans.push_back(a);
		return;
	}
	if (getR(a, nxt(b)) && G[b][nxt(b)]) {
		recR(a, nxt(b));
	} else if (getL(nxt(b), a) && G[a][b]) {
		recL(nxt(b), a);
	}
	ans.push_back(b);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		G[a - 1][b - 1] = G[b - 1][a - 1] = 1;
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			L[i][j] = -1, R[i][j] = -1;
		}
	}
	
	
	int ok = 0;
	for (int i = 0; i < n && !ok; i++) {
		for (int j = 0; j < n && !ok; j++) {
			if (getL(nxt(i), j) && getR(i, j)) {
				ok = 1;
				
				recL(nxt(i), j);
			
				auto A = ans;
				ans.clear();
				
				recR(i, j);
				
				auto B = ans;
				
				B.pop_back();
				reverse(B.begin(), B.end());

			
				for (int x : A) printf("%d\n", x + 1);
				for (int x : B) printf("%d\n", x + 1);	
			}
		}
	}
	
	if (!ok) {
		puts("-1");
		return 0;
	}
	
	return 0;
}