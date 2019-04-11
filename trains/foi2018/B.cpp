#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<int> q;

void SWAP(int i, int len) {
	for (int it = 0; it < len - i; it++) q.push_back(1);
	q.push_back(0);
	for (int it = 0; it < i; it++) q.push_back(1);
}

int main() {
	string s;
	cin >> s;
	
	
	for (int it = 0; it < (int)s.size(); it++) {
		for (int i = 0; i + 1 < (int)s.size(); i++) {
			if (s[i] > s[i + 1]) {
				swap(s[i], s[i + 1]);
				SWAP(i, (int)s.size());
			}
		}
	}
	
	//assert(s.size() <= 50);
	
	cout << q.size() << "\n";
	for (auto c : q) cout << (c ? "MOVE\n" : "SWAP\n");

	return 0;
}