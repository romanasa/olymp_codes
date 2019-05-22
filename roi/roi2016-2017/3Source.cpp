#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <queue>
#include <string>
#include <cassert>
 
using namespace std;
 
int solve();
 
typedef long long ll;
 
int main() {
#ifdef ROII
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    solve();
}
/* 
const int MAX_MEM = (int)4e8 + 1;
char MEM[MAX_MEM];
int mpos;

inline void* operator new (size_t n) {
	char *res = MEM + mpos;
	mpos += n;
	return (void*)res;
}

inline void operator delete (void*) {}
*/
struct pt {
    ll x, y;
    int ind;
    pt() {}
    pt(ll x, ll y) : x(x), y(y) {}
    pt(pt A, pt B) : x(B.x - A.x), y(B.y - A.y) {}
    ll operator % (pt b) { return x * b.y - y * b.x; }
};
 
ll dist(pt A, pt B) { return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y); }
 
void out(vector<pt> &T) {
    cout << "! " << (int)T.size() << " ";
    for (auto p : T) cout << p.ind << " ";
    cout << endl;
}
 
int ask(vector<pt> &T) {
    if (T.size() < 3) return 0;
    cout << "? " << (int)T.size() << " ";
    for (auto p : T) cout << p.ind << " ";
    cout << endl;
    string s;
    cin >> s;
    return (s == "Yes");
}
 
vector<pt> Convex(vector<pt> &P) {
    stable_sort(P.begin(), P.end(), [](pt A, pt B) { return A.x == B.x ? A.y < B.y : A.x < B.x; });
    pt O = P[0];
    stable_sort(P.begin() + 1, P.end(), [O](pt A, pt B) {
        ll t = pt(O, A) % pt(O, B);
        if (t == 0) return dist(O, A) < dist(O, B);
        return t > 0;
    });
    vector<pt> T;
    for (auto p : P) {
        while (T.size() > 1 && (pt(T[T.size() - 2], T.back()) % pt(T.back(), p)) <= 0) {
            T.pop_back();
        }
        T.push_back(p);
    }
    return T;
}
 
int sgn(ll x) { return x ? x > 0 ? 1 : -1 : 0; }
 
bool in(pt A, pt B, pt C, pt M) {
    int s1 = sgn(pt(A, B) % pt(A, M));
    int s2 = sgn(pt(B, C) % pt(B, M));
    int s3 = sgn(pt(C, A) % pt(C, M));
    return s1 == s2 && s2 == s3;
}
 
void go(vector<pt> &T, vector<pt> &P) {
 
    if (P.size() == T.size()) {
        out(P);
        return;
    }
 
    int n = (int)T.size();
 
    vector<pt> A, B, C;
 
    int ind = n / 2;
 
    for (auto p : T) {
        if (pt(T[0], p) % pt(T[0], T[ind]) >= 0) A.push_back(p);
        if (pt(T[0], p) % pt(T[0], T[ind]) <= 0) B.push_back(p);
    }
 
    pt a, b, c;
    int ok = 0;
 
    for (int i = 1; i + 1 < (int)P.size(); i++) {
        int s1 = sgn(pt(T[0], P[i]) % pt(T[0], T[ind]));
        int s2 = sgn(pt(T[0], P[i + 1]) % pt(T[0], T[ind]));
        if (s1 != s2) {
            a = P[i], b = P[i + 1], c = T[ind];
            ok = 1;
        }
    }
 
    if (ok) {
        C.push_back(a);
        C.push_back(b);
        C.push_back(c);
        for (auto p : T) {
            if (in(a, b, c, p)) {
                C.push_back(p);
            }
        }
    }
 
    int t = 0;
    vector<pt> tmp;
 
    if (ask(tmp = Convex(A))) go(A, tmp);
    else if (ask(tmp = Convex(C))) go(C, tmp);
    else go(B, tmp = Convex(B));
 
}
 
int solve() {
    int n;
    cin >> n;
 
    vector<pt> P(n);
    for (int i = 0; i < n; i++) {
        cin >> P[i].x >> P[i].y;
        P[i].ind = i + 1;
    }
 
    int q;
    cin >> q;
    auto Q = Convex(P);
 
 
    for (int it = 0; it < q; it++) {
        go(P, Q);
    }
    return 0;
}