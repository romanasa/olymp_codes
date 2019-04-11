#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define TASK "exp"

#define mp make_pair
#define pub push_back
#define x first
#define all(a) a.begin(), a.end()
#define y second

int n;
int color[111];
vector<int> a[111];
bool was[111];
bool add[111];

pair<int, vector<int> > calc(int col){
    for (int i = 0; i < n; i++) was[i] = 0, add[i] = 0;;
    int ans = 0;
    vector<int> pr;
    vector<int> st[2];

    while(1){
        if (pr.size() == n) break;
        for (int i = 0; i < n; i++) if (!add[i]){
            bool ok = 1;
            for (int j = 0; j < a[i].size(); j++) if (!was[a[i][j]]){
                ok = 0;
                break;
            }
            if (ok){
                st[color[i]].pub(i);
                add[i] = 1;
            }
        }
        if (st[col].size() == 0) col ^= 1, ans++;
        for (int x : st[col]) pr.pub(x), was[x] = 1;
        st[col].clear();
    }

    return mp(ans, pr);
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> color[i];
        int sz;
        cin >> sz;
        a[i].resize(sz);
        for (int j = 0; j < sz; j++) cin >> a[i][j];
        for (int j = 0; j < sz; j++) a[i][j]--;
    }
    auto now1 = calc(0);
    auto now2 = calc(1);
    auto now = min(now1, now2);
    cout << now.x << "\n";
    for (int x : now.y) cout << x + 1 << ' ';
}

