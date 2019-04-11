#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)1e5 + 1;
int A[dd];
unordered_map<int, int> dp;
int sum;
 
const int mod = (int)1e9 + 7;
 
void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}
 
void sub(int &a, int b) {
    a -= b;
    if (a < 0) a += mod;
}
 
#define TASK "subsequences"
 
int main() {
#ifndef HOME
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
     
    for (int i = 0; i < n; i++) scanf("%d", &A[i]);
     
    int ans = 0;
    for (int i = 0; i < n; i++) {
        sum = 1;
        dp.clear();
        for (int j = i; j < n; j++) {
            int cur = sum;
            add(cur, cur);
             
            int &res = dp[A[j]];
             
            sub(cur, res);
             
            add(res, cur);
            sub(res, sum);
             
            sum = cur;
             
            printf("i = %d, j = %d, sum = %d\n", i, j, sum - 1);
            add(ans, sum);
        }
    }
    printf("%d\n", ans);
    return 0;
}