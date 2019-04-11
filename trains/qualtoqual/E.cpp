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

struct man {
    string name;
    double a, b;
};

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    int n;
    cin >> n;

    vector<man> A(n);
    for (int i = 0; i < n; i++) {
        string s;
        double a, b;
        cin >> s >> a >> b;
        A[i] = { s, a, b };
    }


    double ans = 1e18;
    string a, b, c, d;
    for (int i = 0; i < n; i++) {

        auto B = A;
        B.erase(B.begin() + i);

        sort(B.begin(), B.end(), [](man Q, man W) {
            return Q.b < W.b;
        });

        double cur = A[i].a + B[0].b + B[1].b + B[2].b;
        if (cur < ans) {
            ans = cur;
            a = A[i].name;
            b = B[0].name;
            c = B[1].name;
            d = B[2].name;
        }
    }
    cout.precision(10);
    cout << fixed << ans << "\n";
    cout << a << "\n" << b << "\n" << c << "\n" << d << "\n";
    return 0;
}

