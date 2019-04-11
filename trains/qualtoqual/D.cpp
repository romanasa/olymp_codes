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

bool ok(char a, char b, char c) {
    return a != c && a != b && b != c;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    string s;
    cin >> s;

    for (int i = 0; i < (int)s.size(); i++) {
        if (i + 3 <= (int)s.size() && ok(s[i], s[i + 1], s[i + 2])) {
            cout << 'C';
            i += 2;
        } else if (s[i] == 'R') cout << 'S';
        else if (s[i] == 'L') cout << 'H';
        else if (s[i] == 'B') cout << 'K';
    }
    return 0;
}

