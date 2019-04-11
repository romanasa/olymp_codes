#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

vector<vector<pair<int, int> > > E;

int A[507];

double get(int v, int e) {
	if (e == 0)
		return 0;
	return v * 1.0 / e;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	E.resize(n);
	
	for (int i = 0; i < n; i++)
		scanf("%d", &A[i]);
	
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		E[a - 1].push_back({ b - 1, c });
		E[b - 1].push_back({ a - 1, c });
	}	
	
	
	double ans = 0;
	for (int i = 0; i < n; i++) {
		
		vector<int> T(1, i), used(n);

		used[i] = 1;	
		int v = A[i], e = 0;
		
		while (1) {
			int ind = -1;
			double cur = 0;
			
			for (int j = 0; j < n; j++) {
				if (used[j])
					continue;
				
				int curc = 0;
				for (auto c : E[j]) {
					if (used[c.first])
						curc += c.second;
				}

				if (curc == 0)
					continue;	
				
				double t = get(A[j], curc);
				
				if (ind == -1 || t > cur) {
					ind = j;
					cur = t;
				}
			}
			
			
			if (ind == -1)
				break;
				
			used[ind] = 1;
			
			int curc = 0;
			for (auto c : E[ind]) {
				if (used[c.first])
					curc += c.second;
			}
			
			double t = get(A[ind], curc);
			
			if (t > get(v, e)) {
				v += A[ind];
				e += curc;	
			} else {
				break;
			}
		}
		ans = max(ans, get(v, e));
	}
	printf("%.10f", ans);
	return 0;
}