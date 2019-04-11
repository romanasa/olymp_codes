#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int mod = (int)1e6 + 3;

const int dd = (int)2e2 + 1;

int s[111];

void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

int main() {
#ifdef WIN
    freopen("input.txt", "r", stdin);
#endif
    int c, w, h;
    cin >> c >> w >> h;

    for (int i = 1; i <= c; i++) {

        int p = h;
        int cur = 0;

        for (int j = 1; j <= min(w, i); j++) {

            if (i - j > 1) add(cur, 1ll * p * s[i - j - 1] % mod);

            add(cur, p);
            p = p * h % mod;
        }

        s[105] = s[104];
        add(s[105], cur);

        for (int i = 0; i < 105; i++) s[i] = s[i + 1];
    }

    cout << s[104] + 1 << "\n";
	return 0;
}

