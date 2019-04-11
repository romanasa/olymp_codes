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
#include <cstring>
#include <sstream>
#include <numeric>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "freedom"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll inf = (ll)2e9 + 1;
const ll linf = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int dd = 2e6 + 7;

int go[dd][31];
int len[dd], suf[dd];

int last = 0, nv = 1;

int clone(int v) {
    int cur = nv++;

    forn(i, 31)
        go[cur][i] = go[v][i];

    return cur;
}

void add(int c) {
    int nlast = nv++;

    len[nlast] = len[last] + 1;

    int p = last;
    while (p != -1 && go[p][c] == -1) {
        go[p][c] = nlast;
        p = suf[p];
    }

    if (p == -1) {
        suf[nlast] = 0;
    } else {
        int q = go[p][c];

        if (len[q] == len[p] + 1)
            suf[nlast] = q;
        else {
            int r = clone(q);

            len[r] = len[p] + 1;

            suf[r] = suf[q], suf[q] = r;
            suf[nlast] = r;

            while (p != -1 && go[p][c] == q) {
                go[p][c] = r;
                p = suf[p];
            }
        }
    }
    last = nlast;
}

int N;

void upd(int &l1, int &r1, int l2, int r2) {
    if (l2 > r2)
        return;

    int t1 = r1 - l1 + 1 - max(l1, N - r1 - 1);
    int t2 = r2 - l2 + 1 - max(l2, N - r2 - 1);

    if (t1 < t2) 
        l1 = l2, r1 = r2;
    if (t1 == t2 && mp(l2, r2) < mp(l1, r1))
        l1 = l2, r1 = r2;
}
	
int solve() {
    forn(i, dd) {
        forn(j, 31) {
            go[i][j] = -1;
        }
    }
    suf[0] = -1;

    string s, t;
    cin >> s >> t;

    N = s.size();

    for (auto c : t)
        add(c - 'a');

    int cur = 0;
    int l = 0;

    int lmax = -1, rmax = -1;
    forn(i, s.size()) {
        char c = s[i];
        while (cur && go[cur][c - 'a'] == -1) {
            cur = suf[cur];
            l = len[cur];
        }
        if (go[cur][c - 'a'] != -1) {
            cur = go[cur][c - 'a'];
            l++;
        }

        upd(lmax, rmax, i - l + 1, i);
    }

    cout << lmax << " " << rmax;
    return 0;
	}