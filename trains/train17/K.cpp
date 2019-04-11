#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int pos[200007];
int good[200007];

vector<int> build(string s) {
    s += (char)1;

    int n = (int)s.size();

    vector<pair<int, int> > S;
    vector<int> col(n);
    for (int i = 0; i < n; i++) S.push_back({ s[i], i });

    sort(S.begin(), S.end());

    int cc = 0;
    for (int i = 0; i < n; i++) {
        if (i && S[i - 1].first != S[i].first) cc++;
        col[S[i].second] = cc;
    }

    for (int L = 1; L < n; L *= 2) {
        vector<pair<pair<int, int>, int> > J;
        for (int i = 0; i < n; i++) {
            int nt = (i + L);
            if (nt >= n) nt -= n;
            J.push_back({ { col[i], col[nt] }, i});
        }
        sort(J.begin(), J.end());
        cc = 0;
        for (int i = 0; i < n; i++) {
            if (i && J[i].first != J[i - 1].first) cc++;
            col[J[i].second] = cc;
        }
    }

    vector<int> A(n);
    for (int i = 0; i < n; i++) A[col[i]] = i;
    return A;
}


vector<int> getLcp(string &s, vector<int> &g){
    vector<int> ans(s.size());
    int k = 0;
    for (int i = 0; i < s.size(); i++){
        if (k > 0) k--;
        int uk = pos[i];
        if (uk == (int)g.size() - 1){
            ans[uk] = 0;
            continue;
        }
        while(i + k < (int)s.size() && g[uk + 1] + k < (int)s.size() && s[i + k] == s[g[uk + 1] + k]) k++;
        ans[uk] = k;
    }
    return ans;
}

int sp[18][200007];
int sp2[18][200007];
int gg[200007];
int num[200007];
int len[200007];

set<int> Minus;
set<cond> S;
multiset<pair<int, int> > T;
int n, m;

int getSp(int l, int r) {
    if (l == r) return len[l];
    r--;
    int lvl = gg[r - l + 1];
    return min(sp[lvl][l], sp[lvl][r - (1 << lvl) + 1]);
}

int getI(int l, int r) {
    int lvl = gg[r - l + 1];
    return min(sp2[lvl][l], sp2[lvl][r - (1 << lvl) + 1]);
}

const int INF = (int)1e9 + 7;

struct tree{
    int t[4 * 200007];

    void up(int v, int vl, int vr, int pos, int val){
        if (vl == vr){
            t[v] = val;
        } else {
            int vm = (vl + vr) >> 1;
            if (pos <= vm){
                up(v * 2 + 1, vl, vm, pos, val);
            } else {
                up(v * 2 + 2, vm + 1, vr, pos, val);
            }
            t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }

    int get(int v, int vl, int vr, int l, int r){
        if (r < vl || l > vr) return INF;
        if (vl >= l && vr <= r) return t[v];
        int vm = (vl + vr) >> 1;
        return min(get(v * 2 + 1, vl, vm, l, r), get(v * 2 + 2, vm + 1, vr, l, r));
    }
} tt;

map<int, int> M[200007];

struct cond {
    int l, r, ind;
};


void upd(cond &cur, int q) {
    if (M[cur.ind].size() < q) return;

    int iL = tt.getLeft(0, 0, m, cur.l, cur.r);
    int iR = tt.getRight(0, 0, m, cur.l, cur.r);

    int cur = getSp(iL, iR);

    auto it = Minus.lower_bound(l);

    int d = 0;

    if (it != Minus.end()) d = max(d, getSp(iR, *it));

    if (it != Minus.begin()) {
        --it;
        d = max(d, getSp(*it, iL));
    }
    if (cur > d) T.insert({ d + 1, getI(iL, iR) });
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string t;

    cin >> n;

    int cur = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        if (s.back() == '+') good[i] = 1, s.pop_back();

        for (int j = cur; j < cur + (int)s.size(); j++) num[j] = i;
        num[cur + (int)s.size()] = n;

        for (int j = cur; j <= cur + (int)s.size(); j++) len[j] = cur + (int)s.size() - j;

        cur += (int)s.size() + 1;

        t += s;
        t += (char)(i + 1);
    }

    auto P = build(t);

    m = (int)P.size();
    for (int i = 0; i < m; i++) pos[P[i]] = i;

    for (int i = 2; i < 200007; i++) gg[i] = gg[i / 2] + 1;
    for (int lvl = 0; lvl < 18; lvl++){
        for (int l = 0, r = (1 << lvl) - 1; r < P.size(); l++, r++){
            if (lvl == 0){
                sp[0][l] = P[l];
            } else {
                sp[lvl][l] = min(sp[lvl - 1][l], sp[lvl - 1][r - (1 << (lvl - 1)) + 1]);
            }
        }
    }

    for (int lvl = 0; lvl < 18; lvl++){
        for (int l = 0, r = (1 << lvl) - 1; r < P.size(); l++, r++){
            if (lvl == 0){
                sp[0][l] = num[l];
            } else {
                sp[lvl][l] = min(sp[lvl - 1][l], sp[lvl - 1][r - (1 << (lvl - 1)) + 1]);
            }
        }
    }

    //TODO сделать сеты, закинуть минусы


    auto L = getLcp(t, P);



    for (int i = 0; i < m; i++) {
        if (num[i] == n) continue;
    }



    return 0;
}

