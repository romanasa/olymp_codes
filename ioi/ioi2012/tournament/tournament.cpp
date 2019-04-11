#include "grader.h"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;

struct seg {
    vector<vector<int> > T;

    void build(int v, int tl, int tr, vector<pair<int, int> > &A) {
        T[v].resize(tr - tl + 1);
        if (tl == tr) T[v][0] = A[tl].second;
        else {
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm, A);
            build(v * 2 + 1, tm + 1, tr, A);
            merge(T[v * 2].begin(), T[v * 2].end(), T[v * 2 + 1].begin(), T[v * 2 + 1].end(), T[v].begin());
        }
    }

    int get(int v, int tl, int tr, int l, int r, int x, int y) {
        if (tl == l && tr == r) return upper_bound(T[v].begin(), T[v].end(), y) - lower_bound(T[v].begin(), T[v].end(), x);
        int tm = (tl + tr) / 2;
        if (r <= tm) return get(v * 2, tl, tm, l, r, x, y);
        if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r, x, y);
        return get(v * 2 , tl, tm, l, tm, x, y) + get(v * 2 + 1, tm + 1, tr, tm + 1, r, x, y);
    }

    void resize(vector<pair<int, int> > &A) {
        T.resize((int)4 * (int)A.size() + 7);
        build(1, 0, (int)A.size() - 1, A);
    }
} F;

int get(int i, int l, int r, vector<pair<int, int> > &T) {
    int L = lower_bound(T.begin(), T.end(), make_pair(l, -1)) - T.begin();
    int R = upper_bound(T.begin(), T.end(), make_pair(i, (int)1e9)) - T.begin() - 1;

    if (L > R) return 0;
    return F.get(1, 0, (int)T.size() - 1, L, R, i, r);
}

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E) {
    vector<pair<int, int> > T;
    tree<pair<int, int>, null_type, less<pair<int, int> >, rb_tree_tag, tree_order_statistics_node_update> cur;

    for (int i = 0; i < N; i++) cur.insert({ i, i });

    for (int it = 0; it < C; it++) {
        auto cc = cur.find_by_order(S[it]);
        int l = cc->first;
        int r = cc->second;

        vector<pair<int, int> > f;

        for (int x = S[it]; x <= E[it]; x++) {
            r = max(r, cc->second);
            f.push_back(*cc);
            ++cc;
        }
        for (auto c : f) cur.erase(c);
        cur.insert({ l, r });
        T.push_back({ l, r });
    }

    sort(T.begin(), T.end());
    F.resize(T);

    set<int> positions;
    positions.insert(-1);
    for (int i = 0; i + 1 < N; i++) if (K[i] > R)
        positions.insert(i);
    positions.insert(N - 1);

    int ans = -1;
    int pos = -1;

    for (int i = 0; i < N; i++) {
        int l = *(--positions.lower_bound(i));
        int r = *(positions.lower_bound(i));
        int cur = get(i, l + 1, r, T);
        if (cur > ans) {
            ans = cur;
            pos = i;
        }
    }
    return pos;
}
