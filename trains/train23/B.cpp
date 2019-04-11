#include <bits/stdc++.h>

#define ll long long
#define db double
#define x first
#define y second
#define mp make_pair
#define pub push_back

using namespace std;

db ans = 1e30;
db ansPos = -1;

int n;
db a[200007];
vector<pair<db, int> > b;

bool goLeft(db a, db b){
    if (a <= b){
        return b - a < 180;
    } else {
        return b + 360 - a < 180;
    }
}

db sum1 = 0, sum2 = 0;
int k1 = 0, k2 = 0;

void update(db pos){
    //cout << sum1 << ' ' << k1 << ' ' << sum2 << ' ' << k2 << ' ' << pos << endl;
    db now = sum1 - k1 * pos ;
    now += k2 * pos - sum2;
    if (now < ans){
        ans = now;
        ansPos = pos;
    }
}

int main() {
    freopen("01", "r", stdin);
    freopen("02", "w", stdout);
    //freopen("meeting.in", "r", stdin);
    //freopen("meeting.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    for (int i = 0; i < n; i++){
        db ww = a[i] + 180;
        while(ww >= 360) ww -= 360;
        b.pub(mp(a[i], 0));
        b.pub(mp(ww, 1));
    }
    sort(b.begin(), b.end());

    int uk = 0;

    for (int i = 0; i < n; i++) if (goLeft(b[0].x, a[i])){
        sum1 += a[i];
        k1++;
    } else {
        db gg = a[i];
        if (gg > b[0].x) gg -= 360;
        sum2 += gg;
        k2++;
    }

    update(b[0].x);
    for (int i = 0; i < b.size(); i++){
        //cout << "====" << b[i].x << ' ' << b[i].y << endl;
        if (b[i].y == 0){
            k1--;
            sum2 += b[i].x;
            sum1 -= b[i].x;
            k2++;
        } else {
            db pos = b[i].x + 180;
            while(pos >= 360) pos -= 360;
            k1++;
            k2--;
            if (pos > b[i].x){
                sum1 += pos;
                while(pos > b[i].x) pos -= 360;
                sum2 -= pos;
            } else {
                sum2 -= pos;
                while(pos < b[i].x) pos += 360;
                sum1 += pos;
            }
        }
        update(b[i].x);
    }

    cout.precision(10);
    if (ansPos == -1) assert(0);
    cout << fixed << ans;
}
