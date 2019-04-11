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

vector<int> a[26];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i++) a[s[i] - 'a'].pub(i);
    int ans = -1;

    for (int i = 0; i < 26; i++){
        for (int j = 1; j < a[i].size(); j++){
            int val = a[i][j] - a[i][j - 1];
            if (ans == -1) ans = val
            else ans = min(ans, val);
        }
    }

    if (ans == -1) ans = 0;
    cout << ans;
    return 0;
}
