#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
const int dd = (int)1e6 + 1;
 
int A[dd], dp[dd];
int n;
 
deque<int> T;
void add(int x) {
    while (T.size() && T.back() < x) T.pop_back();
    T.push_back(x);
}
 
void pop(int x) {
    if (T.front() == x) T.pop_front();
}
 
int L, R;
 
int get(int l, int r) {
    if (l > r) return 0;
 
    while (L > l) {
        L--;
        add(dp[L]);
    }
 
    while (R > r) {
        pop(dp[R]);
        R--;
    }
 
    return T.size() ? T.front() : 0;
}
 
 
bool check(int r) {
    for (int i = 0; i + 1 < n; i++)
        if (A[i] + r < A[i + 1]) return false;
 
    T.clear();
 
    L = n - 1, R = n - 1;
    add(dp[L]);
 
    //err("add %d\n", dp[L]);
 
    dp[n - 2] = 1;
 
    int ind = n - 1;
 
    for (int i = n - 3; i >= 0; i--) {
 
        while (ind > i && A[i] + r < A[ind]) {
            ind--;
        }
 
        int l = i + 2;
        int r = ind - 1;
 
        dp[i] = get(l, r);
 
        if ((i == 0 || ind == n - 1) && dp[i + 1]) dp[i] = 1;
        //err("l = %d, r = %d\n", l, r);
        //err("dp[%d] = %d\n", i, dp[i]);
 
    }
    return dp[0];
}
 
 
int main() {
    scanf("%d", &n);
 
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);
 
    if (n == 1) {
        return 0 * puts("0");
    }
 
    sort(A, A + n);
    for (int i = 0; i + 1 < n; i++) assert(A[i] != A[i + 1]);
 
    //check(8);
    //return 0;
 
    int l = -1, r = (int)1e9 + 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (check(m)) r = m;
        else l = m;
    }
    printf("%d\n", r);
    return 0;
}