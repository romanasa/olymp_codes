#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	
	vector<int> cnt(n + 1);
	vector<pair<int, int> > A(n);
	
	for (int i = 0; i < n / 2 + 1; i++) {
		int a, b;
		cin >> a >> b;
		
		A[i] = { a, b };
		cnt[a]++, cnt[b]++;
	}
	
	for (int i = 0; i < n / 2 + 1; i++) {
		if (cnt[A[i].first] == 2 && cnt[A[i].second] == 2) {
			cout << A[i].first << " " << A[i].second << "\n";
			return 0;
		}
	}
	
	return 0;
}