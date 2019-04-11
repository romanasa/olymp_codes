#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
  
using namespace std;
  
typedef long long ll;
  
struct pt {
    int x, y;
};
  
int main() {
    int n;
    scanf("%d", &n);
  
    vector<pt> P(n);
      
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &P[i].x, &P[i].y);
    }
      
    int lx = -1e9, rx = (int)1e9;
    int ly = -1e9, ry = (int)1e9; 
      
    for (int i = 0; i < n; i++) {
      
        pt A = (i ? P[i - 1] : P.back());
        pt B = P[i];
        pt C = (i + 1 < n ? P[i + 1] : P[0]);
          
        if (B.y == C.y && B.x < C.x) { 
            if (A.y < B.y) lx = max(lx, B.x), ry = min(ry, B.y);
            if (A.y > B.y) rx = min(rx, B.x), ry = min(ry, B.y);
        }
          
        if (B.y == C.y && B.x > C.x) {
            if (A.y < B.y) lx = max(lx, B.x), ly = max(ly, B.y);
            if (A.y > B.y) rx = min(rx, B.x), ly = max(ly, B.y);
        }
          
        if (A.y == B.y && C.y > B.y) {
            if (A.x < B.x) lx = max(lx, B.x), ry = min(ry, B.y);
            if (A.x > B.x) lx = max(lx, B.x), ly = max(ly, B.y);
        }
          
        if (A.y == B.y && C.y < B.y) {
            if (A.x < B.x) rx = min(rx, B.x), ry = min(ry, B.y);
            if (A.x > B.x) rx = min(rx, B.x), ly = max(ly, B.y);
        }
    }
      
    if (lx <= rx && ly <= ry) puts("Yes");
    else puts("No");
      
    return 0;
}