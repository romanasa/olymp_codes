#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

bitset<45> cur, res;

vector<pair<pair<int, int>, char> > op, cans;
int ans = (int)1e9;

int n;
	
void dfs() {
	int t = (cur & res).count();
	
	if (t == n) {
		if ((int)op.size() < ans) {
			ans = (int)op.size();
			cans = op;
		}
		return;
	}
	
	if ((int)op.size() + (n - t) >= ans) return;
	
	for (int x = 1; x <= 42; x++) if (cur[x]) {
		for (int g = 1; (x << g) <= 42; g++) if (!cur[x << g]) {
			op.push_back({ { x, g }, '>' });
			cur[x << g] = 1;
			dfs();
			cur[x << g] = 0;
			op.pop_back();
		}
	}
	
	for (int x = 1; x <= 42; x++) if (cur[x]) {
		for (int y = 1; y < x; y++) if (cur[y]) {
			if (x + y <= 42 && !cur[x + y]) {
				op.push_back({ { x, y }, '+' });
				cur[x + y] = 1;
				dfs();
				cur[x + y] = 0;
				op.pop_back();
			}
			if (!cur[x - y]) {
				op.push_back({ { x, y }, '-' });
				cur[x - y] = 1;
				dfs();
				cur[x - y] = 0;
				op.pop_back();
			}
		}
	}
	
}

int main() {
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		int t;
		scanf("%d", &t);
		res[t] = 1;
	}
	
	cur[1] = 1;
	dfs();
	
	printf("%d\n", (int)cans.size());
	
	for (auto c : cans) {
		if (c.second == '>') printf("%d<<%d\n", c.first.first, c.first.second);
		else printf("%d%c%d\n", c.first.first, c.second, c.first.second);
	}

	return 0;
}