#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main(int argc, char* argv[]) {
	srand(atoi(argv[1]));
	int r = 4, c = 3;
	
	cout << r << " " << c << "\n";
	
	int n = 5;
	cout << n << "\n";
	for (int i = 0; i < n; i++) {
		int tp = 1 + rand() % 2;
		cout << tp << " ";
		if (tp == 1) {
			cout << rand() % r << " " << rand() % c << " " << rand() % 10 << "\n";
		} else {
			int lx = rand() % r, rx = rand() % r;
			int ly = rand() % c, ry = rand() % c;
			if (lx > rx) swap(lx, rx);
			if (ly > ry) swap(ly, ry);
			cout << lx << " " << ly << " " << rx << " " << ry << "\n";
		}
	}
	return 0;
}