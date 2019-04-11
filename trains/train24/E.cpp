#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define TASK "numbers"

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN

    string s;
    cin >> s;

    string a, b;
    a += s[0]; a += s[4]; a += s[5];
    b += s[1]; b += s[2]; b += s[3];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<string> ans;

    do {
        do {
            string cur;
            cur += a[0];
            cur += b;
            cur += a[1];
            cur += a[2];
            ans.push_back(cur);
        } while (next_permutation(b.begin(), b.end()));

    } while (next_permutation(a.begin(), a.end()));

    cout << ans.size() << "\n";
    for (auto c : ans) cout << c << "\n";
    return 0;
}

