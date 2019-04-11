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

int main() {
    freopen("01", "r", stdin);
    freopen("03", "w", stdout);
    //freopen("meeting.in", "r", stdin);
    //freopen("meeting.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);

    for (db pos = 0; pos < 360; pos += 0.01){
        db now = 0;

        for (int i = 0; i < n; i++){
            now += min(abs(pos - a[i]), 360 - abs(pos - a[i]));
        }

        if (now < ans){
            ans = now;
            ansPos = pos;
        }
    }

    cout.precision(10);
    if (ansPos == -1) assert(0);
    cout << fixed << ans;
}
