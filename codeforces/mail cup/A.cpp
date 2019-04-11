#include <bits/stdc++.h>

using namespace std;

int used[12345];
int a[12345], b[12345];

int n, s;
	
void dfs(int v) {
	used[v] = 1;
	if (v == s) return;
	
	for (int i = v + 1; i < n; i++) if (a[v] && a[i] && !used[i])
		dfs(i);
		
	for (int i = v - 1; i >= 0; i--) if (b[v] && b[i] && !used[i])
		dfs(i);
}

int main() {
	cin >> n >> s;
	s--;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	dfs(0);
	puts(used[s] ? "YES" : "NO");
	
	return 0;
}