#include <bits/stdc++.h>

using namespace std;

map<int, vector<int> > m;

int main()
{
    freopen("queries.in", "r", stdin);
    freopen("queries.out", "w", stdout);
    int n, q;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        m[x].push_back(i);
    }

    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, r--;
        auto &cur = m[x];

        int ind = lower_bound(cur.begin(), cur.end(), l) - cur.begin();
        if (ind < (int)cur.size() && cur[ind] <= r) putchar('1');
        else putchar('0');
    }
    return 0;
}
