#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

const int dd = (int)1e6 + 7;

int z[57];
int nxt[dd];
string s;

double calc(int l, int r) {

    //err("l = %d, r = %d\n", l, r);

    if (r - l == 2) return z[1];

    int tp = 0;
    vector<double> cur;

    for (int i = l + 1; i < r; ) {
        cur.push_back(calc(i, nxt[i]));
        i = nxt[i] + 1;

        if (tp == 0) {
            if (s[i] == '+') tp = 1;
            else tp = 2;
        }

        i++;
    }

    if (tp == 1) {
        double res = 0;
        for (auto c : cur) res += c;
        return min(res, 1.0 * z[(int)cur.size()]);
    } else {

        int len = (int)cur.size();
        double T = z[len];
        double res = 1;

        sort(cur.begin(), cur.end());

        //err("cur = "); for (auto c : cur) err("%.2f, ", c); err("\n");

        for (auto c : cur) {
            if (c * len >= T) res *= T / len;
            else {
                T -= c;
                len--;
                res *= c;
            }
        }
        return res;
    }
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> z[i];

    getline(cin, s);
    getline(cin, s);

    vector<int> st;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') st.push_back(i);
        if (s[i] == ')') {
            nxt[st.back()] = i;
            st.pop_back();
        }
    }
    cout.precision(10);
    cout << fixed << calc(0, (int)s.size() - 1);
    return 0;
}
