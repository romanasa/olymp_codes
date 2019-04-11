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

#define TASK "dancing-forever"

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
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    //freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

int n, c, s;

int w[21], curv;

int solve() {
    cin >> n >> c >> s;
    cout << "accept" << endl;
    curv = s;

    while (curv) {
        cin >> s;

        if (s > curv)
            cout << "decline" << endl;
        if (s < curv) {
            curv = s;
            cout << "accept" << endl;
        }
    }

    int g = 0;
    while (g < n) {
        cin >> s;

        if (s < curv)
            cout << "decline" << endl;
        if (s > curv) {
            w[g++] = s - curv;
            curv = s;
            cout << "accept" << endl;
        }
    }

    int ans = 0, mska;
    forn(msk, 1 << n) {
        int cw = 0;
        forn(i, n)
            if (msk & (1 << i))
                cw += w[i];
        if (cw <= c && cw > ans)
            ans = cw, mska = msk;
    }

    //cout << ans;
    if (curv == ans) {
        cin >> s;
        curv = s;
        cout << "accept" << endl;
        while (1) {
            cin >> s;
            if (s == ans) {
                cout << "stop" << endl;
                return 0;
            }
            else
                cout << "decline\n";
        }
    }

    while (curv != ans) {
        cin >> s;
        if (s == ans)
            break;

        bool ok = (curv > s);

        if (ok) {
            bool ok1 = false;
            for (int i = 0; i < n && !ok1; i++) {
                if (!(mska & (1 << i)))
                    if (w[i] == curv - s) {
                        cout << "accept" << endl;
                        curv = s;
                        mska |= (1 << i);
                        ok1 = true;
                    }
            }
            if (!ok1) {
                cout << "decline" << endl;
            }
        }
        else {
            cout << "decline" << endl;
        }
    }
    cout << "stop" << endl;
    return 0;
}