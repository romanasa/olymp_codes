#include <bits/stdc++.h>

using namespace std;

int main() {
	int n = (int)1e3;
	int maxc = (int)1e6;
	cout << n << " " << 1ll * n * (n - 1) / 2 << "\n";
	for (int i = 0; i < n; i++) cout << maxc - i << " \n"[i == n - 1]; 
}