#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int cnt[26];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    string s;
    cin >> s;
    for (char c : s) cnt[c - 'a']++;
    int uk = 0;
    for (int i = 0; i < 26; i++) if (cnt[i] > cnt[uk]) uk = i;
    cout << (char)('a' + uk);
    return 0;
}
