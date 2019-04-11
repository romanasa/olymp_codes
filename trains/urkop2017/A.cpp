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

int get(int x) {
    int sum = 0;
    while (x) sum += x % 10, x /= 10;
    return sum;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    for (int j = 0; j < n; j++) {

        int sum = 0;
        for (int i = j; i >= 0; i--) {
            sum += A[i];
            if (sum > 50) break;

            if (sum == get(j - i + 1)) {
                cout << i + 1 << " " << j + 1 << "\n";
                return 0;
            }
        }
    }
    cout << -1;
    return 0;
}

