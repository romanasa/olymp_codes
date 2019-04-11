#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	
	for (int n = 1; n <= 1000; n++) {
		
		int ok = 0;
    	for (int x = 1; x <= n; x++) {
    		for (int y = x + 1; x + y < n; y++) if (y % x == 0) {
    			int z = n - x - y;
    			if (z > y && z % y == 0) {
    				ok = 1;
    				cout << x << " " << y << " " << z << "\n";
    			}
    		}
    	} 
	}
	return 0;
}