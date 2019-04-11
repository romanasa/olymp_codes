#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    int n;
    cin >> n;

    vector<int> A(n + 2), B(n + 2);
    for (int i = 0; i < n; i++) cin >> A[i + 1];
    for (int i = 0; i < n; i++) cin >> B[i + 1];

    double ans = 0;
    for (int i = 0; i <= n; i++) {
        int a = A[i], b = A[i + 1];
        int c = B[i], d = B[i + 1];

        if (a > c) swap(a, c), swap(b, d);

        //cerr << i << " ";

        if (a == c) {
            ans += abs(d - b) / 2.0;
            //cerr << "1 " << ans << endl;
            continue;
        }

        if (b == d) {
            ans += abs(a - c) / 2.0;
            //cerr << "2 " << ans << endl;
            continue;
        }

        if (b <= d) {
            ans += ((c - a) + (d - b)) / 2.0;
            //cerr << "3 " << ans << endl;
            continue;
        }

        double k = (b - d) * 1.0 / (c - a);
        double S = ((c - a) + (b - d)) / 2.0;
        ans += S / ((k + 1) * (k + 1)) * (k * k + 1);

        //cerr << "4 " << ans << endl;
    }
    cout.precision(10);
    cout << fixed << ans << "\n";
    return 0;
}

