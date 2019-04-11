#include <bits/stdc++.h>

#define x first
#define y second
#define mp make_pair
#define pub push_back

using namespace std;

typedef long long ll;

vector<string> a;

bool step(int x){
    int cnt = 0;
    for (int i = 0; i < 30; i++) if ((x >> i) & 1) cnt++;
    return cnt == 1;
}

string helpGovno(int x){
    string ans;
    if (x == 0) ans += (char)('a' + x);
    while(x){
        ans += (char)('0' + x % 10);
        x /= 10;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

string govno(int a, int b){
    string ans;
    ans = helpGovno(a) + ' ' + helpGovno(b);
    return ans;
}

vector<string> ans;

int solve(vector<pair<int, int> > t){
    //for (auto c : t) cout << c.x << ' ' << c.y << endl;
    //cout << endl;
    int cnt = 0;
    for (auto c : t) if (c.x > 0) cnt++;
    if (cnt == 1){
        int uk = ans.size();
        for (int i = 0; i < t.size(); i++) if (t[i].x){
            ans.pub(a[i]);
        }
        return uk;
    } else {
        int sum = 0;
        vector<pair<int, int> > t1, t2;

        for (int i = 0; i < t.size(); i++) t1.pub(mp(0, t[i].y / 2)), t2.pub(mp(0, t[i].y / 2));

        for (int i = 0; i < t.size(); i++){
            int now = min(t[i].x, t[i].y / 2 - sum);
            sum += now;
            t1[i].x = now;
            t2[i].x = t[i].x - now;
        }

        int p1 = solve(t1);
        int p2 = solve(t2);
        int uk = ans.size();
        ans.pub(govno(p1 + 1, p2 + 1));
        return uk;
    }
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s;
    cin >> s;
    string now;
    s += '-';
    for (char c : s){
        if (c == '-'){
            a.push_back(now);
            now = "";
        } else {
            now += c;
        }
    }
    vector<pair<int, int> > t;
    int ma = 0;
    for (int i = 0; i < a.size(); i++){
        int x, y;
        char c;
        cin >> x >> c >> y;
        int tmp = __gcd(x, y);
        x /= tmp;
        y /= tmp;
        if (!step(y)) cout << "No solution", exit(0);
        ma = max(ma, y);
        t.push_back(mp(x, y));
    }
    for (int i = 0; i < t.size(); i++){
        int need = ma / t[i].y;
        t[i].x *= need;
        t[i].y = ma;
    }
    solve(t);
    cout << ans.size() << "\n";
    for (auto c : ans) cout << c << "\n";
}
