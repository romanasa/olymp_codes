#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:66777216")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (ll i = 0; i < (ll)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "tandems"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)9e18 + 7;
const ll MM = (ll)1e9 + 7;

int solve();

int main()
{
#ifdef _DEBUG
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

vector<int> Z(string &s){
    vector<int> Z(s.size());
    for (int l = 0, r = 0, i = 1; i < s.size(); i++){
        if (i <= r)
            Z[i] = min(r - i + 1, Z[i - l]);
        while (i + Z[i] < s.size() && s[Z[i]] == s[Z[i] + i])
            Z[i]++;
        if (i + Z[i] - 1 > r)
            l = i, r = i + Z[i] - 1;
    }
    return Z;
}

ll res = 0;

void sol(string a, string b){
    string s = b + "#" + a;
    reverse(all(a));

    auto G = Z(s), H = Z(a);

    forn(i, a.size()) {
        int k1 = 0, k2 = 0, len = a.size() - i;
        if (i)
            k1 = H[a.size() - i];
        k2 = G[i + b.size() + 1];

        if (k1 >= len)
            k1 = len - 1;
        
        res += max(k1 + k2 - len + 1, 0);
    }
}

void eq(string a, string b){
    string s = b + "#" + a;
    auto G = Z(s);
    int del = 0;
    forn(i, a.size()){
        if (G[b.size() + i + 1] + i >= a.size())
            del++;
    }
    res -= del;
}

string S;

void go(string s) {
    int n = s.size();
    
    if (n == 1)
        return;

    int m = n / 2;

    string a, b;
    
    forn(i, m)
        a.pk(s[i]);

    fornn(i, m, s.size())
        b.pk(s[i]);

    sol(a, b);
    eq(a, b);
    
    reverse(all(a)), reverse(all(b));

    sol(b, a);

    reverse(all(a)), reverse(all(b));

    go(a);
    go(b);
}

int solve() {
    while (cin >> S){
        if (S[0] != '0'){
            res = 0;
            go(S);
            cout << res << '\n';
        }
        else
            break;
    }
    return 0;
}