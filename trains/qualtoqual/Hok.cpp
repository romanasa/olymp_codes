#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()

using namespace std;

typedef long long ll;
typedef double db;

const int dd = (int)5e3 + 7;

int cur[123];
int op[123];
int cl[123];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        p[x]++;
        t = max(x, t);
    }

    t++;
    for (int msk = 0; msk < (1 << t); msk++) {
        if (t & 1) continue;

        cur[i] = 0;
        for (int i = 0; i + 1 < t; i++) cur[i + 1] = cur[i] ^ ((msk >> i) & 1);


        int q = 0, ok = 1;
        for (int i = 0; i < t; i++) {
            if (cur[i]) q++;
            else {
                if (q < 6) ok = 0;
                q = 0;
            }
        }
        if (q < 6) ok = 0;

        if (!ok) continue;

        for (int i = 0; i < t; i++) {
            if ((i == 0 || cur[i - 1] == 0) && cur[i] == 1) {
                op[i + 3] = 1;
            }
            if ((i == 0 || cur[i - 1] == 1) && cur[i] == 0) {
                cl[i - 2] = 1;
            }
        }


        int curT = 0;
        for (int i = 0; i < t; i++) {
            if (p[i]) {
                curT++;
            }
        }
    }

    return 0;
}


