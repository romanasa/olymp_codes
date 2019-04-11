#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

const int C = 20;
int cur[C], val[C];

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#endif

    vector<int> pr;
    for (int x = (int)1e9; (int)pr.size() < C; x++) {
        if (prime(x)) pr.push_back(x);
    }

    string s;
    cin >> s;
    for (int j = 0; j < C; j++) {
        cur[j] = 0;
        for (int i = 0; i < (int)s.size(); i++) cur[j] = (1ll * cur[j] * 10 + s[i] - '0') % pr[j];
    }

    for (int i = 0; i < C; i++) val[i] = 1;

    for (int x = 1; ; x++) {
        for (int j = 0; j < C; j++) val[j] = 1ll * val[j] * x % pr[j];

        int ok = 1;
        for (int j = 0; j < C; j++) ok &= (val[j] == cur[j]);
        if (ok) { cout << x; return 0; }
    }
    return 0;
}


