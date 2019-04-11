#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int dd = (int)1e5 + 7;

int R[dd], W[dd];
int place[dd];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &R[i]);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &W[i]);
	}
	
	queue<int> Q;
	set<int> S;
	for (int i = 0; i < n; i++) {
		S.insert(i);
	}
	
	int ans = 0;
	
	for (int i = 0; i < 2 * m; i++) {
		int t;
		scanf("%d", &t);
		
		if (t < 0) {
			t = -t;
			S.insert(place[t - 1]);
		} else {
			Q.push(t - 1);
		}
		
		while ((int)Q.size() && (int)S.size()) {
			int a = Q.front();
			int b = *S.begin();
			
			Q.pop();
			S.erase(S.begin());
			
			place[a] = b;
			ans += R[b] * W[a];
		}
	}
	printf("%d\n", ans);
	return 0;
}