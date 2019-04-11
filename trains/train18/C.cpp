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

int solve(vector<int> a, int g){
    for (int i = 0; i < a.size(); i++) if (a[i] == -1){
        if (i == 0 || a[i - 1] != g) if (i == (int)a.size() - 1 || a[i + 1] != g){
            a[i] = g;
            if (solve(a, g ^ 1) == 0) return 1;
            a[i] = -1;
        }
    }

    return 0;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    int n;
    cin >> n;
    if (n == 1) cout << "B";
    else cout << "A";
    exit(0);
    for (n = 1; n <= 20; n++){
        vector<int> a(n);
        for (int i = 0; i < n; i++) a[i] = -1;
        cout << solve(a, 0) << endl;
    }
}

