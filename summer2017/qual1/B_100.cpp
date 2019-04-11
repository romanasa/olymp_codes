#include "stocks.h"
 
int Q[(int)5e7], l, L, sz;
long long ans;
 
long long countSegments(int n, int *a, int x) {
    for (int i = 0; i < n; i++) {
        while (L < i && a[i] - Q[l] >= x) if (Q[l] == a[L++]) l++;
        while (sz - l && Q[sz - 1] > a[i]) sz--;
        Q[sz++] = a[i], ans += L;
    }
    return ans;
}