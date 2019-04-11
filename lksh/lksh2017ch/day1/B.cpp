#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

string A[7], B[7], C[7];

const int n = 4;

void rot() {
    for (int i = 0; i < n; i++) C[i] = A[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[j][n - i - 1] = C[i][j];
        }
    }
}

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#else
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif

    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];

    string ans;
    for (int it = 0; it < 4; it++) {

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (A[i][j] == 'X') ans += B[i][j];
            }
        }
        rot();
    }
    cout << ans << "\n";
    return 0;
}

