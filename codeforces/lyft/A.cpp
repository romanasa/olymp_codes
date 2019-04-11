#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int dx[] = { 1, 0, };
int dy[] = { 0, 1, };

int main() {
	int n ;
	cin >> n;
	
	int ax, ay, bx, by, cx, cy;
	cin >> ax >> ay;
	cin >> bx >> by;
	cin >> cx >> cy;
	
	
	for (int i = 0; i < 2; i++) {
		
		int ta = dx[i] * ax + dy[i] * ay;
		int tb = dx[i] * bx + dy[i] * by;
		
		int tc = dx[i] * cx + dy[i] * cy;
		
		if ((ta < tc) ^ (ta < tb)) return 0 * puts("NO");
	}
	puts("YES");
	
	
	return 0;
}