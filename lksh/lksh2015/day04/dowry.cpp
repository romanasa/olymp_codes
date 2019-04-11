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

#define TASK "dowry"

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

ll n, w[33], c[33];
ll l, r;

int solve() {
    cin >> n >> l >> r;
    forn(i, n)
        cin >> w[i] >> c[i];
    vector<tuple<ll, ll, ll> > first, second, answer;
    ll p1 = n / 2, p2 = n / 2 + n % 2;

    forn(msk, (1ll << p1)) {
        ll cw = 0, cc = 0;
        forn(i, p1)
            if (msk & (1 << i))
                cw += w[i], cc += c[i];
        first.pk(make_tuple( cw, cc, msk ));
    }

    forn(msk, (1ll << p2)) {
        ll cw = 0, cc = 0;
        forn(i, p2)
            if (msk & (1 << i))
                cw += w[i + p1], cc += c[i + p1];
        second.pk(make_tuple(cw, cc, msk));
    }

    sort(all(first));
    sort(all(second));

    ll st = 0, en = 0;
    set<pair<ll, ll> > s;
    
    for (ll i = first.size() - 1; i >= 0; i--) {
        while (en < second.size() && get<0>(first[i]) + get<0>(second[en]) <= r) {
            s.insert({ get<1>(second[en]), en });
            en++;
        }

        if (en < second.size() && get<0>(first[i]) + get<0>(second[en]) > r &&
            en > 0 && get<0>(first[i]) + get<0>(second[en - 1]) <= r && en > l) {
            auto it = s.find({ get<1>(second[en]), en });
            if (it != s.end())
                s.erase(it);
            en--;
        }


        while (st < second.size() && get<0>(first[i]) + get<0>(second[st]) < l) {
            auto it = s.find({ get<1>(second[st]), st });
            if (it != s.end())
                s.erase(it);
            st++;
        }

        if (s.size()) {
            auto it = s.rbegin();
            ll cost = it->first, ind = it->second;
            answer.pk(make_tuple(cost + get<1>(first[i]), get<2>(first[i]), get<2>(second[ind])));
        }
    }
    sort(all(answer));
    reverse(all(answer));
    if (!answer.size()) {
        cout << 0;
        return 0;
    }
    vector<ll> res;
    ll msk1 = get<1>(answer[0]), msk2 = get<2>(answer[0]);

    forn(i, p1)
        if (msk1 & (1ll << i))
            res.pk(i);
    forn(i, p2)
        if (msk2 & (1ll << i))
            res.pk(i + p1);
    cout << res.size() << "\n";
    for (ll x : res)
        cout << x + 1 << " ";
    return 0;
}