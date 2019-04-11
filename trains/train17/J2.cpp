#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> pf(string s) {
    int n = (int)s.size();
    vector<int> p(n);

    for (int i = 1; i < n; i++) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }
    return p;
}

vector<int> zf(string s) {
    int n = (int)s.size();
    vector<int> z(n);

    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

vector<int> p, z;
map<int, string> Q;

int calc(string s) {
    int n = (int)s.size();

    //for (int i = 0; i < n; i++) cout << p[i] << " "; cout << "\n";
    //for (int i = 0; i < n; i++) cout << z[i] << " "; cout << "\n";

    set<string> S;
    for (int i = p[n - 1]; i > 0; i = p[i - 1]) {

        auto it = Q.find(i);
        if (it != Q.end()) {
            S.insert(it->second);
            break;
        }

        //cout << "i = " << i << "\n";
        string cur;

        //cout << i << " ";

        int ind = -1;
        for (int j = 0; j <= i; j++) {
            if (j + z[j] >= i) {
                ind = j;
                break;
            }
            if (j < i) cur += s[j];
        }
        assert(ind != -1);

        Q[i] = cur;
        S.insert(cur);
    }
    return (int)S.size();
}

int calc2(string cur) {
    p = pf(cur), z = zf(cur);
    Q.clear();

    int curc = 0;

    string s;
    for (int i = 0; i < (int)cur.size(); i++) {
        s += cur[i];
        curc += calc(s);
    }

    return curc;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN

    //cout << calc(".X..X..X..");
    //return 0;

    int n;
    cin >> n;

    int ans = -1;
    string ansS;

    for (int msk = 0; msk < (1 << n); msk++) {
        string cur;
        for (int i = 0; i < n; i++)
            if ((msk >> i) & 1) cur += '.';
            else cur += 'X';

        int curc = calc2(cur);
        if (curc > ans) {
            ans = curc, ansS = cur;
        }
    }
    cout << ansS << "\n";
    cout << ans << "\n";
    return 0;
}


