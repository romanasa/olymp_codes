#include "lightbulbs.h"
#include <bits/stdc++.h>
 
using namespace std;
 
const int dd = (int)1e7 + 1;
 
int ask(int st) {
    int x = Walk(st);
    Rollback();
    return x;
}
 
int ch(int st, int c) {
    Walk(st);
    SwitchTo(c);
    Rollback();
}
 
int go[2][dd];
int nv = 2;
 
struct node {
    int cA, cB;
    int ind;
};
 
map<pair<int, int>, node> M;
 
node get(int a, int b) {
    if (M.count({ a, b })) return M[{ a, b }];
 
    node cur = { a, b, nv++ };
    return M[{ a, b }] = cur;
}
 
void calc(node cur) {
    //printf("%d\n", cur.ind);
 
    Walk(0), SwitchTo(0);
        Walk(0), SwitchTo(0), Rollback();
        Walk(1), SwitchTo(0), Rollback();
    Rollback();
 
    Walk(1), SwitchTo(0);
        Walk(0), SwitchTo(0), Rollback();
        Walk(1), SwitchTo(0), Rollback();
    Rollback();
 
    node xa = get(cur.cA + 1, cur.cB);
    node xb = get(cur.cA, cur.cB + 1);
 
    for (int dir = 0; dir < 2; dir++) {
 
        Walk(go[0][cur.ind]);
 
        Walk(dir), SwitchTo(1), Rollback();
 
        Rollback();
 
        Walk(go[1][cur.ind]);
 
        int x0 = Walk(0);
        SwitchTo(0), Rollback();
 
        int x1 = Walk(1);
        SwitchTo(0), Rollback();
 
        Rollback();
 
        if (x0) {
            go[dir ^ 1][xa.ind] = 0;
            go[dir][xa.ind] = 1;
 
            go[0][xb.ind] = 0;
            go[1][xb.ind] = 1;
            break;
        }
 
        if (x1) {
            go[dir ^ 1][xa.ind] = 0;
            go[dir][xa.ind] = 1;
 
            go[1][xb.ind] = 0;
            go[0][xb.ind] = 1;
            break;
        }
    }
}
 
set<pair<int, int> > S;
 
const int C = (int)3e4;
 
void calc(int x, int y) {
 
    if (x + y > C) return;
 
    if (S.count({ x, y })) return;
    S.insert({ x, y });
 
    calc(get(x, y));
 
    if (y == 0) {
        Walk(go[0][get(x, y).ind]);
        calc(x + 1, y);
        Rollback();
    }
 
    if (x == 0) {
        Walk(go[1][get(x, y).ind]);
        calc(x, y + 1);
        Rollback();
    }
 
}
 
void FindAB(int state) {
 
    {
        //a = 1, b = 1
        ch(0, 0);
        ch(1, 1);
        if (ask(0) == 1) {
            Answer(1, 1);
            return;
        }
    }
 
    for (int i = 0; i < dd; i++) go[0][i] = go[1][i] = -1;
 
    node root = get(0, 0);
    go[0][root.ind] = 0;
    go[1][root.ind] = 1;
 
    calc(0, 0);
 
    //printf("find\n");
 
    node cur = root;
 
    for (int i = 0; i < C; i++) {
 
        Walk(go[0][cur.ind]);
        SwitchTo(1);
        cur = get(cur.cA + 1, cur.cB);
    }
    for (int i = 0; i < C; i++) {
        Rollback();
    }
 
    cur = root;
    int aa = -1, bb = -1;
 
    int cnt = 0;
    for (; ; cnt++) {
        int x = Walk(go[1][cur.ind]);
        if (x) {
            SwitchTo(0);
            cnt++;
            aa = cnt;
            break;
        }
        cur = get(cur.cA, cur.cB + 1);
    }
 
    for (int it = 0; it < cnt; it++) {
        Rollback();
    }
 
    cur = root;
 
    for (int i = 0; i < C; i++) {
        int x = Walk(go[0][cur.ind]);
        if (x == 0) {
            bb = i + 1;
            int tt = __gcd(aa, bb);
            aa /= tt, bb /= tt;
            Answer(min(aa, bb), max(aa, bb));
            return;
        }
        cur = get(cur.cA + 1, cur.cB);
    }
}