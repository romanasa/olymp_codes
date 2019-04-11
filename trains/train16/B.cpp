#include <bits/stdc++.h>

using namespace std;

const int dd = 1007;
double need[dd][dd];

int n, w;

bool check(int x, vector<int> &b) {
    if (x * (x + 1) / 2 > n) return false;

    vector<double> A;
    for (int it = 1; it <= x; it++) {
        for (int i = 0; i < it; i++) A.push_back(need[it][i]);
    }

    sort(A.rbegin(), A.rend());

    multiset<int> S;
    for (int i = 0; i < n; i++) S.insert(b[i]);

    for (auto c : A) {
        auto it = S.lower_bound((int)(c + 0.5));
        if (it == S.end()) return false;
        S.erase(it);
    }
    return true;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    cin >> n >> w;

    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];

    sort(b.begin(), b.end());

    int sum = 0;
    for (int it = 1; sum <= n; it++) {
        for (int i = 0; i < it; i++) {
            need[it][i] = 0;
            if (i > 0) need[it][i] += (need[it - 1][i - 1] + w) / 2;
            if (i < it - 1) need[it][i] += (need[it - 1][i] + w) / 2;
            //cout << need[it][i] << ", ";
        }
        //cout << endl;
        sum += it;
    }

    int l = 0, r = n;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (check(m, b)) l = m;
        else r = m;
    }
    cout << l << "\n";
    return 0;
}
