#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()
//236695ZVSVG

using namespace std;

typedef long long ll;
typedef double db;

int n;
pair<ll, ll> a[100007];
ll tout, v;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
    cin >> tout >> v;
    int last = -2;
    for (int i = 0; i < n; i++) if (a[i].y >= tout && a[i].x <= (a[i].y - tout) * v){
        if (last == -2) last = 0;
        else {
            if (a[i].x < a[last].x){
                last = i;
            } else if (a[i].x == a[last].x){
                if ((a[i].y - a[last].y) * v < a[last].x - a[i].x){
                    last = i;
                }
            }
        }
    }
    cout << last + 1;
    return 0;
}

