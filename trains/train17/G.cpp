#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

set<string> A, B;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        if (s.back() == '+') {
            s.pop_back();

            set<string> curS;
            for (int l = 0; l < (int)s.size(); l++) {
                string cur;
                for (int r = l; r < (int)s.size(); r++) {
                    cur += s[r];
                    curS.insert(cur);
                }
            }

            if (i) {
                set<string> nA;
                for (auto c : curS) if (A.count(c))
                    nA.insert(c);
                A = nA;
            } else A = curS;
        } else {
            for (int l = 0; l < (int)s.size(); l++) {
                string cur;
                for (int r = l; r < (int)s.size(); r++) {
                    cur += s[r];
                    B.insert(cur);
                }
            }
        }

        string ans = "-1";
        for (auto c : A) if (!B.count(c)) {
            if (ans == "-1" || ans.size() > c.size()) ans = c;
        }
        cout << ans << "\n";
    }
    return 0;
}

