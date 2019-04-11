#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int dd = 107;
unordered_map<ull, int> S(1e7);

const int mod = (int)8e8 + 7;
const int P = 31;

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#else
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<string> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];

        for (int j = 0; j < (int)A[i].size(); j++) {
            ull cur = 0;
            for (int k = j; k < (int)A[i].size(); k++) {
                cur = cur * P + A[i][k] - 'a' + 1;
                S[cur]++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int ll = -1, rr = -1, len = (int)1e9;

        for (int j = 0; j < (int)A[i].size(); j++) {
            ull cur = 0;
            for (int k = j; k < (int)A[i].size(); k++) {
                cur = cur * P + A[i][k] - 'a' + 1;
                S[cur]--;
            }
        }

        for (int j = 0; j < (int)A[i].size(); j++) {
            ull cur = 0;
            for (int k = j; k < (int)A[i].size(); k++) {
                cur = cur * P + A[i][k] - 'a' + 1;
                if ((k - j + 1 < len) && S[cur] == 0) {
                    len = k - j + 1;
                    ll = j, rr = k;
                }
            }
        }

        for (int j = 0; j < (int)A[i].size(); j++) {
            ull cur = 0;
            for (int k = j; k < (int)A[i].size(); k++) {
                cur = cur * P + A[i][k] - 'a' + 1;
                S[cur]++;
            }
        }
        cout << string(A[i].begin() + ll, A[i].begin() + rr + 1) << "\n";
    }
    return 0;
}
