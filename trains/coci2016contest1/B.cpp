#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
int d[11][dd];
pair<int, int> p[11][dd], op[11][dd];

int main() {
	int n;
	cin >> n;
	
	vector<string> a(10);
	for (int i = 0; i < 10; i++) cin >> a[i];
	
	queue<pair<int, int> > q;
	
	for (int i = 0; i < 10; i++)
		fill(d[i], d[i] + n + 1, (int)1e9);
	
	q.push({ 9, 0 });
	d[9][0] = 0;
	
	
	for (int j = 0; j < n; j++) for (int i = 0; i < 10; i++) {
		
		if (d[i][j] == (int)1e9) continue;
		
		int ni = max(i - 1, 0), nj = j + 1;
   		if (nj < n && a[ni][nj] != 'X' && d[ni][nj] > d[i][j] + 1) {
   			d[ni][nj] = d[i][j] + 1;
   			p[ni][nj] = { i, j };
   			op[ni][nj] = { j, 1 };
   		}
   		
   		ni = min(i + 1, 9), nj = j + 1;
   		if (nj < n && a[ni][nj] != 'X' && d[ni][nj] > d[i][j]) {
   			d[ni][nj] = d[i][j];
   			p[ni][nj] = { i, j };
   			op[ni][nj] = { -1, -1 };
   		}
	}
	
	int cur = (int)1e9, ind = -1;
	
	for (int i = 0; i < 10; i++) {
		if (d[i][n - 1] < cur) {
			cur = d[i][n - 1];
			ind = i;
		}
	}

	vector<pair<int, int> > ans;
	
	int i = ind, j = n - 1;
	while (j) {
		if (op[i][j].first != -1) ans.push_back(op[i][j]);
		int ni = p[i][j].first, nj = p[i][j].second;
		i = ni, j = nj;
	}
	
	reverse(ans.begin(), ans.end()); 
	
	auto t = ans;
	ans.clear();
	
	for (auto c : t) {
		if (ans.size() && ans.back().first + ans.back().second == c.first) ans.back().second += c.second;
		else ans.push_back(c);
	}
	
	cout << ans.size() << "\n";
	for (auto c : ans) cout << c.first << " " << c.second << "\n";
	
	return 0;
}