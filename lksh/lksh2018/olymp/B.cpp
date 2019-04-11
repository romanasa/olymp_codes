#include <iostream>
#include <cstdio>
using namespace std;

const int maxN = 1e5 + 10;
const int maxK = 50;

long long a[maxN];

long long get_bit(long long mask, long long pos) {
    return (mask >> pos) & 1;
}

long long div(long long n) {
    while(n > 0 && (n & 1LL) == 0)
        n >>= 1;
    return n;
}

int cost(long long n, int d) {
    int ans = 0;
    while(n > 0 && d > 0) {
        if(n == 1LL) n = 0, ans++;
        else if(n == 2LL) 
            n = 0, ans += 2;
        //else if((n & 3LL) == 2)
        //    n = div(n), ans += 2, d--;
        else if((n & 3LL) == 1)
            n = div(n - 1), ans++, d--;
        else if((n & 3LL) == 3)
            n = div(n + 1), ans++, d--;
        else if((n & 1LL) == 0)
            n = div(n), d--;
    }
    ans += n;
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
    long long ans = 1e18;
    for(int k = 0; k < maxK; k++) {
        long long cur = 0;
        for(int i = 0; i < n; i++) 
            cur += cost(a[i], k);
        ans = min(ans, cur + k);
    }
    printf("%lld", ans);
}

