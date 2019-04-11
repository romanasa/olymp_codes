#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int A[1234][1234];

int main() {
#ifdef WIN
    freopen("input.txt", "r", stdin);
#endif
    int q;
    scanf("%d", &q);

    while (q--) {
        int h, w;
        scanf("%d %d", &h, &w);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                scanf("%d", &A[i][j]);
            }
        }

        ll s1 = 0;
        ll s2 = 0;
        for (int i = 0; i < w; i++) {
            s1 += abs(A[h / 2][i] - A[h / 2 - 1][i]);
            s2 += abs(A[h - 1][i] - A[0][i]);
        }
        if (s2 < s1) puts("YES");
        else puts("NO");
    }

	return 0;
}
