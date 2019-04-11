#define _ijps 01
#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(linker, "/STACK:667772160")
#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <map>
#include <set>
#include <deque>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <bitset>
#include <algorithm>
#include <string>
#include <fstream>
#include <assert.h>
#include <list>
#include <cstring>
using namespace std;
 
#define name ""
typedef unsigned long long ull;
typedef long long ll;
#define mk make_pair
#define forn(i, n) for(ll i = 0; i < (ll)n; i++)
#define fornn(i, q, n) for(ll i = (ll)q; i < (ll)n; i++)
#define times clock() * 1.0 / CLOCKS_PER_SEC
 
struct __isoff{
    __isoff(){
        if (_ijps)
            freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);//, freopen("test.txt", "w", stderr);
        else freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);
        //ios_base::sync_with_stdio(0);
        //srand(time(0));
        srand('C' + 'T' + 'A' + 'C' + 'Y' + 'M' + 'B' + 'A');
    }
    ~__isoff(){
        //if(_ijps) cout<<times<<'\n';
    }
} __osafwf;
const ull p1 = 131;
const ull p2 = 129;
const double eps = 1e-7;
const double pi = acos(-1.0);
 
const int infi = 1e9 + 7;
const ll inf = 1e18 + 7;
const ll dd = 1500 + 7;
const ll mod = 1e9 + 7;
 
int n;
 
 
struct ver2{
    ll sl, sr, mx;
};
 
struct ver{
    ver2 E[3];
    int n;
    ll s;
};
 
ver merge(ver a, ver b){
    ver c;
    forn(i, 3){
        c.E[i].mx = max(a.E[i].mx, b.E[i].mx);
        c.E[i].sl = a.E[i].sl;
        c.E[i].sr = b.E[i].sr;
    }
    c.n = a.n + b.n;
    c.s = a.s + b.s;
    forn(i,  min(3, a.n + 1)){
        forn(j, min(3, b.n + 1)){
            c.E[min(i + j, 2ll)].mx = max(c.E[min(i + j, 2ll)].mx, a.E[i].sr + b.E[j].sl);
        }
    }
    forn(i, min(3, a.n + 1)){
        c.E[min(i + b.n, 2ll)].sr = max(c.E[min(i + b.n, 2ll)].sr, a.E[i].sr + b.s);
    }
    forn(i, min(3, b.n + 1)){
        c.E[min(i + a.n, 2ll)].sl = max(c.E[min(i + a.n, 2ll)].sl, b.E[i].sl + a.s);
    }
    return c;
};
 
struct seg{
    ver F[dd * 4];
    void build(int v, int l, int r){
        forn(j, 3){
            ll t = 0;
            if(j > 0){
                t = -inf;
            }
            F[v].E[j].mx = F[v].E[j].sl = F[v].E[j].sr = t;
        }
        F[v].n = 0;
        F[v].s = 0;
        if(l == r){
            return;
        }
        int s = (l + r) / 2;
        build(v * 2, l, s);
        build(v * 2 + 1, s + 1, r);
    }
    void up(int v, int l, int r, int x, int s){
        if(l == r){
            F[v].n++;
            F[v].E[0].mx += s;
            F[v].E[0].sl += s;
            F[v].E[0].sr += s;
            F[v].s += s;
            fornn(i, 1, min(F[v].n + 1, 3)){
                F[v].E[i] = F[v].E[i - 1];
            }
            return;
        }
        int e = (l + r) / 2;
        if(x <= e){
            up(v * 2, l, e, x, s);
        }
        else{
            up(v * 2 + 1, e + 1, r, x, s);
        }
        F[v] = merge(F[v * 2], F[v * 2 + 1]);
    }
    ll getMax(){
        return F[1].E[2].mx;
    }
};
 
struct en{
    int x, y;
    ll s;
};
 
vector<en> PX[dd];
vector<en> PY[dd];
const int sizeN = 1507;
 
ll Dp[sizeN][sizeN];
 
ll getSum(ll x1, ll y1, ll x2, ll y2){
    if(x1 > x2){
        swap(x1, x2);
    }
    if(y1 > y2){
        swap(y1, y2);
    }
    x1--, y1--;
    return Dp[x2][y2] + Dp[x1][y1] - Dp[x1][y2] - Dp[x2][y1];
}
 
int main(){
    cin >> n;
    vector<int> X, Y;
    vector<en> P(n);
    forn(i, n){
        int a, f, s;
        cin >> a >> f >> s;
        X.push_back(a);
        Y.push_back(f);
        P[i].x = a;
        P[i].y = f;
        P[i].s = s;
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    X.resize(unique(X.begin(), X.end()) - X.begin());
    Y.resize(unique(Y.begin(), Y.end()) - Y.begin());
    map<int, int> GoX, GoY;
    forn(i, X.size()){
        GoX[X[i]] = i;
    }
    forn(i, Y.size()){
        GoY[Y[i]] = i;
    }
    forn(i, n){
        P[i].x = GoX[P[i].x];
        P[i].y = GoY[P[i].y];
        PX[P[i].x].push_back(P[i]);
    }
    ll res = -inf;
    int l, r, ql, qr;
    forn(i, X.size()){
        seg T;
        T.build(1, 0, Y.size());
        for(int k = i; k < X.size(); k++){
            for(int j = 0; j < PX[k].size(); j++){
                T.up(1, 0, Y.size(), PX[k][j].y, PX[k][j].s);
            }
            ll q = T.getMax();
            if(res < q){
                res = q;
                l = i, r = k;
            }
        }
    }
    for(int i = l; i <= r; i++){
        for(int j = 0; j < PX[i].size(); j++){
            PY[PX[i][j].y].push_back(PX[i][j]);
        }
    }
    int nm = 0;
    forn(i, Y.size()){
        ll s = 0;
        nm = 0;
        bool ok = 0;
        for(int j = i; j < Y.size(); j++){
            forn(k, PY[j].size()){
                s += PY[j][k].s;
                nm++;
            }
            if(s == res && nm >= 2){
                ql = i;
                qr = j;
                ok = 1;
                break;
            }
        }
        if(ok){
            break;
        }
    }
    forn(i, n){
            Dp[P[i].x + 1][P[i].y + 1] += P[i].s;
    }
    fornn(i, 1, sizeN){
        fornn(j, 1, sizeN){
            Dp[i][j] = Dp[i - 1][j] + Dp[i][j - 1] - Dp[i - 1][j - 1] + Dp[i][j];
        }
    }
    if(0)if(nm < 2){
         
        res = -inf;
        forn(i, n){
            forn(j, n){
                if(i != j){
                    ll q = getSum(P[i].x + 1, P[i].y + 1, P[j].x + 1, P[j].y + 1);
                    if(res < q){
                        res = q;
                        l = min(P[i].x, P[j].x);
                        r = max(P[i].x, P[j].x);
                        ql = min(P[i].y, P[j].y);
                        qr = max(P[i].y, P[j].y);
                    }
                }
            }
        }
    }
    cout << X[l] << ' ' << X[r] << '\n';
    cout << Y[ql] << ' ' << Y[qr] << '\n';
    //cout << res;
}