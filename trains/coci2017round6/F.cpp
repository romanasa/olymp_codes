#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

const int dd = 157;

int go[dd], used[dd], c[dd];
int ans[dd];
vector<vector<int> > T[dd];

int cost[dd][dd];
int cur[dd];

int get(vector<int> A) {
    if (A.size() <= 2) return abs(A.back() - A[0]);
    vector<int> d;
    for (int i = 1; i < (int)A.size(); i++) d.push_back(A[i] - A[i - 1]);
    int ans = 0;
    for (int i = 0; i + 1 < (int)d.size(); i++) ans = max(ans, d[i] + d[i + 1]);
    return ans;
}

const int p = 12345677;
const int mod = (int)1e9 + 7;

int n;
int pw[dd];
/*
int geth() {
    int h = 0;
    int sq = 0;
    for (int i = 1; i <= n; i++) {
        int x = cur[i];
        h = (1ll * h * p + x) % mod, sq = (sq + 1ll * x * x) % mod;
    }
    return (h + sq) % mod;
}*/

void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

void sub(int &a, int b) {
    a -= b;
    if (a < 0) a += mod;
}

//unordered_map<int, int> M(1e7);

const int sz = (1 << 23) - 1;

struct hhh {
    int A[sz + 3], B[sz + 3];

    hhh() { fill(A, A + sz + 3, -1); }

    int& operator [](int x) {
        int i = (x&sz);
        for (; A[i] != -1; i = (i + 1) & sz) {
            if (A[i] == x) return B[i];
        }
        A[i] = x, B[i] = -2;
        return B[i];
    }
} M;

int calc(int sum, int h, int last = 1) {
    if (sum == 0) return 0;

    int t = M[h];
    if (t != -2) return t;

    int res = (int)1e9;
    int ind = -1;
    for (int i = last; i <= sum; i++) if (cur[i] > 0) {
        if (ind == -1) ind = i;
        cur[i]--;
        sub(h, pw[i]);
        res = min(res, max(calc(sum - i, h, ind), cost[sum - i][sum - 1]));
        cur[i]++;
        add(h, pw[i]);
    }
    return (M[h] = res);
}

void restore(int sum, int h) {
    if (sum == 0) return;

    int res = M[h];

    for (int i = 1; i <= sum; i++) if (cur[i] > 0) {
        cur[i]--;
        sub(h, pw[i]);
        if (res == max(calc( sum - i, h), cost[sum - i][sum - 1])) {

            int pos = 0;
            for (int j = 0; j < i; j += 2) {
                ans[T[i].back()[pos++]] = c[sum - i + j];
            }
            for (int j = (i - 1) - (i % 2); j > 0; j -= 2)
                ans[T[i].back()[pos++]] = c[sum - i + j];

            T[i].pop_back();
            restore(sum - i, h);
            return;
        }
        cur[i]++;
        add(h, pw[i]);
    }
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif
    pw[0] = 1;
    for (int i = 1; i < dd; i++) pw[i] = 1ll * pw[i - 1] * p % mod;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> go[i];
        go[i]--;
    }

    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        vector<int> cur;
        for (int j = i; !used[j]; j = go[j]) {
            used[j] = 1;
            cur.push_back(j);
        }
        T[(int)cur.size()].push_back(cur);
    }

    //assert(T[n].size() == 1);

    for (int i = 0; i < n; i++) cin >> c[i];
    sort(c, c + n);

    for (int i = 0; i < n; i++) {
        vector<int> cur;
        for (int j = i; j < n; j++) {
            cur.push_back(c[j]);
            cost[i][j] = get(cur);
        }
    }

    int h = 0;
    for (int i = 0; i <= n; i++) {
        cur[i] = T[i].size();
        h = (h + 1ll * T[i].size() * pw[i]) % mod;
    }

    cout << calc(n, h) << "\n";
    restore(n, h);
    for (int i = 0; i < n; i++) cout << ans[i] << " "; cout << "\n";

    return 0;
}
