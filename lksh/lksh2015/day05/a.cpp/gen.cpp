#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

string A = "0123456789ABCDEF";

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n = 1e5;
	cout << n << "\n";
	
	mt19937 rnd(1);
	for (int i = 0; i < n; i++) {
		cout << A[rnd() % 16] << A[rnd() % 16] << " ";
	}
	cout << "\n";
	return 0;
}