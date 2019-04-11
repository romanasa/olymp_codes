#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int p = 3;
const int mod = (int)8e8 + 7;


#define TASK "compression"
int main() {
#ifndef HOME
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	
	int l, m;
	cin >> l >> m;
	
	string s;
	cin >> s;
	int n = (int)s.size();
	vector<int> A(n - l + 1);
	
	map<int, int> M;
	multiset<int> S;
	
	for (int i = 0; i + l <= n; i++) {
		int h = 0;
		for (int j = 0; j < l; j++) h = (1ll * h * p + s[i + j] - '0' + 1) % mod;
		A[i] = h;
	}
	
	//err("A = {"); for (int x : A) err(" %d,", x); err(" }\n");
	
	for (int i = 0; i < n; i++) S.insert(0);
	
	for (int i = 0; i <= m - l; i++) {
		auto it = S.find(M[A[i]]);
		S.erase(it);
		M[A[i]]++;
		S.insert(M[A[i]]);
		//err("add %d\n", A[i]);
	}
	
	for (int i = 0; i + m <= n; i++) {
	
		//err("i = %d, j = %d, S = {", i, i + m - l); err(" }\n");
	
		//for (auto c : M) err("(%d, %d), ", c.first, c.second); err("\n");
		
		cout << *S.rbegin() << " ";
		if (i + m == n) continue;
		
		//err("add %d\n", A[i + m - l + 1]);
		auto it = S.find(M[A[i + m - l + 1]]);
		S.erase(it);
		M[A[i + m - l + 1]]++;
		S.insert(M[A[i + m - l + 1]]);
		
		
		//err("del %d\n", A[i]);
		it = S.find(M[A[i]]);
		S.erase(it);
		M[A[i]]--;
		S.insert(M[A[i]]);
	}
	return 0;
}