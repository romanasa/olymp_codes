#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
    
using namespace std;
    
typedef long long ll;
    
const int CC = 20;
  
const int MAXMEM = (int)2e8;
char MEM[MAXMEM];
int mpos;
   
inline void* operator new(size_t n) {
    char *res = MEM + mpos;
    mpos += n;
    return (void*)res;
}
   
inline void operator delete(void*) {}
   
const int dd = (int)1e5 + 1;
unordered_set<int> A[2 * CC * dd], C[2 * CC * dd];
char s[dd];
    
const int maxC = (int)1e5;
    
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
    
const char* NAME = "WNES";
    
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    scanf("%s", s);
        
    int cx = 0, cy = 0;
    A[cx + maxC].insert(cy);    
        
    ll ans = 0;
    int last = -1;
    for (int it = 0; it < min(CC, k); it++) {
        for (int i = 0; i < n; i++) {
            int gg = strchr(NAME, s[i]) - NAME;
            cx += dx[gg], cy += dy[gg];
            A[cx + maxC].insert(cy);
        }
            
            
        int cur = 0;
        for (int i = 0; i < 2 * CC * dd; i++) {
            for (auto it = A[i].begin(); it != A[i].end(); ++it) {
                if (C[i].find(*it) != C[i].end()) continue;
                if (A[i].find(*it + 1) != A[i].end() && A[i + 1].find(*it) != A[i + 1].end() && A[i + 1].find(*it + 1) != A[i + 1].end()) {
                    cur++;
                    C[i].insert(*it);
                }
            }
        }
        ans += cur;
        last = cur;
    }
    if (k > CC) ans += 1ll * last * (k - CC);
        
    printf("%I64d\n", ans);
    return 0;
}