#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    freopen("paradox.in", "r", stdin);
    freopen("paradox.out", "w", stdout);

    int n;
    cin >> n;

    map<string, int> dp;
    map<string, int> num;
    vector<int> p(n, -1);
    vector<string> Q(n);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;


        string A, B;
        A += s[0]; A += s[1]; A += s[2];
        B += s[4]; B += s[5]; B += s[6];

        if (!num.count(A)) num[A] = -1;
        if (!num.count(B)) num[B] = -1;

        Q[i] = B;

        if (dp[A] < dp[B] + 1) {
            dp[A] = dp[B] + 1;
            p[i] = num[B];
            num[A] = i;
        }
    }

    int ans = -1;
    string anss;
    for (auto c : dp) {
        if (c.second > ans) {
            ans = c.second;
            anss = c.first;
        }
    }


    cout << ans << "\n";
    cout << anss;
    for (int i = num[anss]; i != -1; i = p[i]) cout << "-" << Q[i];

    return 0;
}

