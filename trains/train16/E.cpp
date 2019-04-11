#include <bits/stdc++.h>

using namespace std;

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

int pos[200007];

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

int sp[20][200007];
int gg[200007];

int getSp(int l, int r){
    int lvl = gg[r - l + 1];
    return min(sp[lvl][l], sp[lvl][r - (1 << lvl) + 1]);
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

string s;

int getLeft(int v, int len){
    int vl = -1, vr = v;
    while(vl + 1 < vr){
        int vm = (vl + vr) >> 1;
        if (getSp(vm, v - 1) >= len)
            vr = vm;
        else
            vl = vm;
    }
    return vr;
}

int getRight(int v, int len){
    int vl = v, vr = s.size();
    while(vl + 1 < vr){
        int vm = (vl + vr) >> 1;
        if (getSp(v, vm - 1) >= len)
            vl = vm;
        else
            vr = vm;
    }
    return vl;
}

int getFunc(int v){
    int vl = 0, vr = v + 1;
    //if (v == 2){
    //    cout << pos[v] << endl;
    //    cout << getLeft(pos[v], 1) << endl;
    //    cout << getRight(pos[v], 1) << endl;
    //    exit(0);
    //}
    while(vl + 1 < vr){
        int vm = (vl + vr) >> 1;
        int left = getLeft(pos[v], vm);
        int right = getRight(pos[v], vm);
        if (tt.get(0, 0, (int)s.size() - 1, left, right) <= v - vm)
            vl = vm;
        else
            vr = vm;
    }
    //cout << v << ' ' << vl << endl;
    return vl;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    cin >> s;

    auto p = build(s);
    reverse(p.begin(), p.end());
    p.pop_back();
    reverse(p.begin(), p.end());
    for (int i = 0; i < p.size(); i++) pos[p[i]] = i;
    auto t = getLcp(s, p);

    for (int i = 2; i < 200007; i++) gg[i] = gg[i / 2] + 1;
    for (int lvl = 0; lvl < 20; lvl++){
        for (int l = 0, r = (1 << lvl) - 1; r < t.size(); l++, r++){
            if (lvl == 0){
                sp[0][l] = t[l];
            } else {
                sp[lvl][l] = min(sp[lvl - 1][l], sp[lvl - 1][r - (1 << (lvl - 1)) + 1]);
            }
        }
    }

    //for (int i = 0; i < p.size(); i++) cout << p[i] << ' ';
    //cout << endl;
    //for (int i = 0; i < t.size(); i++) cout << t[i] << ' ';
    //cout << endl;

    int ans = 0;
    int uk = 0;

    set<int> se;

    for (int i = 0; i < s.size(); i++) tt.up(0, 0, (int)s.size() - 1, i, INF);

    while(1){
        if (uk == s.size()) break;

        int to = max(uk + getFunc(uk), uk + 1);

        ans++;
        for (int i = uk; i < to; i++) tt.up(0, 0, (int)s.size() - 1, pos[i], i);
        uk = to;
    }

    cout << ans;
    return 0;
}
