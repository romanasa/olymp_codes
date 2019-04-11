#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
    int n, m;
    cin >> n >> m;
    string s;
    for (int i = 0; i < n; i++) cin >> s;
    s += '.';
    int ans = 0;
    for (int i = 0; i < m; i++) ans += (s[i] == 'B' && s[i + 1] == '.');
    cout << ans << "\n";
	return 0;
}
