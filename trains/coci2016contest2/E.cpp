#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)1e6 + 7;
ll p[dd], need[dd], h[dd];
int pr[dd], r[dd];
int a[dd], b[dd];
 
//const int mod = (int)1e9 + 7;
const int mod = 0;
const ll pw = 1234577;
 
int get(int v) { return v == pr[v] ? v : pr[v] = get(pr[v]); }
 
ll ans = 0;
unordered_map<ll, int> cnt;
 
void upd(int pos, int root, int sgn) {
    h[root] += sgn * p[a[pos]];
    if (h[root] < 0) h[root] += mod;
    if (h[root] >= mod) h[root] -= mod;
}
 
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
     
    p[0] = 1;
    for (int i = 1; i < dd; i++) p[i] = p[i - 1] * pw;
 
    int n, m;
    cin >> n >> m;
     
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        b[i] = a[i];
    }
     
    sort(b, b + n); 
     
    for (int i = 0; i < n; i++) need[i] = p[b[i]];
    for (int i = 0; i < n; i++) h[i] = p[a[i]];  
    for (int i = 0; i < n; i++) pr[i] = i, r[i] = 1;
     
    for (int i = 0; i < n; i++) {
        ll diff = h[i] - need[i];
        if (diff < 0) diff += mod;
         
        //if (diff) 
            //err("i = %d, diff = %d\n", i, diff);
            if (diff) ans += cnt[mod - diff]; cnt[diff]++;
    }
     
    int comp = n;
     
    for (int i = 0; i < m; i++) {
        int tp;
        cin >> tp;
         
        //err("tp = %d\n", tp);
         
        if (tp == 1) {
            int aa, b;
            cin >> aa >> b;
            aa--, b--;
             
            int ra = get(aa), rb = get(b);
             
            ll diffa = h[ra] - need[ra]; if (diffa < 0) diffa += mod;
            ll diffb = h[rb] - need[rb]; if (diffb < 0) diffb += mod;
             
            //if (diffa) 
                cnt[diffa]-=1ll * r[ra]; if (diffa) ans -= 1ll * r[ra] * cnt[mod - diffa];
             
            //if (diffb) 
                cnt[diffb]-=1ll * r[rb]; if (diffb) ans -= 1ll * r[rb] *cnt[mod - diffb];
             
            upd(aa, ra, -1);
            upd(b, rb, -1);
             
            swap(a[aa], a[b]);
             
            upd(aa, ra, 1);
            upd(b, rb, 1);
             
            diffa = h[ra] - need[ra]; if (diffa < 0) diffa += mod;
            diffb = h[rb] - need[rb]; if (diffb < 0) diffb += mod;
             
            //if (diffa)
                if (diffa) ans += 1ll * r[ra] *cnt[mod - diffa]; cnt[diffa] += 1ll * r[ra];
             
            //if (diffb) 
                if (diffb) ans += 1ll * r[rb] *cnt[mod - diffb]; cnt[diffb] += 1ll * r[rb];
             
        } else if (tp == 2) {
            int a, b;
            cin >> a >> b;
            a--, b--;
             
            int ra = get(a), rb = get(b);
            if (ra == rb) continue;
             
            comp--;
             
            ll diffa = h[ra] - need[ra]; if (diffa < 0) diffa += mod;
            ll diffb = h[rb] - need[rb]; if (diffb < 0) diffb += mod;
             
            //if (diffa) 
                cnt[diffa]-=1ll * r[ra]; if (diffa) ans -= 1ll * r[ra] * cnt[mod - diffa];
             
            //if (diffb) 
                cnt[diffb]-=1ll * r[rb]; if (diffb) ans -= 1ll * r[rb] *cnt[mod - diffb];
             
            a = ra, b = rb;
             
            if (r[b] > r[a]) swap(a, b);
             
            pr[b] = a;
            r[a] += r[b];
             
            need[a] += need[b]; if (need[a] >= mod) need[a] -= mod;
            h[a] += h[b]; if (h[a] >= mod) h[a] -= mod;
             
            ll diff = h[a] - need[a];
            if (diff < 0) diff += mod;
             
            //if (diff) 
                if (diff) ans += 1ll * r[a] * cnt[mod - diff]; cnt[diff]+= r[a];
                 
        } else if (tp == 3) {
            if (cnt[0] == n) cout <<"DA\n";
            else cout << "NE\n";
        } else {
            cout << ans << "\n";
        }
    }
    return 0;
}