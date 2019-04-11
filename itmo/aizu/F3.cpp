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
//[25 30)
const int C1 = 10;
const int C2 = 10;

double project(ll x, ll y, ll z, double a, double b, double c, double d) {
    double dot = a * x + b * y + c * z;
    //double len1 = sqrt(a * a + b * b + c * c);
    //double len2 = sqrt(x * x + y * y + z * z);
    double s = dot;
    return s;
}

long double ANG;
vector<ll> VEC(6);

void relax(ll x1, ll y1, ll z1, ll x2, ll y2, ll z2) {
    ll dot = x1 * x2 + y1 * y2 + z1 * z2;
    ll l1 = x1 * x1 + y1 * y1 + z1 * z1;
    ll l2 = x2 * x2 + y2 * y2 + z2 * z2;
    long double cs = (long double) dot / sqrt(l1) / sqrt(l2);
    long double ang = cs;
    if (cs > 1 - eps || ANG > cs + eps) {
        return;
    }
    if (vector<ll> {x1, y1, z1} > vector<ll> {x2, y2, z2}) {
        swap(x1, x2);
        swap(y1, y2);
        swap(z1, z2);
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
        
        vector<double> len(total);
        for (int i = 0; i < total; i++) {
        	len[i] = sqrt(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
        }
        
        vector<int> ind(total);
        for (int i = 0; i < total; i++) {
            ind[i] = i;
        }
        for (int it = 0; it < C1; it++) {
            double A = rand() * 1.0 / RAND_MAX - 0.5;
            double B = rand() * 1.0 / RAND_MAX - 0.5;
            double C = rand() * 1.0 / RAND_MAX - 0.5;
            double D = rand() * 1.0 / RAND_MAX - 0.5;
            vector<pair<double, int> > n_ind(total);
            for (int i = 0; i < total; i++) {
                n_ind[i] = {project(x[i], y[i], z[i], A, B, C, D) , i};
            }
            sort(n_ind.begin(), n_ind.end(), [](pair<double, int> a, pair<double, int> b) {
            	return a.first * 
            });
            for (int i = 0; i < total; i++) {
                ind[i] = n_ind[i].second;
            }
            for (int j = 0; j < total; j++) {
                for (int k = -C2; k <= C2; k++) {
                    int i = k + j;
                    if (0 <= i && i < total && j != i) {
                        relax(x[ind[i]], y[ind[i]], z[ind[i]], x[ind[j]], y[ind[j]], z[ind[j]]);
                    }
                }
            }
        }
        cerr << (double)ANG << '\n';
        for (auto v :VEC) {
            cout << v << ' ';
        }
        cout << endl;
    }
}