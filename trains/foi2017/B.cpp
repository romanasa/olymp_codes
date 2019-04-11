#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

set<int> fr;
map<int, int> cnt;

void add(int x) {
	fr.erase(x);
	cnt[x]++;
}

void del(int x) {
	cnt[x]--;
	if (cnt[x] == 0) fr.insert(x);
}

int main() {
	int n, k;
	cin >> n >> k;
	
	for (int i = 0; i < n + 2; i++) fr.insert(i);
	
	vector<int> A(n);
	for (int i = 0; i < k - 1; i++) {
		cin >> A[i];
		add(A[i]);
	}
	
	for (int i = k - 1; i < n; i++) {
		cin >> A[i];
		add(A[i]);
		cout << *fr.begin() << " ";
		del(A[i - k + 1]);
	}
	
	return 0;
}