#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
	srand(atoi(argv[1]));
	int n = 20, d = rand() % (2 * n + n / 2), start = rand() % n;
	cout << n << " " << start << " " << d << "\n";
	for (int i = 0; i < n; i++) cout << rand() % (int)1e2 << " ";
	cout << "\n";
	return 0;
} 
