//
// Created by spb1 on 10/17/2018.
//

#include <bits/stdc++.h>

#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct pt {
    ll x, y;

    pt() {}

    pt(ll x, ll y) : x(x), y(y) {}

    pt(pt A, pt B) : x(B.x - A.x), y(B.y - A.y) {}

    ll operator%(pt b) const {
        return x * b.y - y * b.x;
    }

    ll operator*(pt b) const {
        return x * b.x + y * b.y;
    }
    
    bool operator < (const pt &other) const {
        if (y == 0 && other.y == 0) {
            if (x < 0 && other.x > 0) return 1;
            return 0;
        }
        if (y <= 0 && other.y > 0) return 1;
        if (y > 0 && other.y <= 0) return 0;
        return (*this % other) > 0;
    }
};

struct ev {
    pt n;
    int i, j;

    bool operator<(const ev &other) const {
        if (n.y == 0 && other.n.y == 0) {
            if (n.x < 0 && other.n.x > 0) return 1;
            return 0;
        }
        if (n.y <= 0 && other.n.y > 0) return 1;
        if (n.y > 0 && other.n.y <= 0) return 0;
        return (n % other.n) > 0;
    }

    bool operator==(const ev &other) const {
        return !(*this < other) && !(other < *this);
    }
};

void upd(int pos, vector<ll> &ans, vector<int> &Px, vector<int> &Py) {
    ll sx = Px[pos];
    ll sy = Py[pos];
    ans[pos] = max(ans[pos], sx * sx + sy * sy);
}

int solve() {

    int n;
    cin >> n;

    vector<pt> P(n);
    for (int i = 0; i < n; i++) {
        cin >> P[i].x >> P[i].y;
    }
    
    sort(P.begin(), P.end());

    pt st(1, (int) 3e6);

    vector<ev> E;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (i != j) {

                pt cur(P[i], P[j]);
                if (cur.x != 0 || cur.y != 0) {
                    E.push_back({cur, i, j});
                } else {
                    if (i < j) {
                        //E.push_back({pt(-P[i].y, P[i].x), i, j});
                    } else {
                        //E.push_back({pt(P[i].y, -P[i].x), i, j});
                    }
                }
            }
    }

    vector<int> T(n), pos(n);
    for (int i = 0; i < n; i++) T[i] = i;

    sort(T.begin(), T.end(), [&](int a, int b) {
        return make_pair(P[a] * st, -a) > make_pair(P[b] * st, -b);
    });

    for (int i = 0; i < n; i++) {
        pos[T[i]] = i;
    }

    vector<int> Px(n), Py(n);
    vector<ll> ans(n);

    for (int i = 0; i < n; i++) {
        if (i) Px[i] += Px[i - 1], Py[i] += Py[i - 1];
        Px[i] += P[T[i]].x;
        Py[i] += P[T[i]].y;
        upd(i, ans, Px, Py);
    }

    sort(E.begin(), E.end());

    int i = 0;

        	err("T = ");
        	for (auto c : T) err("(%d, %I64d), ", c, P[c] * st); err("\n");
    while (i < (int) E.size()) {


    	st.x = E[i].n.y;
    	st.y = -E[i].n.x;
    	
    	int t1 = (int)1e9 / (st.x ? abs(st.x) : 1);
    	int t2 = (int)1e9 / (st.y ? abs(st.y) : 1);
    	
    	st.x *= min(t1, t2);
    	st.y *= min(t1, t2);
    	
    	if (st.x < 0) st.y--;
    	else if (st.x == 0) st.x += (st.y > 0 ? -1 : (st.y < 0 ? 1 : 0));
    	else st.y++;
    	

        sort(T.begin(), T.end(), [&](int a, int b) {
            return make_pair(P[a] * st, -a) > make_pair(P[b] * st, -b);
        });

        for (int i = 0; i < n; i++) {
            Px[i] = P[T[i]].x;
            Py[i] = P[T[i]].y;
            if (i) Px[i] += Px[i - 1], Py[i] += Py[i - 1];
            upd(i, ans, Px, Py);
        }
        
        
        err("n = (%I64d, %I64d), T = ", st.x, st.y);
        for (auto c : T) err("(%d, %I64d), ", c, P[c] * st); err("\n");

        vector<ev> cur;
        int j = i;
        while (j < (int) E.size() && E[i] == E[j]) {
            cur.push_back(E[j]);
            j++;
        }
        i = j;
        continue;


        //int mn = n + 1;
        //int mx = -1;

        sort(cur.begin(), cur.end(), [&](ev a, ev b) {

            //return make_pair(min(a.i, a.j), max(a.i, a.j)) < make_pair(min(b.i, b.j), max(b.i, b.j));

            int t1 = min(pos[a.i], pos[a.j]);
            int t2 = max(pos[a.i], pos[a.j]);

            int t3 = min(pos[b.i], pos[b.j]);
            int t4 = max(pos[b.i], pos[b.j]);

            //if (t2 - t1 != t4 - t3) return t2 - t1 < t4 - t3;
            return make_pair(t1, t2) < make_pair(t3, t4);
        });

        err("sz = %d\n", (int) cur.size());
        for (auto c : cur) err("(%d, %d)\n", c.i, c.j); err("\n");


        set<pair<int, int> > cc;
        vector<int> pp;

        for (auto c : cur) {

            int pi = pos[c.i];
            int pj = pos[c.j];

            //assert(pi + 1 == pj);



            //cc.insert({ pj, c.j });
            pp.push_back(c.i);
            pp.push_back(c.j);

            swap(pos[c.i], pos[c.j]);
            swap(T[pos[c.i]], T[pos[c.j]]);
        }

        for (auto x : pp) {
            int i = x;
            int pi = pos[i];
            cc.insert({pi, i});
        }

        for (auto c : cc) {
            int pi = c.first;
            int i = c.second;

            Px[pi] = P[i].x;
            if (pi) Px[pi] += Px[pi - 1];
            Py[pi] = P[i].y;
            if (pi) Py[pi] += Py[pi - 1];

            upd(pi, ans, Px, Py);
        }
    }

    cout.precision(20);
    cout << fixed;
    for (int i = 0; i < n; i++) cout << sqrt(ans[i]) << "\n";
    return 0;
}

int main() {
#ifdef SIR
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}