#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)2e5 + 7;
const int MAXMEM = (int)1e8;
char MEM[MAXMEM];
int mpos;
 
inline void* operator new(size_t n) {
    char *res = MEM + mpos;
    mpos += n;
    return (void*)res;
}
 
inline void operator delete(void*) {}
 
struct ev {
    int x, y, e, s;
    bool operator < (const ev &b) const {
        return (y == b.y ? x < b.x : y > b.y);
    }
};
 
struct rec {
    int tp, y, ind;
};
 
int ADD = 50000 + 1;
const int maxX = (int)1e5 + 1234;
/*
struct node {
    deque<int> q;
     
    void push(int x) {
        while (q.size() && q.back() < x) q.pop_back();
        q.push_back(x);
    }
     
    void pop(int x) {
        if (q.size() && q.front() == x) q.pop_front();
    }
    int get() {
        return q.size() ? q.front() : -(int)1e9;
    }
};*/
 
struct node {
    multiset<ll> S;
    void push(ll x) { S.insert(x); }
    void pop(ll x) { S.erase(S.find(x)); }
    ll get() { return S.size() ? *S.rbegin() : -(ll)1e18; };
};
 
struct SegmentTree {
    node T[4 * maxX + 7];
     
    void add(int v, int tl, int tr, int l, int r, ll val) {
        if (tl == l && tr == r) {
            T[v].push(val);
            return;
        }
        int tm = (tl + tr) / 2;
        if (r <= tm) add(v * 2, tl, tm, l, r, val);
        else if (l > tm) add(v * 2 + 1, tm + 1, tr, l, r, val);
        else add(v * 2, tl, tm, l, tm, val), add(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
         
    }
     
    void del(int v, int tl, int tr, int l, int r, ll val) {
        if (tl == l && tr == r) {
            T[v].pop(val);
            return;
        }
         
        int tm = (tl + tr) / 2;
        if (r <= tm) del(v * 2, tl, tm, l, r, val);
        else if (l > tm) del(v * 2 + 1, tm + 1, tr, l, r, val);
        else del(v * 2, tl, tm, l, tm, val), del(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
    }
     
    ll get(int v, int tl, int tr, int pos) {
        if (tl == tr) return T[v].get();
        int tm = (tl + tr) / 2;
         
        ll cur = T[v].get(); 
         
        if (pos <= tm) cur = max(cur, get(v * 2, tl, tm, pos));
        else cur = max(cur, get(v * 2 + 1, tm + 1, tr, pos));
        return cur;
    }
} T;
 
ll get(int x) {
    x += ADD;
    //err("get(%d) = %I64d\n", x - ADD, T.get(1, 0, maxX, x));
     
    return T.get(1, 0, maxX, x);
}
 
void add(int l, int r, ll x) {
    //err("add (%d, %d), %I64d\n", l, r, x);
    l += ADD, r += ADD;
    l = max(l, 0);
    r = min(r, maxX);
     
    T.add(1, 0, maxX, l, r, x);
}
 
void del(int l, int r, ll x) {
    //err("del (%d, %d), %I64d\n", l, r, x);
    l += ADD, r += ADD;
     
    l = max(l, 0);
    r = min(r, maxX);
     
    T.del(1, 0, maxX, l, r, x);
}
 
int main() {
    int n, h;
    cin >> n >> h;
     
    vector<ev> A(n);
    for (int i = 0; i < n; i++) cin >> A[i].x >> A[i].y >> A[i].s >> A[i].e;
    //sort(A.begin(), A.end());
     
    vector<rec> E;
     
    for (int i = 0; i < n; i++) {
        E.push_back({ 0, A[i].y, i });
        E.push_back({ 1, A[i].y - A[i].e, i });
    }
     
    sort(E.begin(), E.end(), [&A](rec a, rec b) { 
        //if (a.y == b.y && a.tp == b.tp) return a.ind > b.ind;
        return make_pair(-a.y, a.tp) < make_pair(-b.y, b.tp); 
    });
     
    vector<ll> dp(n);
     
    for (int i = 0; i < (int)E.size(); i++) {
     
        auto c = E[i];
        if (c.tp == 0) {
         
            vector<rec> cur;
            int j = i;
            while (j < (int)E.size() && E[i].tp == E[j].tp && E[i].y == E[j].y) {
                cur.push_back(E[j]);
                j++;
            }
            
            sort(cur.begin(), cur.end(), [&](rec a, rec b) { return A[a.ind].x < A[b.ind].x; });

			for (int k = 0; k < (int)cur.size(); ) {
				int pos = k;
				
				ll curc = 0;
				ll sum = 0;
				
				while (pos + 1 < (int)cur.size() && A[cur[pos].ind].x + A[cur[pos].ind].e >= A[cur[pos + 1].ind].x) {
					curc = max(curc, max(get(A[cur[pos].ind].x), 0ll));
					sum += A[cur[pos].ind].s;
					pos++;
				}
				curc = max(curc, max(get(A[cur[pos].ind].x), 0ll));
				sum += A[cur[pos].ind].s;
				
				for (int z = k; z <= pos; z++) {
					dp[cur[z].ind] = curc + sum;
				}
				k = pos + 1;
			}
			
            for (auto q : cur) {
           	 	add(A[q.ind].x - A[q.ind].e, A[q.ind].x + A[q.ind].e, dp[q.ind]); 
            }
            i = j - 1;  
        } else {
            del(A[c.ind].x - A[c.ind].e, A[c.ind].x + A[c.ind].e, dp[c.ind]);
        }
        //for (auto c : dp) err("%I64d, ", c); err("\n");
    }
    cout << *max_element(dp.begin(), dp.end());
     
    return 0;
}