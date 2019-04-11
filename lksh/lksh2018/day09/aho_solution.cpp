#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <ctime>
#include <cstring>
#include <cassert>
#include <bitset>
#include <sstream>
#include <queue>

#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define sz(a) ((int) (a).size())
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

typedef long long int64;
typedef long double ldb;

const long double eps = 1e-9;
const int inf = (1 << 30) - 1;
const long long inf64 = ((long long)1 << 62) - 1;
const long double pi = acos(-1);

template <class T> T sqr (T x) {return x * x;}
template <class T> T abs (T x) {return x < 0 ? -x : x;}

const int MAXN = 200 * 1000 + 100;

int n, m, cur_q;
int pr[MAXN];
char tmp[10];

void ask(int x) {
    if (x < n) {
        printf ("s %d", x + 1);
    } else {
        printf ("t %d", x - n);
    }
}

bool ask (int x, int y) {
    if (x == y)
        return true;
    if (x == n || y == n)
        return false;

    cur_q++;
    ask(x);
    printf(" ");
    ask(y);
    printf("\n");
    fflush(stdout);

    scanf ("%s", tmp);
    return (tmp[0] == 'Y');
}

int main () {
//  ios_base::sync_with_stdio(0);
//	freopen("input.txt", "rt", stdin);
//	freopen("output.txt", "wt", stdout);

    scanf ("%d%d", &n, &m);

    pr[0] = 0;
    pr[1] = 1;
    int ind = 1;

    int ans = 0;
    for (int i = 0; i < m; ++i) {
        cur_q = 0;

        while (cur_q < 3 && ind <= n + i + 1) {
            if (ask(ind, pr[ind] - 1)) {
                pr[ind + 1] = pr[ind] + 1;
                ind++;
            } else {
                if (pr[ind] == 1) {
                    pr[ind] = 0;
                    pr[ind + 1] = pr[ind] + 1;
                    ind++;
                } else {
                    pr[ind] = pr[pr[ind] - 2] + 1;
                }
            }
        }

        if (pr[n + i + 1] == n) {
            ans++;
        }

        printf ("$ %d\n", ans);
        fflush(stdout);
    }


	return 0;
}
