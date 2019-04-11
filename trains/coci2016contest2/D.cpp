#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int a[123][123];

int main() {
	int n;
	cin >> n;
	
	if (n % 2) {
		int cnt = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cout << cnt++ << " ";
			cout << "\n";
		}
	} else {
	
		if (n == 2) return 0 * puts("-1");
		
		
		for (int i = 0; i < n - 1; i++) a[0][i] = i + 1;
		a[0][n - 1] = n * (n - 1) / 2;
		
		for (int i = 1; i < n; i++)
			for (int j = 0; j < n; j++)
				a[i][j] = a[i - 1][j] + n * (n - 1) / 2;
        
		for (int j = 0; j < n; j++) {
			a[n - 1][j] = a[n - 2][j] * n;
			for (int i = 0; i < n - 1; i++) a[n - 1][j] -= a[i][j];
		}	
				
        for (int i = 0; i < n; i++) {
        	for (int j = 0; j < n; j++) cout << a[i][j] << " ";
        	cout << "\n";
        }
		
		//cout << (q / n) << " " << q % n << "\n";
	}
	return 0;
}