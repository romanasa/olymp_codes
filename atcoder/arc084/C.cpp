#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int k, n;

int main() {	
	cin >> k >> n;
	vector<int> cur(n + 1);
	
	if (k % 2 == 0) {
		cout << k / 2 << " ";
		for (int i = 1; i < n; i++) cout << k << " ";
		return 0;
	}
	
	
	for (int i = 0; i < n; i++) cur[i] = (k + 1) / 2;
	
	int last = n - 1;
	for (int it = 0; it < n / 2; it++) {
		if (cur[last] == 1) {
			last--;
		} else {
			cur[last]--;
			while (last + 1 < n) cur[last + 1] = k, last++;
		}
	}
	for (int i = 0; i <= last; i++) cout << cur[i] << " ";
	cout << "\n";
	return 0;
}