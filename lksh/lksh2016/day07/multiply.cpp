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
#include <cstring>
#include <sstream>
#include <numeric>
#include <complex>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (ll i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "multiply"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll inf = (ll)2e9 + 1;
const ll linf = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

const int dd = 1e5 + 7;

typedef complex<double> cmpl;

int reverse(int x, int k) {
    int t = 0;
    forn(i, k) {
        if (x & (1 << i)) {
            t += 1 << (k - i - 1);
        }
    }
    return t;
}

void FFT(cmpl *a, int k, bool rev) {
    int N = 1 << k;
    forn(i, N) {
        int j = reverse(i, k);
        if (i < j)
            swap(a[i], a[j]);
    }

    for (int L = 1; L < N; L *= 2) {
        double phi = (2 * pi) / (2 * L) * (rev ? -1 : 1);
        cmpl wn(cos(phi), sin(phi));

        for (int i = 0; i < N; i += 2 * L) {
            cmpl wp(1, 0);
            for (int j = 0; j < L; j++) {
                cmpl u = a[i + j];
                cmpl v = a[i + j + L] * wp;

                a[i + j] = u + v;
                a[i + j + L] = u - v;

                wp *= wn;
            }
        }
    }
    if (rev) {
        forn(i, N)
            a[i] /= N;
    }
}

int solve() {
    string a, b;
    cin >> a >> b;

    int N = a.size() + b.size();

    int lg = 1;

    while ((1 << lg) < N)
        lg++;

    N = 1 << lg;

    cmpl *A = new cmpl[N]();
    cmpl *B = new cmpl[N]();

    reverse(all(a));
    reverse(all(b));

    bool neg = false;

    if (a.back() == '-') {
        neg ^= 1;
        a.pop_back();
    }

    if (b.back() == '-') {
        neg ^= 1;
        b.pop_back();
    }



    forn(i, a.size()) {
        A[i] = a[i] - '0';
    }

    forn(i, b.size()) {
        B[i] = b[i] - '0';
    }

    FFT(A, lg, false);
    FFT(B, lg, false);
    forn(i, N)
        A[i] = A[i] * B[i];
    FFT(A, lg, true);

    vector<int> T(N + 1);
    forn(i, N)
        T[i] = ((int)(A[i].real() + 0.5));

    forn(i, N) {
        T[i + 1] += T[i] / 10;
        T[i] %= 10;
    }

    while (T.size() > 1 && !T.back())
        T.pop_back();

    reverse(all(T));

    if (neg)
        putchar('-');

    for (int x : T)
        cout << x;

    return 0;
}