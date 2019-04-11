#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)
 
typedef long long ll;
 
using namespace std;
 
const int dd = 700 + 5;
 
int G1[2 * dd][2 * dd], G2[2 * dd][2 * dd];
int A[dd][dd];
 
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
     
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int v;
            scanf("%d", &v);
             
            if (!v) continue;
             
            G1[i + j][i + dd] += v;
            G1[i + j][i + 1 + dd] -= v;
             
             
            for (int t = i + 1; t < v + i && t + j <= (n - 1 + m - 1); t++) {
                G1[t + j][i + dd] += v - (t - i);
                G1[t + j][t + 1 + dd] -= v - (t - i);
            }
             
            for (int t = i - 1; t > i - v && t + j >= 0; t--) {
                G1[t + j][t + dd] += v - (i - t);
                G1[t + j][i + 1 + dd] -= v - (i - t);
            }
             
            for (int t = i + 2; t < v + i && t - j <= ((n - 1) - 0); t++) {
                G2[t - j + dd][i + 1 + dd] += v - (t - i);
                G2[t - j + dd][t + dd] -= v - (t - i);
            }   
             
            for (int t = i - 2; t > i - v && t - j >= (0 - (m - 1)); t--) {
                G2[t - j + dd][t + 1 + dd] += v - (i - t);
                G2[t - j + dd][i + dd] -= v - (i - t);
            }
        }
    }
     
    for (int s = 0; s < dd + dd; s++) {
        int cur = 0;
        for (int i = -n; i <= n; i++) {
            int j = s - i;
            cur += G1[s][i + dd];
            if (j < 0 || j >= m) continue;
            if (i < 0 || i >= n) continue;
            A[i][j] += cur;
        }
    }
     
    for (int d = 0; d < dd + dd; d++) {
        int cur = 0;
        for (int i = -n; i <= n; i++) {
            int j = i + dd - d;
            cur += G2[d][i + dd];
            if (j < 0 || j >= m) continue;
            if (i < 0 || i >= n) continue;
            A[i][j] += cur;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d%c", A[i][j], " \n"[j == m - 1]);
        }
    }
    return 0;
}