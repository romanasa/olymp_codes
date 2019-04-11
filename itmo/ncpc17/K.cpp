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
const double eps = 1e-8;
const double pi = acos(-1.0);

const int infi = static_cast<int>(1e9) + 7;
const ll inf = static_cast<ll>(1e18) + 7;
const ll dd = static_cast<ll>(2e3) + 7;
#define times (clock() * 1.0 / CLOCKS_PER_SEC)


vector<int> cap;

bool check(int speed, vector<int> count, vector<int> strength) {
    for (auto c : cap) {
        int mx = infi;
        int a, b;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == j && count[i] < 2) {
                    continue;
                }
                if (count[i] > 0 && count[j] > 0) {
                    int cspeed = (strength[i] + strength[j]) * c;
                    if (cspeed >= speed) {
                        if (mx > strength[i] + strength[j]) {
                            mx = strength[i] + strength[j];
                            a = i;
                            b = j;
                        }
                    }
                }
            }
        }
        if (mx == infi) {
            return false;
        }
        count[a]--;
        count[b]--;
    }
    return true;
}

int main() {
    vector<int> count;
    vector<int> strength;
    count.resize(3);
    for (int i = 0; i < 3; i++) {
        cin >> count[i];
    }
    strength.resize(3);
    for (int i = 0; i < 3; i++) {
        cin >> strength[i];
    }
    int n = (count[0] + count[1] + count[2]) / 2;
    cap.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> cap[i];
    }
    sort(cap.begin(), cap.end());
    int l = 0, r = infi;
    while (r - l > 1) {
        int s = (l + r) / 2;
        if (check(s, count, strength)) {
            l = s;
        } else {
            r = s;
        }
    }
    cout << l;
}