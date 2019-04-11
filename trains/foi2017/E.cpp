#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int a[1234][1234];

int main() {
	int n;
	cin >> n;
	
	if (n <= 3) return 0 * puts("QAQ");
	if (n == 4) {
		cout << "1 1 1 2\n1 2 2 3\n2 3 4 4\n3 4 4 3\n";
		return 0;
	}//assert(0);
	
	for (int i = 1; i <= n; i++) a[1][i] = a[i][1] = i;
	for (int i = 1; i <= n; i++) a[n][i] = 1;
	for (int i = 1; i <= n; i++) a[i][n] = n;
	for (int i = 2; i < n; i++) 
		for (int j = 2; j < n; j++) a[i][j] = (i + j - 4) % (n - 2) + 2;
		
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) cout << a[i][j] << " \n"[j == n];
	
	return 0;
}