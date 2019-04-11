#include <bits/stdc++.h>
#define err(...) //fprintf(stderr, __VA_ARGS__)

using namespace std;

typedef long long ll;

const int mod = (int)1e9 + 7;

int P[2007];

int main() {
    int n, S, T;
    scanf("%d %d %d", &n, &S, &T);
    S--, T--;

    if (S > T) swap(S, T);

    for (int i = 0; i < n; i++) {
        P[i] = i;
    }

    int ans = 0;
    do {
        if (P[0] != S) continue;
        if (P[n - 1] != T) continue;

        int ok = 1;
        for (int i = 1; i + 1 < n; i++)
            if (P[i - 1] < P[i] && P[i] < P[i + 1] ||
                P[i - 1] > P[i] && P[i] > P[i + 1])
                ok = 0;
        ans += ok;
        if (ok) {
            for (int i = 0; i < n; i++) {
                err("%d ", P[i] + 1);
            }
            err("\n");
        }
    } while (next_permutation(P, P + n));
    printf("%d\n", ans);
    return 0;
}

