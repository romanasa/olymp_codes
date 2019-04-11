#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll x, y, l, r;
ll val, delta;

ll getSum(ll x){
    return x * (x + 1) / 2;
}

ll getSumFunc(ll k){
    return k * val - delta * getSum(k - 1);
}

 const ll maxVal = (ll)9e18;

bool canMult(ll a, ll b){
    ll now = maxVal / a;
    return b <= now;
}

ll get(ll gr){
    if (gr == 0) return 0;
    if (x == y) return gr / x;
    if (x == 1) return gr;
    val = x - 1;
    delta = y - x;
    ll cnt = (val + delta - 1) / delta;
    ll vl = 0, vr = cnt + 1;
    while(vl + 1 < vr){
        ll vm = (vl + vr) >> 1;
        if (!canMult(vm, y)){
            vr = vm;
            continue;
        }
        ll ri = vm * y;
        ll le = vm * x - (val - (vm - 1) * delta);
        if (le > gr)
            vr = vm;
        else
            vl = vm;
    }
    ll ans = getSumFunc(vl - 1);

    ll ri = vl * y;
    ll le = vl * x;

    ans += val - (vl - 1) * delta - max((ll)0, le - gr - 1);
    return gr - ans;
}

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#else
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    cin >> x >> y >> l >> r;

    cout << get(r) - get(l - 1);
}

