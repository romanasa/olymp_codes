#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()

using namespace std;

typedef long long ll;
typedef double db;

int n, m;
int a[1007][1007];
int b[1007];
pair<int, int> w[1007];

vector<int> q[2][1007];
int sz[2];

vector<int> prim(vector<int> q, int v){
    vector<pair<int, int> > now;
    vector<int> ans;
    for (int i = 0; i < q.size(); i++) now.pub(mp(a[q[i]][v], i));
    sort(all(now));
    for (auto c : now) ans.pub(q[c.y]);
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output2.txt", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> a[i][j];
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) b[i]--;
    bool ff = 1;
    for (int i = 0; i < n; i++) if (i != b[i]) ff = 0;
    if (ff) cout << 1, exit(0);

    vector<int> tt;
    for (int i = 0; i < m; i++) tt.pub(i);
    do{
        vector<int> qq;
        for (int i = 0; i < n; i++) qq.pub(i);
        for (auto c : tt){
            qq = prim(qq, c);
            bool can = 1;
            for (int i = 0; i < qq.size(); i++) if (qq[i] != b[i])can = 0;
            if (can) cout << 1, exit(0);
        }
    } while(next_permutation(all(tt)));
    cout << -1;
}
