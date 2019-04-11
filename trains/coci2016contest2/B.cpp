#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n, m, k, x;
	cin >> n >> m >> k >> x;
	
	string s;
	cin >> s;
	
	vector<string> A(m);
	for (int i = 0; i < m; i++) {
		cin >> A[i];
		sort(A[i].begin(), A[i].end());
	}
	
	x--;
	
	
	vector<int> t;
	for (int j = 0; j < m; j++) t.push_back(x % k), x /= k;
	reverse(t.begin(), t.end());
	
	int ind = 0;
	
	for (int i = 0; i < n; i++) {
		if (s[i] != '#') cout << s[i];
		else {
			cout << A[ind][t[ind]];
			ind++;
		}
	}
	cout << "\n";
	
	return 0;
}