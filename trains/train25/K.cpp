#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define mp make_pair
#define pub push_back

typedef long long ll;

#define TASK "virus"

int n, m, k;
char a[111][111];
bool was[111][111];
int block[111][111];
ll ans = 0;
set<pair<ll, ll> > se[11];

int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

ll h1 = 0, h2 = 0;
vector<pair<int, int> > st;
void calc(int v){
    //cout << v << ' ' << last << ' ' << st.size() << ' ' << se[0].size() << endl;
    if (v == 0){
        /*for (int i = 1; i < st.size(); i++){
            cout << st[i].x << ' ' << st[i].y << endl;
        }
        cout << endl;*/
        ans++;
        return;
    }

    int fff = st.size();
    for (int j = 0; j < fff; j++){
        auto c = st[j];
        for (int i = 0; i < 4; i++){
            int nx = c.x + dx[i];
            int ny = c.y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && !was[nx][ny] && !block[nx][ny]){
                was[nx][ny] = 1;
                st.pub(mp(nx, ny));
                calc(v - 1);
                was[nx][ny] = 0;
                st.pop_back();
            }
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && !was[nx][ny]) block[nx][ny]++;
        }
    }
    for (int j = 0; j < fff; j++){
        auto c = st[j];
        for (int i = 0; i < 4; i++){
            int nx = c.x + dx[i];
            int ny = c.y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && !was[nx][ny]){
                block[nx][ny]--;
            }
        }
    }
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> a[i][j];
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (a[i][j] == '*'){
        was[i][j] = 1;
        st.pub(mp(i, j));
    }
    calc(k);
    cout << ans;
    return 0;
}

