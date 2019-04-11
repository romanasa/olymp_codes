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

    bool operator < (const ev &other) const {
        return n < other.n;
    }

    bool operator == (const ev &other) const {
        return !(*this < other) && !(other < *this);
    }
};

void upd(int pos, int val, vector<int> &T) {
	for (int i = pos + 1; i < (int)T.size(); i += (i&-i)) T[i] += val;
}

int get(int pos, vector<int> &T) {
	int res = 0;
	for (int i = pos + 1; i > 0; i -= (i&-i)) res += T[i];
	return res;
}

void upd(int pos, vector<ll> &ans, vector<int> &Px, vector<int> &Py) {
    ll sx = get(pos, Px);
    ll sy = get(pos, Py);
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
    
    pt st(1, (int) 2e6);
    vector<ev> E;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (i != j) {
            pt cur(P[i], P[j]);
            if (cur.x != 0 || cur.y != 0) E.push_back({cur, j, i});
        }
    }

    vector<int> T(n), pos(n);
    for (int i = 0; i < n; i++) T[i] = i;

    sort(T.begin(), T.end(), [&](int a, int b) {
        return make_pair(P[a] * st, -a) > make_pair(P[b] * st, -b);
    });

    for (int i = 0; i < n; i++) pos[T[i]] = i;

    vector<int> Px(n + 2), Py(n + 2);
    vector<ll> ans(n);

    for (int i = 0; i < n; i++) {
        upd(i, P[T[i]].x, Px);
        upd(i, P[T[i]].y, Py);
        upd(i, ans, Px, Py);
    }

    sort(E.begin(), E.end());

    for (int i = 0; i < (int)E.size(); ) {
    
    	vector<int> cT, cP;
    	int j = i;
    	while (j < (int)E.size() && E[i] == E[j]) {
    		cT.push_back(E[j].i), cT.push_back(E[j].j);
    		cP.push_back(pos[E[j].i]), cP.push_back(pos[E[j].j]);
    		j++;
    	}
    	i = j;
    	
    	sort(cT.begin(), cT.end());
    	cT.resize(unique(cT.begin(), cT.end()) - cT.begin());
    	sort(cP.begin(), cP.end());
    	cP.resize(unique(cP.begin(), cP.end()) - cP.begin());
    	
    	st.x = E[i - 1].n.y;
    	st.y = -E[i - 1].n.x;
    	
    	int t1 = (int)1e9 / (st.x ? abs(st.x) : 1);
    	int t2 = (int)1e9 / (st.y ? abs(st.y) : 1);
    	
    	st.x *= min(t1, t2);
    	st.y *= min(t1, t2);
    	
    	if (st.x < 0) st.y--;
    	else if (st.x == 0) st.x += (st.y > 0 ? -1 : (st.y < 0 ? 1 : 0));
    	else st.y++;
    	
        sort(cT.begin(), cT.end(), [&](int a, int b) {
            return make_pair(P[a] * st, -a) > make_pair(P[b] * st, -b);
        });
    	
    
        for (int ii = 0; ii < (int)cT.size(); ii++) {
       		
        	int ind = cT[ii];
        	int pi = pos[ind];
            int pj = cP[ii];
           
            upd(pi, -P[ind].x, Px);
            upd(pi, -P[ind].y, Py);
            
            upd(pj, P[ind].x, Px);
            upd(pj, P[ind].y, Py);
            
            pos[ind] = pj;
            T[pj] = ind;
        }
        for (auto c : cP) upd(c, ans, Px, Py);
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