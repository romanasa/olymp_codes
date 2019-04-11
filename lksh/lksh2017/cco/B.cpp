#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e8 + 1;
unordered_map<int, int> Min[dd], Max[dd];

int goMin(int a, int b) {
	if (a < b) swap(a, b);
	
	if (Min[a].count(b)) return Min[a][b];
	int cur = (int)1e9;
	
	if (2 * b == a) return 1;
	
	if (2 * b < a) cur = min(cur, goMin(b, a - 2 * b) + 1);
	if (b % 2 == 0) cur = min(cur, goMin(b, a - b / 2) + 1);
	if (a % 2 == 0 && a / 2 < b) cur = min(cur, goMin(a, b - a / 2) + 1);

	return Min[a][b] = cur;
}

int goMax(int a, int b) {
	if (a < b) swap(a, b);
	if (Max[a].count(b)) return Max[a][b];
	int cur = -(int)1e9;
	if (2 * b == a) cur = max(cur, 1);
	if (2 * b < a) cur = max(cur, goMax(b, a - 2 * b) + 1);
	if (b % 2 == 0) cur = max(cur, goMax(b, a - b / 2) + 1);
	if (a % 2 == 0 && a / 2 < b) cur = max(cur, goMax(a, b - a / 2) + 1);
	return Max[a][b] = cur;
}

int main() {
	int n, m;
	cin >> n >> m;
	
	int tmp1 = goMin(n, m);
	int tmp2 = goMax(n, m);
	
	cout << tmp1 << " " << tmp2 << "\n";
	return 0;
}