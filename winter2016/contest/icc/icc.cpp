#include "icc.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

const int dd = 107;

struct dsu {
    int P[dd];
    dsu() { for (int i = 0; i < dd; i++) P[i] = i; }

    int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }

    void un(int a, int b) {
        a = get(a), b = get(b);
        if (a != b)
            P[b] = a;
    }
} J;

int a[dd], b[dd];

int ask(vector<int> &A, vector<int> &B) {
    int n = (int)A.size(), m = (int)B.size();
    for (int i = 0; i < n; i++)
        a[i] = A[i] + 1;
    for (int i = 0; i < m; i++)
        b[i] = B[i] + 1;
    return query(n, m, a, b);
}

void run(int n) {

    for (int it = 0; it < n - 1; it++) {
        vector<int> cur;

        for (int i = 0; i < n; i++) {
            if (J.get(i) == i)
                cur.push_back(i);
        }

        int sz = (int)cur.size();

        int lg = 0;

        for (int i = 0; i < 16; i++) {
            if ((sz >> i) & 1)
                lg = i;
        }

        for (int bit = 0; bit <= lg; bit++) {

            vector<int> A, B;
            set<int> T;

            for (int i = 0; i < (int)cur.size(); i++) {
                if ((i >> bit) & 1) {
                    T.insert(J.get(cur[i]));
                }
            }

            for (int i = 0; i < n; i++) {
                if (T.count(J.get(i)))
                    A.push_back(i);
                else
                    B.push_back(i);
            }

            if (bit == lg || ask(A, B)) {

                vector<int> a, b;
                set<int> S;

                for (int x : A)
                    S.insert(J.get(x));

                for (int i = 0; i < n; i++) {
                    if (S.count(J.get(i))) {
                        a.push_back(i);
                    } else {
                        b.push_back(i);
                    }
                }


                int ind1 = 0;
                {
                    int l = -1, r = (int)a.size() - 1;
                    while (r - l > 1) {
                        //err("l = %d,  r = %d\n", l, r);
                        int m = (l + r) / 2;

                        vector<int> G;
                        for (int i = 0; i <= m; i++) {
                            G.push_back(a[i]);
                        }

                        if (ask(G, b)) {
                            r = m;
                        } else {
                            l = m;
                        }
                    }
                    ind1 = r;
                }

                int ind2 = 0;
                {
                    int l = -1, r = (int)b.size() - 1;
                    while (r - l > 1) {
                        int m = (l + r) / 2;

                        vector<int> G;
                        for (int i = 0; i <= m; i++) {
                            G.push_back(b[i]);
                        }

                        if (ask(a, G)) {
                            r = m;
                        } else {
                            l = m;
                        }
                    }
                    ind2 = r;
                }
                setRoad(a[ind1] + 1, b[ind2] + 1);
                J.un(a[ind1], b[ind2]);
                break;
            }
        }
    }
}
