#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

char A[543][543];
int T[543][543];

struct pt { ll x, y; };

struct vt {
    ll x, y;
    vt() {}
    vt(pt A, pt B) { x = B.x - A.x, y = B.y - A.y; }
    ll operator % (vt b) {
        return x * b.y - y * b.x;
    }
};

ll dist(pt A, pt B) {
    return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y);
}

bool check(int i, int j) {
    int sum = 0;
    for (int di = -1; di <= 0; di++) {
        for (int dj = -1; dj <= 0; dj++) {
            int ni = i + di, nj = j + dj;
            if (ni >= 0 && nj >= 0 && T[ni][nj] == 0) sum++;
        }
    }
    return sum == 0;
}

int main() {
#ifdef WIN
    freopen("input.txt", "r", stdin);
#endif
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;

        for (int i = 0; i < n; i++) {
            scanf("%s", A[i]);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                T[n - 1 - i][j] = A[i][j] - '0';
            }
        }

        vector<pt> P;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (T[i][j] == 1) {

                    for (int di = 0; di <= 1; di++) {
                        for (int dj = 0; dj <= 1; dj++) {

                            int ni = i + di, nj = j + dj;

                            if (ni >= n || nj >= n) continue;


                            if (check(ni, nj)) {
                                P.push_back({ ni, nj });
                            }
                        }
                    }

                }
            }
        }
        sort(P.begin(), P.end(), [](pt A, pt B){ return A.y == B.y ? A.x < B.x : A.y < B.y; });

        pt O = P[0];

        sort(P.begin() + 1, P.end(), [O](pt A, pt B) {
            ll t = vt(O, A) % vt(O, B);
            if (t == 0) return dist(O, A) < dist(O, B);
            return t > 0;
        });



        vector<pt> st;
        for (auto p : P) {
            while (st.size() > 1 && (vt(st[st.size() - 2], st.back()) % vt(st.back(), p)) <= 0)
                st.pop_back();
            st.push_back(p);
        }

        printf("%d\n", (int)st.size());
        for (auto c : st) printf("%I64d %I64d\n", c.y, c.x);
    }
	return 0;
}
