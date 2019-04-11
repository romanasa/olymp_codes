//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,popcnt,tune=native")
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double ld;
#define sz(x) ((long long ll)(x).size())
#define pb push_back
#define mp make_pair
#define pii pair <ll, ll>
#define vpii vector <pair <ll, ll> >;
//#define int long long
#define forn(i, n) for (int i = 0; i < n; ++i)
#define x real
#define y imag
const int N = 1e5 + 5;
vector <int> a, b;

struct suf_arr {
    int p[N], p2[N];
    int len[N];
    void build(int n, vector <int> &s) {
        static int num[N + 1], col[N];
        int ma = n, cc = 0;
        for (int i = 0; i < n; ++i)
            ma = max(ma, int(s[i]));
        for (int i = 0; i < n; ++i) {
            col[i] = s[i];
            p[i] = i;
        }
        for (int k2 = 1; k2 / 2 < n && cc != n - 1; k2 *= 2) {
            int k = k2 / 2;
            for (int i = 0; i <= ma; ++i)
                num[i] = 0;
            for (int i = 0; i < n; ++i)
                ++num[col[i] + 1];
            for (int i = 0; i < ma; ++i)
                num[i + 1] += num[i];
            for (int i = 0; i < n; ++i)
                p2[num[col[(p[i] - k + n) % n]]++] = (p[i] - k + n) % n;
                cc = 0;
            for (int i = 0; i < n; ++i) {
                cc += (i && (col[p2[i]] != col[p2[i - 1]] || col[(p2[i] + k) % n] != col[(p2[i - 1] + k) % n]));
                num[p2[i]] = cc;
            }
            for (int i = 0; i < n; ++i) {
                p[i] = p2[i];
                col[i] = num[i];
            }
        }
        for (int i = 0; i < n; ++i)
            p2[p[i]] = i;
    }
    void get_lcp(int n, vector <int> &s) {
        int lcp = 0;
        for (int i = 0; i < n; ++i) {
            int j = p2[i];
            --lcp;
            if (lcp < 0)
                lcp = 0;
            if (j != n - 1)
                while (lcp < n && s[(p[j] + lcp) % n] == s[(p[j + 1] + lcp) % n])
                    lcp++;
            len[j] = lcp;
        }
    }
};


void solve(int n) {
    //cout << "start" << endl;
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ++a[i];
    }
    suf_arr now;
    //cout <<" A" << endl;
    b = a;
    for (int i = 0; i < n; ++i)
        b.pb(a[i]);
    b.pb(0);
    int m = sz(b);
    now.build(m, b);
    ll cnt = 0;
    now.get_lcp(m, b);
    for (int i = 0; i < m; ++i) {
        if (now.p[i] >= n)
            continue;
        cnt += min(n, now.len[i]);
        cout << now.p[i] << " = " << now.len[i] << "\n";
    }
    cout << cnt << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    while (
    cin >> n) {
        //cout << n << endl;
        solve(n);
    }
    return 0;
}