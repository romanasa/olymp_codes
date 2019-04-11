#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:66777216")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>
#include <cstring>
#include <sstream>
#include <numeric>

using namespace std;

typedef long long ll;

#define TASK "o"
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout);
#define all(v) v.begin(), v.end()

int solve();

int main() {
#ifdef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//if (TASK != "")
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
	return 0;
}

const int dd = (int)1e5 + 7;
const int inf = (int)1e9 + 7;

struct pt {
	ll x, y;
};

ll dist(pt A, pt B) {
	return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y);
}

int n, m;
int A[7][7];
int ans = 0;
void gen(int x) {
	if (x == n * m) {
		ans++;
		return;
	}

	int i = x / m, j = x % m;

	bool ok1 = i == 0 || A[i - 1][j] == 2 || A[i - 1][j] == 3;
	bool ok2 = i == 0 || A[i - 1][j] == 1 || A[i - 1][j] == 4;
	bool ok3 = j == 0 || A[i][j - 1] == 1 || A[i][j - 1] == 2;
	bool ok4 = j == 0 || A[i][j - 1] == 3 || A[i][j - 1] == 4;

	if (ok1 && ok4) {
		A[i][j] = 1;
		gen(x + 1);
	}
	if (ok1 && ok3) {
		A[i][j] = 4;
		gen(x + 1);
	}
	if (ok2 && ok3) {
		A[i][j] = 3;
		gen(x + 1);
	}
	if (ok2 && ok4) {
		A[i][j] = 2;
		gen(x + 1);
	}
}

const int mod = (int)1e6 + 3;

int solve() {
	int n, m;
	scanf("%d %d", &n, &m);

	vector<vector<int> > A(n, vector<int>(m));
	vector<vector<int> > R(n, vector<int>(2)), C(m, vector<int>(2));

	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m; j++) {
			A[i][j] = (s[j] == '.' ? 0 : s[j] - '0');
		}
	}


	int ans = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (A[i][j] == 1 || A[i][j] == 2) {
				if ((j ^ 0) & 1)
					R[i][1] = 1;
				else
					R[i][0] = 1;
			}
			if (A[i][j] == 3 || A[i][j] == 4) {
				if ((j ^ 1) & 1)
					R[i][1] = 1;
				else
					R[i][0] = 1;
			}

			if (A[i][j] == 1 || A[i][j] == 4) {
				if ((i ^ 0) & 1)
					C[j][1] = 1;
				else
					C[j][0] = 1;
			} 
			if (A[i][j] == 2 || A[i][j] == 3) {
				if ((i ^ 1) & 1)
					C[j][1] = 1;
				else
					C[j][0] = 1;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		ans = ans * (2 - R[i][0] - R[i][1]) % mod;
	}
	for (int j = 0; j < m; j++) {
		ans = ans * (2 - C[j][0] - C[j][1]) % mod;
	}
	cout << ans;
	return 0;
}