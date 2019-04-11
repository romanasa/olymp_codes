#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long double ld;
#define X first
#define Y second
#define pb push_back
 
ll n, s, a[100005], sum[43][2], kol[43];
vector<pair<ll, string>> s1, s2;
 
void dfs1(ll len, ll summ, string out) {
    if (len == 20) {
        // s1[summ] = out;
        s1.pb({summ, out});
        return;
    }
    dfs1(len + 1, summ + sum[len][0], out + '0');
    dfs1(len + 1, summ + sum[len][1], out + '1');
}
 
void dfs2(ll len, ll summ, string out) {
    if (len == 40) {
        // s2[summ] = out;
        s2.pb({summ, out});
        return;
    }
    dfs2(len + 1, summ + sum[len][0], out + '0');
    dfs2(len + 1, summ + sum[len][1], out + '1');
}
 
int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> s;
    for (ll i = 1; i <= n; ++i) {
        cin >> a[i];
        for (ll j = 0; j <= 41; ++j) {
            if ((1LL << j) & a[i]) kol[j]++;
        }
    }
    for (ll i = 0; i <= 41; ++i) {
        sum[i][0] = kol[i] * (1LL << i);
        sum[i][1] = (n - kol[i]) * (1LL << i);
    }
    dfs1(0, 0, "");
    dfs2(21, 0, "");
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    ll uk = s2.size() - 1;
    for (ll i = 0; i < s1.size(); ++i) {
        while(uk > 0 && s1[i].X + s2[uk].X > s) --uk;
        if (s1[i].X + s2[uk].X == s) {
            ll ttr = 0;
            for (ll j = 0; j < s1[i].Y.size(); ++j) {
                if (s1[i].Y[j] == '1') ttr += (1LL << j);
            }
            string art = s2[uk].Y;
            for (ll j = 0; j < art.size(); ++j) {
                if (art[j] == '1') ttr += (1LL << (j + 21));
            }
            cout << ttr << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}
