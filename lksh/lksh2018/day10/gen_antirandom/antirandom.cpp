#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int cx = -1e9, cy = 1e9;
	
	vector<pair<int, int> > T;
	
	T.push_back({ cx, cy });
	
	int cnt = 0;

	
	for (int t = 1; cx < (int)1e9 && T.size() < (int)5e4; t++) {
		cx += t;
		cy -= 1;
		T.push_back({ cx, cy });
		cnt++;
	}
	
	for (int t = 1; t < cnt; t++) {
		cx -= t; 
		cy += 1;
		T.push_back({ cx, cy });
	}
	
	cout << (int)T.size() << "\n";
	for (auto c : T) cout << c.first << " " << c.second << "\n";
	
	return 0;
}