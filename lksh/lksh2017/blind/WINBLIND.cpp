#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int k;
	cin >> k;
	
	vector<int> a;
	int x;
	while (cin >> x) a.push_back(x);
	a.pop_back();
	
	vector<pair<int, int> > Q;
	for (int i: a) if (Q.empty() || Q.back().first != i) Q.push_back({ i, 1 });
	else Q.back().second++;
	if (Q.empty() || Q[0].first != 0) cout << "0 ";
	for (auto c : Q) {
		while (c.second > k) { cout << k << " " << 0  << " ";
		c.second -= k;
		}
		cout << c.second << " ";
	}
	return 0;
}