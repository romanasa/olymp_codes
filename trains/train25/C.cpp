#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define mp make_pair
#define pub push_back

typedef long long ll;

#define TASK "dwarfs"

int n, s, t;
vector<int> g[200007];
int func[200007];
vector<int> st, need;
int gg[200007];
void dfs(int v, int pred){
    st.pub(v);
    if (v == t) need = st;
    for (int to : g[v]) if (to != pred) dfs(to, v);
    st.pop_back();
}

bool was[200007];
int calcMa(int v, int pred){
    int ans = 0;
    for (int to : g[v]) if (!was[to] && to != pred){
        ans = max(ans, calcMa(to, v));
    }
    return ans + 1;
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
    for (int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].pub(b);
        g[b].pub(a);
    }
    cin >> s >> t;
    s--; t--;
    dfs(s, -1);
    for (int x : need) was[x] = 1;
    for (int i = 0; i < need.size(); i++) func[i] = calcMa(need[i], -1);
    int ans = 0;
    for (int i = (int)need.size() - 1; i >= 0; i--){
        int val = func[i] + (int)need.size() - i - 1;
        gg[i] = val;
        if (i != (int)need.size() - 1) gg[i] = max(gg[i], gg[i + 1]);
    }
    int my = 0;
    for (int i = 0; i < (int)need.size() - 1; i++){
        int val = func[i] + i;
        my = max(my, val);
        ans = max(ans, min(my, gg[i + 1]));
    }
    cout << ans;
    return 0;
}

