#define _ijps 0
#define _CRT_SECURE_NO_DEPRECATE
//#pragma comment(linker, "/STACK:667772160")
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
#include <unordered_set>
#include <bitset>
#include <algorithm>
#include <string>
#include <fstream>
#include <assert.h>
#include <list>
#include <cstring>
#include <queue>
using namespace std;

#define name "problem5"

typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;

struct __isoff {
    __isoff() {
        if (_ijps)
            freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);//, freopen("test.txt", "w", stderr);
        //else freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);
        //ios_bsume::sync_with_stdio(0);
        //srand(time(0));
        srand('C' + 'T' + 'A' + 'C' + 'Y' + 'M' + 'B' + 'A');
    }
    ~__isoff() {
        //if(_ijps) cout<<times<<'\n';
    }
} __osafwf;
const ull p1 = 131;
const ull p2 = 129;
const double eps = 1e-15;
const double pi = acos(-1.0);

const int infi = static_cast<int>(1e9) + 7;
const ll inf = static_cast<ll>(1e18) + 7;
const ll dd = static_cast<ll>(2e3) + 7;
#define times (clock() * 1.0 / CLOCKS_PER_SEC)

const int C1 = 10;
const int C2 = 10;

double project(ll x, ll y, ll z, double a, double b, double c) {
    double s = sqrt(x * x + y * y + z * z);
    double sum = (x * a + y * b + z * c) / s;
  ///  cerr << sum << endl;
    return sum;
}

long double ANG;
vector<ll> VEC(6);

void relax(ll x1, ll y1, ll z1, ll x2, ll y2, ll z2) {
    if (vector<ll> {x1, y1, z1} > vector<ll> {x2, y2, z2}) {
        swap(x1, x2);
        swap(y1, y2);
        swap(z1, z2);
    }
    ll dot = x1 * x2 + y1 * y2 + z1 * z2;
    ll l1 = x1 * x1 + y1 * y1 + z1 * z1;
    ll l2 = x2 * x2 + y2 * y2 + z2 * z2;
    long double cs = (long double) dot / sqrt(l1) / sqrt(l2);
    long double ang = cs;
    if (cs > 1 - eps) {
        return;
    }
    vector<ll> temp{x1, y1, z1, x2, y2, z2};
    if (ANG < ang - eps || (abs(ANG - ang) < eps && VEC > temp)) {
        ANG = ang;
        VEC = temp;
    }
}

ll gcd(ll a, ll b) {
    a = abs(a);
    b = abs(b);
    while (a && b) {
        a %= b;
        swap(a, b);
    }
    return a + b;
}

struct pt { ll x, y, z, id; };

void relax(pt A, pt B) {
	relax(A.x, A.y, A.z, B.x, B.y, B.z);
}

ll dist(pt A, pt B) {
	return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y) + (B.z - A.z);
}

ll go(int l, int r, vector<pt> &p) {
    if (r - l == 1)
        return (ll)1e18;

    int m = (l + r) / 2;
    ll midx = p[m].x;
    ll ansl = go(l, m, p), ansr = go(m, r, p);
    ll cur_ans = min(ansl, ansr);
    ll h = cur_ans;

    vector<pt> res(r - l), cur;

    merge(p.begin() + l, p.begin() + m, p.begin() + m, p.begin() + r, 
        res.begin(), [](pt a, pt b) { return a.y == b.y ? a.x < b.x : a.y < b.y; });
    
    for (pt x : res)
        if (h > (midx - x.x) * (midx - x.x))
            cur.push_back(x);
    
    ll ans = (ll)1e18;

    for(int i = 0; i < (int)cur.size(); i++) {
        for (int j = max(i - 10, 0); j < i; j++) {
        	relax(cur[i], cur[j]);
        	ans = min(ans, dist(cur[i], cur[j]));
        }
    }

    for (int i = l; i < r; i++)
        p[i] = res[i - l];

    return min(cur_ans, ans);
}


void solve(vector<pt> &P) {
	go(0, (int)P.size(), P);
	
for (auto v :VEC) {
            cout << v << ' ';
        }
        cout << endl;
}

int main() {
    int n, m, S, W;
    while (1) {
        cin >> m >> n >> S >> W;
        if (n == 0 && m == 0) {
            break;
        }
        ANG = -100;
        int g = S;
        int total = n + m;
        vector<int> x(0), y(0), z(0);
        {
            vector<int> X(total), Y(total), Z(total);
            for (int i = 0; i < m; i++) {
                cin >> X[i] >> Y[i] >> Z[i];
            }
            for (int i = m + 1; i <= m + n; i++) {
                X[i - 1] = (g / 7) % 100 + 1;
                Y[i - 1] = (g / 700) % 100 + 1;
                Z[i - 1] = (g / 70000) % 100 + 1;
                if (g % 2 == 0) { g = (g / 2); }
                else { g = (g / 2) ^ W; }
            }
            set<vector<ll> > T;
            for (int i = 0; i < total; i++) {
                auto t = gcd(X[i], Y[i]);
                t = gcd(t, Z[i]);
                vector<ll> temp{X[i] / t, Y[i] / t, Z[i] / t};
                if (!T.count(temp)) {
                    T.insert(temp);
                    x.push_back(X[i]);
                    y.push_back(Y[i]);
                    z.push_back(Z[i]);
                }
            }
            total = T.size();
        }
        vector<int> ind(total);
        for (int i = 0; i < total; i++) {
            ind[i] = i;
        }
        
        vector<pt> P;
        
        for (int i = 0; i < total; i++) {
        	P.push_back({ x[i], y[i], z[i], i });
        }
        solve(P);
    }
}