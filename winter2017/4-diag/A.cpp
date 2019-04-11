#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int n, k;

vector<pair<int, int> > cur;

int b[123];
int h[123];

void up(int pos, int val) {
	while (b[pos] < val) b[pos] += k, cur.push_back({ 1, pos });
}

void drop(int l) {
	int r = l + k;
	
	int h = 0;
	for (int i = l; i < r; i++) h = max(h, b[i]);
	
	for (int i = 0; i < l; i++) up(i, h + 1);
	for (int i = r; i < n; i++) up(i, h + 1);
	
	cur.push_back({ 2, l });
	
	for (int i = 0; i < l; i++) b[i]--;
	for (int i = r; i < n; i++) b[i]--;
}

int main() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> h[i];
	
	for (int it = 0; it < k; it++) {
	
		cur.clear();
		for (int i = 0; i < n; i++) b[i] = h[i];
		
		
		for (int j = 0; j < it; j++) drop(0);
		
		for (int i = 1; i <= n - k; i++) {
			while (b[i] % k != b[0] % k) drop(i);
		}
		
		//err("b = "); for (int i = 0; i < n; i++) err("%d, ", b[i]); err("\n");
		
		int ok = 1;
		for (int i = 0; i < n; i++) ok &= (b[i] % k == b[0] % k);
		
		if (ok) {
		
			int h = *max_element(b, b + n);
			for (int i = 0; i < n; i++) up(i, h);
		
			cout << cur.size() << "\n";
			for (auto c : cur) cout << c.first << " " << c.second + 1 << "\n";
			return 0;
		}
	}
	cout << "-1\n";
	return 0;
}