#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int C = 1000;

int main(int argc, char* argv[]) {
	srand(atoi(argv[1]));
	
	cout << 1 << "\n";
	
	for (int i = 0; i < 6; i++) {
		cout << rand() % (2 * C + 1) - C << " ";
		if (i % 2 == 1) cout << "\n";
	}
	
	return 0;
}