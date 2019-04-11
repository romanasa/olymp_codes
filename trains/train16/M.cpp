#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)2e7 + 1;
const int maxC = (int)1e7 + 1;
 
bitset<dd> F;
ll cur[maxC];
 
int main() {
    ll L, R, D;
    cin >> L >> R >> D;
    F[0] = F[1] = 1;
 
    ll ans = 0;
 
    for (ll i = 2; i * i <= R; i++) {
        if (F[i]) continue;
        for (ll j = i * i; j < maxC; j += i) F[j] = 1;
        
        ll st = (L + i - 1) / i * i;
        if (st > maxC) for (ll j = st; j <= R; j += i) F[j - L + maxC] = 1;
    }
    
    ans = 0;
    int ind = 0;
    for (ll j = L; j <= R; j++) if (F[j - L + maxC] == 0) cur[ind++] = j;
    int j = 0;
    for (int i = 0; i < ind; i++) {
        while (j < i && cur[i] - cur[j] > D) j++;
        ans += i - j;
    }
    cout << ans << "\n";
    return 0;
}