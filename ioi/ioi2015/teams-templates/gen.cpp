#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
	srand(atoi(argv[1]));
	int n = 15;
	int m = 10;
	cout << n << "\n";
	for (int i = 0; i < n; i++) {
		int l = rand() % n + 1, r = rand() % n + 1;
		if (l > r) swap(l, r);
		cout << l << " " << r << "\n";
	}
	

	cout << m << "\n";
	for (int i = 0; i < m; i++) {
		int k = rand() % 3 + 1;
		cout << k << " ";
		for (int j = 0; j < k; j++)
			cout << rand() % 3 + 1 << " ";
		cout << "\n"; 
	}
	return 0;
}



