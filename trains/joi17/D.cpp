#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <set>
#include <queue>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;
const int sz = 507;
	
int h, w;
ll a, b, c;
int x[dd], y[dd];
int dist[sz][sz];
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

bool ok(int i, int j) {
	return i >= 0 && i < h && j >= 0 && j < w;
}

vector<vector<pair<int, ll>>> E;

int main() {
	scanf("%d %d", &h, &w);	
	scanf("%I64d %I64d %I64d", &a, &b, &c);

	h++, w++;
	
	E.resize(3 * h * w);
	
	int n;
	scanf("%d", &n);

	for (int i = 0; i < h; i++) fill(dist[i], dist[i] + w, (int)1e9);

	queue<pair<int, int>> q;	
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &x[i], &y[i]);
		dist[x[i]][y[i]] = 0;
		q.push({ x[i], y[i] });
	}
	
	while (q.size()) {
		int i = q.front().first, j = q.front().second;
		q.pop();
		for (int gg = 0; gg < 4; gg++) {
			int ni = i + dx[gg], nj = j + dy[gg];
			if (ok(ni, nj) && dist[ni][nj] > dist[i][j] + 1) {
				dist[ni][nj] = dist[i][j] + 1;
				q.push({ ni, nj });
			}
		}
	}
	/*
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			err("%d%c", dist[i][j], " \n"[j == w - 1]);
		}
	}
	*/
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			
			int v0 = i * w + j;
			for (int gg = 0; gg < 4; gg++) {
				int ni = i + dx[gg], nj = j + dy[gg];
				int to = ni * w + nj;
				if (ok(ni, nj)) E[v0].push_back({ to, c });
			}
			
			int v1 = h * w + i * w + j;
			int to1 = h * w + i * w + j + 1;
			if (j + 1 < w) E[v1].push_back({ to1, a });
			if (j > 0) E[v1].push_back({ to1 - 2, a });
			
			int v2 = 2 * h * w + i * w + j;
			int to2 = 2 * h * w + (i + 1) * w + j;
			if (i + 1 < h) E[v2].push_back({ to2, a });
			if (i > 0) E[v2].push_back({ to2 - 2 * w, a });
			
			E[v0].push_back({ v1, b });
			E[v0].push_back({ v2, b });
			
			E[v1].push_back({ v0, c * dist[i][j]});
			E[v2].push_back({ v0, c * dist[i][j]});
		}
	}
	
	vector<ll> d(3 * h * w, (ll)1e18);
	
	priority_queue<pair<ll, int>> S;
	
	int st = x[0] * w + y[0];
	d[st] = 0;
	
	S.push({ -d[st], st });
	
	while (S.size()) {
		int v = S.top().second;
		ll ds = -S.top().first;
		
		S.pop();
		
		if (ds != d[v]) continue;
		
		for (auto c : E[v]) {
			if (d[c.first] > d[v] + c.second) {
				d[c.first] = d[v] + c.second;
				S.push({ -d[c.first], c.first });
			}
		}
	}
	
	int fn = x[n - 1] * w + y[n - 1];
	printf("%I64d\n", d[fn]);
	return 0;
}