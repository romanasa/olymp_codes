#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define TASK "fence"

ll n, k;
ll a[100007];

bool can(ll val){
    if (a[0] < val) return 0;
    ll was = 0;
    for (int i = 0; i < n; i++){
        ll now = a[i] - was;
        if (now >= val){
            was = a[i];
        } else was += val;
    }
    return was <= k;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    ll vl = 0, vr = 1e9 + 7;
    while(vl + 1 < vr){
        ll vm = (vl + vr) >> 1;
        if (can(vm))
            vl = vm;
        else
            vr = vm;
    }
    cout << vl;
    return 0;
}

