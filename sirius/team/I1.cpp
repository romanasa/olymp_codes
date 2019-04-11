#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

char A[57][57];
int s[57][57];

inline int get(int x1, int y1, int x2, int y2) {
    return s[x2 + 1][y2 + 1] - s[x1][y2 + 1] - s[x2 + 1][y1] + s[x1][y1];
}

int n;

bool check(int x1, int y1, int x2, int y2, int c) {
    x1 = max(x1, 1);
    x2 = min(x2, n);

    y1 = max(y1, 1);
    y2 = min(y2, n);

    if (x1 > x2 || y1 > y2) return true;
    return get(x1, y1, x2, y2) == c * (x2 - x1 + 1) * (y2 - y1 + 1);
}

int main() {
#ifdef WIN
    freopen("input.txt", "r", stdin);
#endif
    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%s", A[i]);

    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += A[i][j] - '0';
            s[i + 2][j + 2] = s[i + 1][j + 2] + s[i + 2][j + 1] - s[i + 1][j + 1] + A[i][j] - '0';
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int t = i; t <= n; t++) {
                for (int l = j; l <= n; l++) {

                    if (sum != get(i - 1, j - 1, min(t + 1, n), min(l + 1, n))) continue;

                    if (!check(i, j, t, l, 4)) continue;

                    if (!check(i, j - 1, t, j - 1, 2)) continue;
                    if (!check(i, l + 1, t, l + 1, 2)) continue;

                    if (!check(i - 1, j, i - 1, l, 2)) continue;

                    if (!check(t + 1, j, t + 1, l, 2)) continue;

                    if (!check(i - 1, j - 1, i - 1, j - 1, 1)) continue;
                    if (!check(t + 1, l + 1, t + 1, l + 1, 1)) continue;
                    if (!check(i - 1, l + 1, i - 1, l + 1, 1)) continue;
                    if (!check(t + 1, j - 1, t + 1, j - 1, 1)) continue;

                    ans++;
                }
            }
        }
    }
    puts(ans == 1 ? "Yes" : "No");
	return 0;
}
