#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int Gx[123], Gy[123];
int ix, iy;

int main() {
	int n;
	cin >> n;
	
	vector<pair<int, int> > T(2 * n);
	for (int i = 0; i < 2 * n; i++) {
		int x, y;
		cin >> x >> y;
		
		T[i] = { x, y };
		
		Gx[ix++] = x;
		Gy[iy++] = y;
	}
	
	sort(Gx, Gx + ix); ix = unique(Gx, Gx + ix) - Gx;
	sort(Gy, Gy + iy); iy = unique(Gy, Gy + iy) - Gy;
	
	for (int i = 0; i < 2 * n; i++) {
		err("(%d, %d), ", lower_bound(Gx, Gx + ix, T[i].first) - Gx + 1, lower_bound(Gy, Gy + iy, T[i].second) - Gy + 1);
		if (i % 2 == 1) err("\n");
	}
	/*
	for (int i = 0; i < ix; i++) {
		err("x = %d --> %d\n", Gx[i], i + 1);
	}	
	
	for (int i = 0; i < iy; i++) {
		err("y = %d --> %d\n", Gy[i], i + 1);
	}*/
	
	return 0;
}