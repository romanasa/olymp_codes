#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    string s;
    cin >> s;
    int n = (int)s.size();

    int ans = 0;
    for (int i = 0; i < n; i += 3) {
        ans += (s[i] != 'P');
        ans += (s[i + 1] != 'E');
        ans += (s[i + 2] != 'R');
    }
    cout << ans << "\n";
    return 0;
}

