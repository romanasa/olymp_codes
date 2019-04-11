#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main(int argc, char* argv[]) {
	srand(atoi(argv[1]));
	
	
	int n = 5, m = 5;
	cout << "verysecret\n";
	cout << n << " " << m << "\n";
	
	for (int i = 1; i < n; i++) {
		cout << i + 1 << " " << rand() % i + 1 << " " << rand() % m + 1 << "\n";
	}
	return 0;
}