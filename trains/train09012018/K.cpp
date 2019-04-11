#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

void mult (vector<int> & a, const vector<int> & b) {
	vector<int> aa (a);
	for (size_t i=0; i<a.size(); ++i)
		a[i] = aa[b[i]];
}
 
int cnt_cycles (vector<int> a) {
	int res = 0;
	for (size_t i=0; i<a.size(); ++i)
		if (a[i] != -1) {
			++res;
			for (size_t j=i; a[j]!=-1; ) {
				size_t nj = a[j];
				a[j] = -1;
				j = nj;
			}
		}
	return res;
}
 
int main() {
	int n, m;
	cin >> n >> m;
 
	vector<int> p (n*m),  p1 (n*m),  p2 (n*m),  p3 (n*m);
	for (int i=0; i<n*m; ++i) {
		p[i] = i;
		p1[i] = (i % n + 1) % n + i / n * n;
		p2[i] = (i / n + 1) % m * n + i % n;
		p3[i] = (m - 1 - i / n) * n + (n - 1 - i % n);
	}
 
	ll sum = 0,  cnt = 0;
	set<vector<int> > s;
	for (int i1=0; i1<n; ++i1) {
		for (int i2=0; i2<m; ++i2) {
			for (int i3=0; i3<2; ++i3) {
				if (!s.count(p)) {
					s.insert(p);
					++cnt;
					sum += 1ll << cnt_cycles(p);
				}
				mult(p, p3);
			}
			mult(p, p2);
		}
		mult(p, p1);
	} 
	
	cout << sum / cnt;
	return 0;
}