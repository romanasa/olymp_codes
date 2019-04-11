#include <bits/stdc++.h>

using namespace std;

typedef __int128 ll;

#include "grader.h"
#ifdef HOME
    #include "lang.h"
#endif // HOME

const int n = 100;
const int dd = (int)1e5;

map<pair<ll, int>, int> M;
map<ll, pair<int, int> > Get;

ll geth(ll a, ll b, ll c, ll d) {
    return a * (ll)1e15 + b * (ll)1e10 + c * (ll)1e5 + d;
}

void excerpt(int *E) {
    vector<int> cnt(60);

    for (int i = 0; i + 3 < n; i++) {
        auto it = Get.find(geth(E[i], E[i + 1], E[i + 2], E[i + 3]));
        if (it != Get.end()) {
            cnt[it->second.second]++;
        }
    }

    int ind = 0;
    for (int i = 0; i < 60; i++) {
        if (cnt[i] > cnt[ind]) {
            ind = i;
        }
    }

    int lang = language(ind);

    for (int i = 0; i + 2 < n; i++) {
        int t = ++M[{ geth(E[i], E[i + 1], E[i + 2], E[i + 3]), lang }];

        if (t > Get[geth(E[i], E[i + 1], E[i + 2], E[i + 3])].first) {
            Get[geth(E[i], E[i + 1], E[i + 2], E[i + 3])] = { t, lang };
        }
    }
}
