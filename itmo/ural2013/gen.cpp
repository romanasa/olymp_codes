#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main(int argc, char* argv[]) {
	
	mt19937 rnd(atoi(argv[1]));
	
	int n = 3 + atoi(argv[1]) / 5;
	cout << n << "\n";
	for (int i = 0; i < n; i++) {
		cout << rand() % 3 - 1 << " " << rand() % 3 - 1 << "\n";
	}

	return 0;
}