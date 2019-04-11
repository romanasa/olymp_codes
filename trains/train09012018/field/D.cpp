#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)
 
typedef long long ll;
 
using namespace std;
 
const int dd = 700 + 5;
 
int O[dd][dd];
int A[dd][dd];
int F[dd][dd];
 
void add(int t, int l, int r, int x, int q) {
    F[t][l] += q, F[t][r + 1] -= q;
    O[t][l] += x, O[t][r + 1] -= x;
}
 
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
     
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int v;
            scanf("%d", &v);
             
            if (!v) continue;
             
            for (int t = max(0, i - v + 1); t < min(i + v, n); t++) {
                int dx = v - abs(i - t);
                 
                int l = j - dx + 1, val = 1;
                if (l < 0) val += -l, l = 0;
                 
                add(t, l, j, val - l, 1);
                add(t, j + 1, min(j + dx - 1, m - 1), dx + j, -1);  
            }
             
        }
    }
     
     
    for (int i = 0; i < n; i++) {
        int bal = 0;
        int sb = 0;
        for (int j = 0; j < m; j++) {    
            sb += O[i][j];
            bal += F[i][j];
            A[i][j] += bal * j + sb;
        }
    }
     
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d%c", A[i][j], " \n"[j == m - 1]);
        }
    }
    return 0;
}