#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
int d[dd];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	fill(d, d + dd, (int)1e9);
	
	int k;
	cin >> k;
	
	priority_queue<pair<int, int> > S;
	
	for (int i = 1; i <= min(9, k); i++) {
		d[i % k] = i;
		S.push({ -d[i % k], i % k });
	}
	
	while (S.size()) {
		int mod = S.top().second;
		int len = -S.top().first;
		
		S.pop();
		
		if (d[mod] != len) continue;
		
		for (int c = 0; c < 10; c++) {
			int to = (mod * 10 + c) % k;
			if (d[to] > d[mod] + c) {
				d[to] = d[mod] + c;
				S.push({ -d[to], to });
			}
		}
	}
	
	cout << d[0] << "\n";
	return 0;
}