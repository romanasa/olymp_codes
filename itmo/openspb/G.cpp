#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e6 + 7;
int dist[dd], p[dd];

int main() {
	int n, d;
	cin >> n >> d;
	
	fill(dist, dist + n + 1, (int)1e9);
	fill(p, p + n + 1, -1);
	
	queue<int> q;
	for (int i = 1; i < 10; i++) if (i != d) {
		if (dist[i] > 1) {
			dist[i] = 1;
			p[i] = i;
			q.push(i);
		}
	}
	
	while (q.size()) {
		int v = q.front();
		q.pop();
		for (int c = 0; c < 10; c++) if (c != d) {
			if (v + c <= n && dist[v + c] > dist[v] + 1) {
				dist[v + c] = dist[v] + 1;
				p[v + c] = c;
				q.push(v + c);
			}
		}
	}
	
	string ans;
	int i = n;
	while (i > 0) {
		//err("i = %d\n", i);
		ans += (char)(p[i] + '0');
		i -= p[i];
	}
	reverse(ans.begin(), ans.end());
	cout << ans << "\n";

	return 0;
}