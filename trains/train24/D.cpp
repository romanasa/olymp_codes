#include <bits/stdc++.h>
//#define _GLIBCXX_DEBUG
using namespace std;

#define mp make_pair
#define pub push_back
#define x first
#define y second

typedef long long ll;

#define TASK "highways"

struct pt {
    ll x, y;

    pt() {}
    pt(ll x, ll y): x(x), y(y) {}
    pt(pt A, pt B): x(B.x - A.x), y(B.y - A.y) {}

    double dist() { return sqrt(x * x + y * y); }

    ll operator * (pt B) { return x * B.x + y * B.y; }
    ll operator % (pt B) { return x * B.y - y * B.x; }

    pt operator- (pt nxt) const { return pt(x - nxt.x, y - nxt.y); }
};

int n;
pair<string, pt> a[1555];
vector<int> g[1555];
int w[1555];
int pred[1555];

void dfs(int v, int p){
    w[v] = 1;
    pred[v] = p;
    for (int to : g[v]) if (to != p){
        dfs(to, v);
        w[v] += w[to];
    }
    //cout << "----" << v << ' ' << w[v] << endl;
}

string ans[1555];

pair<pt, int> gg;

bool cmp(pair<pt, int> a, pair<pt, int> b){
    auto now1 = a.x - gg.x;
    auto now2 = b.x - gg.x;
    return (now1 % now2) < 0;
}

void calc(int v, vector<pair<pt, int> > t, pair<pt, int> st){
    ans[v] = a[st.y].x;
    if (g[v].size() == 0) return;
    gg = st;
    sort(t.begin(), t.end(), cmp);
    int pos = 0;

    /*cout << v << ' ' << st.x.x << ' ' << st.x.y << endl;

    cout << endl;
    for (int i = 0; i < t.size(); i++) cout << t[i].x.x << ' ' << t[i].x.y << endl;

    cout << endl;*/

    for (int i = 0; i < g[v].size(); i++) if (g[v][i] != pred[v]){
        vector<pair<pt, int> > ww;
        auto tmp = t[pos++];
        for (int j = 0; j < w[g[v][i]] - 1; j++) ww.pub(t[pos++]);
        calc(g[v][i], ww, tmp);
    }
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second.x >> a[i].second.y;
    }
    for (int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    pair<ll, ll> ma = make_pair(1e9, 1e9);

    for (int i = 0; i < n; i++) ma = min(ma, make_pair(a[i].second.x, a[i].second.y));

    vector<pair<pt, int> > t;
    pt st; int kk;
    for (int i = 0; i < n; i++) if (ma == make_pair(a[i].second.x, a[i].second.y)) st = a[i].y, kk = i; else t.push_back(mp(a[i].y, i));

    dfs(0, -1);

    calc(0, t, mp(st, kk));

    for (int i = 0; i < n; i++) cout << ans[i] << "\n";
}

