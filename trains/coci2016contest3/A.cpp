#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

bool checkname(string s) {
    for (char c : s) if (!isalpha(c)) return false;
    int ok = isupper(s[0]);
    for (int i = 1; i < (int)s.size(); i++) {
        ok &= tolower(s[i]) == s[i];
    }
    return ok;
}

bool check(char c) { return c == '.' || c == '?' || c == '!'; }

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    int n;
    cin >> n;

    string s;
    getline(cin, s);
    getline(cin, s);

    istringstream in(s);

    string t;
    int c = 0;
    while (in >> t) {

        int fin = 0;
        if (check(t.back())) fin = 1, t.pop_back();
        if (checkname(t)) c++;
        if (fin) {
            cout << c << "\n";
            c = 0;
        }
    }
    return 0;
}
