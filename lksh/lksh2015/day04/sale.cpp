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

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (int i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "sale"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

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

struct pr {
    ll a, b, c, ind;
    bool operator <(pr f) const {
        return a < f.a;
    }
};

const int MAXW = 1e5;
int dp[100007];

int solve() {
    int n, m;
    cin >> n;

    vector<pr> req(n);
    forn(i, n)
        cin >> req[i].c >> req[i].a >> req[i].b;

    sort(all(req));
    
    cin >> m;
    vector<pr> ques(m);
    vector<string> ans(m);
    forn(i, m) {
        int m, j, k;
        cin >> m >> j >> k;
        ques[i].c = j, ques[i].a = m, ques[i].b = m + k;
        ques[i].ind = i;
    }
    
    sort(all(ques));

    forn(i, 1e5 + 7)
        dp[i] = -INF;
    dp[0] = INF;

    int i = 0, j = 0;
    while (i < req.size() || j < ques.size()) {
        if (j == ques.size() || i < req.size() && req[i].a <= ques[j].a) {
            int b = req[i].b, c = req[i].c;
            for (int w = MAXW - c; w >= 0; w--)
                dp[w + c] = max(dp[w + c], min(dp[w], b));
            i++;
        }
        else {
            int c = ques[j].c, b = ques[j].b;
            if (dp[c] > b)
                ans[ques[j].ind] = "YES";
            else
                ans[ques[j].ind] = "NO";
            j++;
        }
    }

    for (string s: ans)
        cout << s << "\n";
    return 0;
}
