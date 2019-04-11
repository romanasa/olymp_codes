#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct vt {
	int x, y;
	vt() {}
	vt(vt a, vt b) {
		x = b.x - a.x;
		y = b.y - a.y;
	}
	inline ll operator % (vt b) {
		return x * b.y - y * b.x;
	}
};

bool inter(vt A, vt B, vt C, vt D) {
	return ((vt(A, B) % vt(A, C)) * (vt(A, B) % vt(A, D)) <= 0 &&
	 (vt(C, D) % vt(C, A)) * (vt(C, D) % vt(C, B)) <= 0);
}

int main() {
#ifndef HOME
	freopen("ants.in", "r", stdin);
	freopen("ants.out", "w", stdout);
#endif

	int n;
	scanf("%d", &n);
	
	vector<vt> P(n), T(n);
	
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &P[i].x, &P[i].y);
	}
	
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &T[i].x, &T[i].y);
	}
	
	vector<int> ans(n);

	for (int i = 0; i < n; i++)
		ans[i] = i;	

	random_shuffle(ans.begin(), ans.end());
		
	bool ok = true;
	while (ok) {
		ok = false;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (inter(P[i], T[ans[i]], P[j], T[ans[j]])) {
					swap(ans[i], ans[j]);
					ok = true;
				}
	}
		
	for (int x : ans) {
		printf("%d\n", x + 1);
	}
	
	return 0;
}
