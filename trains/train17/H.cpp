#include <bits/stdc++.h>

#define x first
#define y second
#define pub push_back
#define mp make_pair

using namespace std;

typedef long long ll;

int n, m, k;
vector<pair<int, int> > t[100007];
map<pair<int, int>, int> was;
int dd[100007];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < k; i++){
        int sz;
        scanf("%d", &sz);
        t[i].resize(sz);
        for (int j = 0; j < sz; j++) cin >> t[i][j].x >> t[i][j].y;
        for (auto c : t[i]) was[c] = i;
    }
    vector<pair<int, int> > ans;

    vector<int> st;
    int uk = 0;

    for (int i = 0; i < k; i++) if (t[i].size() && t[i].back().y == 1) st.pub(i);

    while(uk < st.size()){
        int v = st[uk++];
        //cout << v << endl;
        ans.pub(t[v].back());
        auto nxt = mp(-1, -1);
        if (t[v].back().y != m) nxt = mp(t[v].back().x, t[v].back().y + 1);
        dd[t[v].back().x]++;
        t[v].pop_back();
        if (t[v].size() && t[v].back().y == dd[t[v].back().x] + 1) st.pub(v);
        if (nxt.x != -1){
            int to = was[nxt];
            if (to != v && t[to].size() && t[to].back() == nxt) st.pub(to);
        }
    }

    if (ans.size() != n * m) cout << "NO", exit(0);

    printf("YES\n");
    for (auto c : ans) printf("%d %d\n", c.x, c.y);
}

