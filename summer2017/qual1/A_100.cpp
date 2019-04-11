#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
  
typedef long long ll;
 
const int dd = (int)1e6 + 1;
  
int C[dd];
 
ll MN[2 * dd];
ll MX[2 * dd];
  
struct pt { 
    ll x, y; 
    pt() {}
    pt(ll x, ll y): x(x), y(y) {}
      
    pt operator - (pt b) { return pt(x - b.x, y - b.y); }
    pt operator + (pt b) { return pt(x + b.x, y + b.y); }
    ll operator % (pt b) { return x * b.y - y * b.x; }
    ll operator * (pt b) { return x * b.x + y * b.y; }
};
  
vector<pt> P;
  
vector<pt> Convex(vector<pt> &A) {
    vector<pt> top, bot;
    for (auto p : A) {
        while (bot.size() > 1 && (bot.back() - bot[(int)bot.size() - 2]) % (p - bot.back()) <= 0)
            bot.pop_back();
        bot.push_back(p);
    }
    reverse(A.begin(), A.end());
    for (auto p : A) {
        while (top.size() > 1 && (top.back() - top[(int)top.size() - 2]) % (p - top.back()) <= 0)
            top.pop_back();
        top.push_back(p);
    }   
    for (int i = 1; i < (int)top.size() - 1; i++) bot.push_back(top[i]);
    return bot;
}
  
bool cmp(pt A, pt B) {
    if (A.x >= 0 && B.x < 0) return true;
    if (A.x < 0 && B.x >= 0) return false;
    return (A % B) > 0;
}
  
void add(pt A) { MN[A.x] = min(MN[A.x], A.y); MX[A.x] = max(MX[A.x], A.y); }
 
vector<pt> A, B;
 
void go(int l, int r) {
    if (r - l == 1) {
        add({ 1, C[l] });
        return;
    }
  
    int m = (l + r) / 2;
      
    if (l < m) go(l, m);
    if (m < r) go(m, r);
          
    //err("l = %d, m = %d, r = %d\n", l, m, r);
 
    A.resize(0), B.resize(0); 
     
    ll s = 0;
    for (int i = m - 1; i >= l; i--) {
        s += C[i];
        A.push_back({ m - i, s });
        add(A.back());
    }
    s = 0;
    for (int i = m; i < r; i++) {
        s += C[i];
        B.push_back({ i - m + 1, s });
        add(B.back());
    }
      
    A = Convex(A);
    B = Convex(B);
      
    A.push_back(A[0]), B.push_back(B[0]);
      
      
    int i = 0, j = 0;
      
    while (i < (int)A.size() - 1 && j < (int)B.size() - 1) {
        pt c1 = A[i + 1] - A[i];
        pt c2 = B[j + 1] - B[j];
          
        add(A[i] + B[j]);
         
        if (cmp(c1, c2)) i++;
        else if (cmp(c2, c1)) j++;
        else i++, j++;  
    }
      
    while (i < (int)A.size() - 1) { add(A[i] + B[j]); i++; }
    while (j < (int)B.size() - 1) { add(A[i] + B[j]); j++; } 
}
  
int main() {
     
    fill(MN, MN + 2 * dd, (ll)1e18);
    fill(MX, MX + 2 * dd, -(ll)1e18);
     
    int n, q;
    scanf("%d %d", &n, &q);
      
    for (int i = 0; i < n; i++) {
        scanf("%d", &C[i]);
    }
      
    go(0, n);
      
    for (int x = 0; x < 2 * dd; x++) {
        if (MN[x] <= MX[x]) {
            P.push_back({ x, MN[x] });
            P.push_back({ x, MX[x] });
        }
    }
      
    P = Convex(P);
      
    //err("P = {");for (auto p : P) err(" (%I64d, %I64d),", p.x, p.y); err(" }\n");
    //err("H = {");for (auto p : H) err(" (%I64d, %I64d),", p.x, p.y); err(" }\n");
      
    vector<pair<int, int> > Q(q);
    vector<ll> ans(q);
      
    for (int i = 0; i < q; i++) {
        scanf("%d", &Q[i].first);
        Q[i].second = i;
    }
      
    sort(Q.begin(), Q.end());
      
    int j = 0, sz = (int)P.size();
      
    auto nxt = [sz](int x) { return (x + 1 == sz ? 0 : x + 1); };
    auto prv = [sz](int x) { return x ? x - 1 : sz - 1; };
      
    for (auto c : Q) {
      
        pt cur = { c.first, 1 };
          
        while (P[prv(j)] * cur > P[j] * cur) j = prv(j);
        while (P[nxt(j)] * cur > P[j] * cur) j = nxt(j);
        ans[c.second] = P[j] * cur;
    }
      
    for (int i = 0; i < q; i++) printf("%lld\n", ans[i]);
    return 0;
}