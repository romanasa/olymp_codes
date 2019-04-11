#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define mp make_pair
#define pub push_back

typedef long long ll;

#define TASK "travel"

int n, m, k;
char a[555][555];
int path[555][555];
int govno[555][555];
pair<pair<int, int>, int> p[555][555];
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
char cc[] = {'S', 'E', 'N', 'W'};
char ccc[] = {'N', 'W', 'S', 'E'};

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN
    cin >> m >> n >> k;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> a[i][j];

    int stx, sty;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (a[i][j] == 'V') stx = i, sty = j;

    deque<pair<int, int> > st;
    st.pub(mp(stx, sty));

    for (int i = 0; i < 555; i++) for (int j = 0; j < 555; j++) p[i][j] = mp(mp(-1, -1), -1);
    p[stx][sty] = mp(mp(-2, -2), -2);

    while(st.size()){
        auto now = st.front();
        st.pop_front();
        for (int i = 0; i < 4; i++){
            int nx = now.x + dx[i];
            int ny = now.y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && p[nx][ny].x.x == -1){
                p[nx][ny] = mp(now, i);
                if (a[nx][ny] == 'A') st.pub(mp(nx, ny)), govno[nx][ny] = govno[now.x][now.y];
                else st.push_front(mp(nx, ny)), govno[nx][ny] = govno[now.x][now.y] + 1;
                path[nx][ny] = path[now.x][now.y] + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (a[i][j] == 'T') govno[i][j]--;

    int ans = 1e9;
    pair<int, int> pos;
    int ww, ff;

    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (a[i][j] == 'T'){
        bool was = 0;
        int fff;
        for (int s = 0; s < 4; s++){
            int nx = i + dx[s];
            int ny = j + dy[s];
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && a[nx][ny] == 'T'){
                was = 1;
                fff = s;
            }
        }
        int dist = path[i][j] - 1;
        if (!was && govno[i][j] != 0) continue;
        if (was && govno[i][j] >= k) continue;
        int now = dist;
        if (was) now += k - govno[i][j];
        else now += 2 * (k - govno[i][j]) - 1;
        if (now < ans){
            ans = now;
            ww = was;
            ff = fff;
            pos = mp(i, j);
        }
    }

    string s;

    auto gg = pos;
    while(1){
        auto to = p[gg.x][gg.y];
        if (to.x.x == -2) break;
        s += cc[to.y];
        gg = to.x;
    }
    reverse(s.begin(), s.end());

    if (ww){
        bool now = 1;
        for (int it = 0; it < k - 1 - govno[pos.x][pos.y]; it++){
            if (now) s += cc[ff];
            else s += ccc[ff];
            now = !now;
        }
    } else {
        int goo = -1;
        for (int s = 0; s < 4; s++){
            int nx = pos.x + dx[s];
            int ny = pos.y + dy[s];
            if (nx >= 0 && ny >= 0 && nx < n && ny < m){
                goo = s;
            }
        }
        for (int it = 0; it < k - 1; it++){
            s += cc[goo];
            s += ccc[goo];
        }
    }
    cout << s;
    assert(s.size() == ans);
    return 0;
}

