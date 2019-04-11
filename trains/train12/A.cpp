#include <iostream>
#include <algorithm>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 1;
int x[dd], st[dd], sz;
double r[dd];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.precision(4);
	
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> r[i];
	}
	
	for (int i = 0; i < n; i++) {
		double cur = r[i];
		while (sz) {
			int ind = st[sz - 1];
			cur = min(cur, 1.0 * (x[ind] - x[i]) * (x[ind] - x[i]) / (4 * r[ind]));
			if (cur >= r[ind]) sz--;
			else break;
		}
		st[sz++] = i;
		r[i] = cur;
		cout << fixed << r[i] << "\n";
	}
	
	return 0;
}