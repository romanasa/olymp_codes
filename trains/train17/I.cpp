#include <bits/stdc++.h>

#define pub push_back

using namespace std;

typedef long long ll;

const int mod = (int)1e9 + 7;

const ll MAXVAL = (ll)1e18 + 7;

bool canMult(ll a, ll b){
    ll can = MAXVAL / a;
    return b <= can;
}

int add(int &a, int  b){
    a += b;
    if (a >= mod) a -= mod;
}

int dp[61][101][53];

#define mp make_pair

map<pair<pair<ll, ll>, ll>, int> was;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    int tt;
    cin >> tt;
    while(tt--){
        ll n, k;
        int len;
        cin >> n >> k >> len;
        if (was.find(mp(mp(n, k), len)) != was.end()){
            cout << was[mp(mp(n, k), len)] << "\n";
            continue;
        }
        vector<ll> t;
        while(n){
            t.pub(n % k);
            n /= k;
        }
        ll sum = 0;
        for (ll c : t) sum += c;
        if (sum > len){
            cout << "0\n";
            continue;
        }

        //for (ll c : t) cout << c << ' ';
        //cout << endl;

        for (int i = 0; i < 61; i++) for (int j = 0; j < 101; j++) for (int s = 0; s < 53; s++) dp[i][j][s] = 0;

        dp[0][0][0] = 1;

        for (int i = 0; i < t.size(); i++){
            for (int j = 0; j <= len; j++){
                for (int per = 0; per <= len / k + 1; per++) if (dp[i][j][per]){
                    //cout << i << ' ' << j << ' ' << per << endl;
                    int st = (t[i] - per) % k;
                    if (st < 0) st += k;
                    for (int w = st; w <= len - j; w += k){
                        int val2 = (per + w) / k;
                        add(dp[i + 1][j + w][val2], dp[i][j][per]);
                    }
                }
            }
        }

        was[mp(mp(n, k), len)] = dp[t.size()][len][0];
        cout << dp[t.size()][len][0] << "\n";
    }
}
