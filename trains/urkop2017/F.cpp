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
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> a[i][j];
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) b[i]--;
    bool ff = 1;
    for (int i = 0; i < n; i++) if (i != b[i]) ff = 0;
    if (ff) cout << 0, exit(0);


    vector<int> ord;
    for (int j = 0; j < m; j++){
        bool can = 1;
        for (int i = 1; i < n; i++) if (a[b[i]][j] < a[b[i - 1]][j]){
            can = 0;
            break;
        }
        if (can){
            ord.pub(j);
        }
    }
    if (ord.size() == 0) cout << -1, exit(0);


    int pos = 0;
    vector<int> tmp;
    for (int i = 0; i < n; i++) tmp.pub(b[i]);
    q[pos][0] = tmp;
    sz[0] = 1;

    for (int i = 0; i < ord.size(); i++){
        int v = ord[i];
        int to = pos ^ 1;
        sz[to] = 0;
        for (int j = 0; j < sz[pos]; j++){
            int gg = 0;
            for (int s = 0; s < q[pos][j].size(); s++) w[gg++] = mp(a[ q[pos][j][s] ][v], s);
            sort(w, w + gg);
            //for (int s = 0; s < 3; s++) cout << w[s].x << ' ' << q[pos][j][w[s].y] << endl;
            vector<int> now;
            now.pub(q[pos][j][w[0].y]);
            for (int s = 1; s < gg; s++){
                if (w[s].x == w[s - 1].x){
                    now.pub(q[pos][j][w[s].y]);
                } else {
                    q[to][sz[to]++] = now;
                    now.clear();
                    now.pub(q[pos][j][w[s].y]);
                }
            }
            q[to][sz[to]++] = now;
        }

        pos = to;

        //cout << sz[pos] << endl;
        //for (int i = 0; i < sz[pos]; i++){
        //    for (int x : q[pos][i]) cout << x << ' ';
        //    cout << endl;
        //}
        //exit(0);
    }

    set<pair<int, pair<int, int> > > se;

    for (int i = 0; i < sz[pos]; i++) se.insert(mp(q[pos][i][0], mp(i, 0)));

    for (int i = 0; i < n; i++){
        auto now = *se.begin();
        if (now.x != i) cout << -1, exit(0);
        se.erase(se.begin());
        if (now.y.y + 1 < q[pos][now.y.x].size()) se.insert(mp(q[pos][now.y.x][now.y.y + 1], mp(now.y.x, now.y.y + 1)));
    }

    vector<int> qq;
    for (int i = 0; i < n; i++) qq.pub(i);
    for (auto c : ord){
        qq = prim(qq, c);
    }
    for (int i = 0; i < qq.size(); i++) if (qq[i] != b[i]) assert(0);
    //for (int x : qq) cout << x + 1 << ' ';
    //cout << endl;

    cout << ord.size() << "\n";
    //reverse(all(ord));
    //srand(time(NULL));
    //random_shuffle(all(ord));
    //reverse(all(ord));
    for (int x : ord) cout << x + 1 << "\n";
}
