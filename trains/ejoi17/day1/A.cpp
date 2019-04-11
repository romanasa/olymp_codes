#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 1;
const int mod = (int)1e9 + 7;
int cnt[dd][57];

char let[52];
map<vector<int>, int> M;
set<char> S;
int num[127];

int main() {
	int n;
	cin >> n;
	string s;
	cin >> s;
	
	for (char c : s) S.insert(c);
	int ind = 0;
	for (auto c : S) num[c] = ind++;	
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < ind; j++) cnt[i + 1][j] = cnt[i][j];
		cnt[i + 1][num[s[i]]]++;
	}
	
	int ans = 0;
	for (int i = 0; i <= n; i++) {
		vector<int> cur(ind - 1);
		for (int j = 0; j + 1 < ind; j++) cur[j] = cnt[i][j + 1] - cnt[i][j];
			
		
		//err("i = %d, cur = ", i); for (int j =0; j < 10; j++) err("%d, ", cur[j]); err("\n");
	
		ans += M[cur];
		if (ans >= mod) ans -= mod;
		M[cur]++;
	}
	cout << ans << "\n";
	return 0;
}