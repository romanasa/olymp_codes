#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<char> L = { 'R', 'G', 'B' };

int main(int argc, char* argv[]) {
	srand(atoi(argv[1]));

	
	int n = 50;
	int m = rand() % 1000 + 1;
	
	cout << n << " " << m << "\n";
	for (int i = 0; i < n; i++) cout << L[rand() % 3];
	cout << "\n";
	
	for (int i = 0; i < m; i++) {	
		int a = rand() % n + 1;
		int b = rand() % n + 1;
		while (a == b) a = rand() % n + 1, b = rand() % n + 1;
		cout << rand() % n + 1 << " " << rand() % n + 1 << "\n";
	}
	
	return 0;
}