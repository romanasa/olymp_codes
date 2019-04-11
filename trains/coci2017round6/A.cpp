#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;


int c[] = { 53, 52, 52, 52, 52, 52, 52 };

int main() {

	int n;
	cin >> n;
	
	n /= 52 * 7;
	
	
	for (int x = 100; x > 0; x--) {
		int add = n - x;
		if (add <= 0 || add % 3) continue;
		cout << x << "\n" << add / 3 << "\n";
		break;
	}

	return 0;
}