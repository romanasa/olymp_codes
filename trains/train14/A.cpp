#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll getSum(int len){
    if (len == 1) return 9;
    ll ans = 81; len -= 2;
    while(1){
        if (len == 0) break;
        if (len == 1){
            ans *= (ll)10;
            break;
        }
        ans *= (ll)90;
        len -= 2;
    }
    return ans;
}

vector<int> q;
ll dp[20][20][3][3];

ll calc(int l, int r, int w1, int w2){
    if (dp[l][r][w1 + 1][w2 + 1] != -1) return dp[l][r][w1 + 1][w2 + 1];
    if (l > r){
        if (w1 == -1) return 1;
        if (w1 == 0 && w2 == -1) return 1;
        return 0;
    } else if (l == r){
        ll ans = 0;
        for (int c1 = 0 + (l == 0); c1 <= 9; c1++){
            int t1 = w1;
            if (t1 == 0){
                if (c1 > q[l]) t1 = 1;
                else if (c1 < q[l]) t1 = -1;
            }
            ans += calc(l + 1, r, t1, w2);
        }
        dp[l][r][w1 + 1][w2 + 1] = ans;
        return ans;
    } else {
        ll ans = 0;
        for (int c1 = 0 + (l == 0); c1 <= 9; c1++) for (int c2 = 0; c2 <= 9; c2++) if (c1 != c2){
            int t1 = w1, t2 = w2;
            if (t1 == 0){
                if (c1 > q[l]) t1 = 1;
                else if (c1 < q[l]) t1 = -1;
            }
            if (c2 > q[r]){
                t2 = 1;
            } else if (c2 < q[r]){
                t2 = -1;
            }
            ans += calc(l + 1, r - 1, t1, t2);
        }
        dp[l][r][w1 + 1][w2 + 1] = ans;
        return ans;
    }
}

ll getDp(ll val){
    q.clear();
    while(val){
        q.push_back(val % 10);
        val /= 10;
    }
    reverse(q.begin(), q.end());
    for (int i = 0; i < 20; i++) for (int j = 0; j < 20; j++) for (int w1 = 0; w1 < 3; w1++) for (int w2 = 0; w2 < 3; w2++) dp[i][j][w1][w2] = -1;
    return calc(0, (int)q.size() - 1, 0, 0);
}

ll getFunc(ll val){
    if (val <= 1) return 0;
    int len = 0;
    ll cop = val;
    while(cop){
        len++;
        cop /= 10;
    }
    ll ans = getDp(val);
    for (int i = 1; i < len; i++) ans += getSum(i);
    return ans;
}

int main(){
    freopen("antipal.in", "r", stdin);
    freopen("antipal.out", "w", stdout);
    long long l, r;
    cin >> l >> r;

    cout << getFunc(r + 1) - getFunc(l);
}
