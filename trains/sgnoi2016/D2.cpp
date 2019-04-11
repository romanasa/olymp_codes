#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)2e5 + 7;
 
struct ev {
    int x, y, e, s;
    bool operator < (const ev &b) const {
        return (y == b.y ? x < b.x : y > b.y);
    }
};
 
int main() {
    int n, h;
    cin >> n >> h;
     
    vector<ev> A(n);
    for (int i = 0; i < n; i++) cin >> A[i].x >> A[i].y >> A[i].s >> A[i].e;
    sort(A.begin(), A.end());
     
    vector<ll> dp(n);
     
    for (int i = 0; i < n; i++) {
        dp[i] = 0;
         
        for (int j = 0; j < i; j++) {
            if (A[i].y >= A[j].y - A[j].e && A[i].x <= A[j].x + A[j].e && A[j].x - A[j].e <= A[i].x)
                dp[i] = max(dp[i], dp[j]);
        }
        dp[i] += A[i].s;
    }
    cout << *max_element(dp.begin(), dp.end());    
    return 0;
}