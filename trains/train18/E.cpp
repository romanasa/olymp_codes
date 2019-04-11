#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()
//236695ZVSVG

using namespace std;

typedef long long ll;
typedef double db;

const db pi = atan2(1, 1) * 4;

db b, h, v, a;

db solve(vector<pair<db, db> > a, vector<pair<ll, ll> > t){
    vector<pair<db, db> > q;
    sort(all(a));
    if (a.size() == 0) return 0;
    db uk = 0;
    for (int i = 1; i < a.size(); i++){
        if (a[i].x > a[i - 1].y){
            q.pub(mp(a[uk].x, a[i - 1].y));
            uk = i;
        }
    }
    q.pub(mp(a[uk].x, a[(int)a.size() - 1].y));
    vector<pair<db, ll> > g;

    //for (auto c : q) cout << c.x << ' ' << c.y << endl;
    //exit(0);

    int l = 0, r = 0;

    for (int i = 0; i < t.size(); i++){
        ll ti = t[i].x;
        while(1){
            if (l >= q.size()) break;
            if (q[l].y - ti * v < -b) l++;
            else break;
        }

        while(1){
            if (r >= q.size()) break;
            if (q[r].x - ti * v <= 0) r++;
            else break;
        }

        //cout << "---" << i << ' ' << l << ' ' << r << endl;

        if (l < q.size()) for (int j = l; j < r; j++){
            /// IF
            db myL = max(q[j].x - v * ti, -b);
            db myR = min(q[j].y - v * ti, 0.0);
            //cout << "===" << myL << ' ' << myR << endl;
            //if (myL > myR) assert(0); //?????
            g.pub(mp(myL, -t[i].y));
            g.pub(mp(myR, t[i].y));
        }
    }

    sort(all(g));
    ll ans = 0, bal = 0;
    for (auto c : g){
        bal -= c.y;
        ans = max(ans, bal);
    }
    db sum = 0;
    for (auto c : q) sum += c.y - c.x;
    //cout << ans << ' ' << sum << ' ' << sum/v << ' ' << ans + sum / v << endl;
    //exit(0);
    return ans + sum / v;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> b >> h >> v >> a;
    vector<pair<db, db> > w1, w2;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        if (a < pi / 2){
            db dx = h / tan(a);
            w1.pub(mp(x, x + y));
            w2.pub(mp(x + dx, x + y + dx));
        } else {
            db dx = h * tan(a - pi / 2);
            w1.pub(mp(x, x + y));
            w2.pub(mp(x + dx, x + y + dx));
        }
    }

    //assert(n <= 2);

    cin >> n;

    ll sum = 0;

    vector<pair<ll, ll> > t;
    for (int i = 0; i < n; i++){
        ll x, y;
        cin >> x >> y;
        //x -= sum;
        //sum += y;
        t.pub(mp(x, y));
        //cerr << x << " " << y << endl;
    }
    sort(all(t));

    for (int i = 1; i < t.size(); i++){
        if (t[i].x < t[i - 1].x + t[i - 1].y) assert(0);
    }

    /*vector<pair<ll, ll> > t2;
    int uk = 0;
    for (int i = 1; i < t.size(); i++){
        if (t[i].x > t[i - 1].x + t[i - 1].y) {
            t2.pub(mp(t[uk].x, t[i - 1].x + t[i - 1].y - t[uk].x));
            uk = i;
        }
    }
    t2.pub(mp(t[uk].x, t[(int)t.size() - 1].x + t[(int)t.size() - 1].y - t[uk].x));*/

    cout.precision(10);
    cout << fixed << max(solve(w1, t), solve(w2, t));
}
