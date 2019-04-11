#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<int> A = { 3, 4, 5, 6 };
vector<int> B = { 80, 100, 120, 140 };

int main() {
	int n;
	cin >> n;
	cout << A[n - 1] * B[n - 1] << "\n";
	return 0;
}