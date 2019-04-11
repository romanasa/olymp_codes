#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct ant {
	int pos;
	char dir;
	int id;
};

int main() {
	int n, l;
	while (cin >> n >> l) {
		if (n == 0 && l == 0) break;
		
		vector<ant> A(n);
		for (int i = 0; i < n; i++) {
			cin >> A[i].dir >> A[i].pos;
			A[i].id = i;
		}
		
		int tmm = 0;
		
		while (A.size()) {
			
			auto nA = A;
			vector<int> L, R;
			
			for (int i = 0; i < (int)A.size(); i++) {
				if (A[i].dir == 'R') {
   					if (i + 1 < (int)A.size() && A[i + 1].dir == 'L' && A[i].pos + 1 == A[i + 1].pos) {
   						swap(nA[i].dir, nA[i + 1].dir);
   						swap(nA[i].id, nA[i + 1].id);
   					} else if (i + 1 < (int)A.size() && A[i + 1].dir == 'L' && A[i].pos + 1 == A[i + 1].pos - 1) {
   						nA[i].pos = A[i].pos + 1;
   						nA[i + 1].pos = A[i + 1].pos - 1;
   						nA[i].dir = 'L', nA[i + 1].dir = 'R';
   						//swap(nA[i], nA[i + 1]);
   					} else {
   						nA[i].pos++;
   					}
				} else {
					if (i > 0 && A[i - 1].pos + 2 >= A[i].pos && A[i-1].dir=='R') {
					} else nA[i].pos--;
				}
			}
			
			A.clear();
			vector<ant> cur;
			for (auto c : nA) {
				if (c.pos <= 0) L.push_back(c.id);
				else if (c.pos >= l) R.push_back(c.id);
				else cur.push_back(c);
			}
			A = cur;
			for (int i = 0; i  + 1 < (int)A.size(); i++) {
				if (A[i].pos == A[i + 1].pos) {
					A[i].dir = 'L';
					A[i + 1].dir = 'R';
				}
			}
			tmm++;
			
			//if (tmm > 10) return 0;
			
			err("sz = %d\n", (int)A.size());
			err("A = "); for (auto c : A) err("(%d, %c, %d), ", c.pos, c.dir, c.id); err("\n");
			//sort(A.begin(), A.end(), [](ant a, ant b) {
			//	return a.pos == b.pos ? a.dir == 'L' && b.dir == 'R' : a.pos < b.pos;
			//});
			if (A.empty()) cout << tmm << " " << (L.size() ? L[0] : R[0]) + 1 << "\n";
		}
	}
	return 0;
}