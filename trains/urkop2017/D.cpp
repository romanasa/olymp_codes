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

int n, m, q;
bool was[444][444];
int func[444][444];
int func2[444][444];
int ww[1000007];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> q;
    for (int i = 0; i < q; i++){
        int x, y;
        cin >> x >> y;
        was[x][y] = 1;
    }
    for (int i = 0; i <= n; i++) was[i][0] = 1, was[i][m] = 1;
    for (int i = 0; i <= m; i++) was[0][i] = 1, was[n][i] = 1;

    for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) func[i][j] = -1;

    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++) if (was[i][j]){
            for (int to = 0; to <= m; to++){
                int dd = abs(j - to);
                if (func[i][to] == -1) func[i][to] = dd;
                else func[i][to] = min(func[i][to], dd);
            }
        }
    }

    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            func2[i][j] = -1;
            for (int to = 0; to <= n; to++) if (func[to][j] != -1){
                int dd = abs(i - to) * abs(i - to) + func[to][j] * func[to][j];
                if (func2[i][j] == -1) func2[i][j] = dd;
                else func2[i][j] = min(func2[i][j], dd);
            }
        }
    }

    for (int i = 0; i < 1000007; i++) ww[i] = -1;
    for (int i = 0; i * i < 1000007; i++) ww[i * i] = i;

    int last = 1;
    for (int i = 1; i < 1000007; i++){
        if (ww[i] != -1){
            last = ww[i];
        } else ww[i] = last;
    }

    int ansx = -1, ansy = -1, ansr = -1;

    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            int now = func2[i][j];
            int can = ww[now];
            //cout << i << ' ' << j << ' ' << now << ' ' << can << endl;
            if (can > 0){
                if (ansr == -1){
                    ansr = can;
                    ansx = i;
                    ansy = j;
                } else if (ansr < can){
                    ansr = can;
                    ansx = i;
                    ansy = j;
                }
            }
        }
    }

    if (ansr == -1) cout << -1;
    else cout << ansx << ' ' << ansy << ' ' << ansr;
    return 0;
}
