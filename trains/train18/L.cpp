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

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    map<int, int> cnt1, cnt2;

    for (int i = 0; i < 3; i++) {
        int x;
        cin >> x;
        cnt1[x]++;
    }

    for (int i = 0; i < 3; i++) {
        char c;
        cin >> c;
        cnt2[c]++;
    }

    vector<int> fact(5);
    fact[0] = 1;
    for (int i = 1; i < 5; i++) fact[i] = fact[i - 1] * i;

    int c1 = fact[3];
    int c2 = fact[3];

    for (auto c : cnt1) c1 /= fact[c.second];
    for (auto c : cnt2) c2 /= fact[c.second];

    cout << c1 * c2;
    return 0;
}

