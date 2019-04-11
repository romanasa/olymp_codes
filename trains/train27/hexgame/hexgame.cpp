#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
int dp[3][3][5432];
int used[5432], tmm;
 
inline int play(int len, int jL, int jR) {
    if (len <= 0) return 0;
    if (len >= 3) return 1;
    if (jL == 2) jL = 2 - jL, jR = 2 - jR;
    if (len == 2 && jL == 0 && jR == 1) return 0;
    if (jL == 0 && jR == 2) return 1;
    if (len <= 1) return 0;
    return 1;
}

void init() {
    memset(dp, -1, sizeof(dp));
       
    for (int len = 0; len < 5111; len++) for (int a = 0; a < 3; a++) for (int b = 0; b < 3; b++) {
    	int jL = a, jR = b;
    
    	//if (jL == 1) swap(jL, jR), len += 1 - (jL == 1);
        if (jL == 2) jL = 2 - jL, jR = 2 - jR;
        
        if (!play(len, jL, jR)) { dp[a][b][len] = -1; continue; }
        if (dp[jL][jR][len] != -1) { dp[a][b][len] = dp[jL][jR][len]; continue; }
         
        ++tmm;
        for (int t = 1; t < len; t++) {
            for (int j = 0; j < 3; j++) {
                int a = dp[jL][j][t];
                int b = dp[j][jR][len - t];
                if (a == -1 || b == -1) continue;
                used[a ^ b] = tmm;
            }
        }
        //for (int x : cur) used[x] = tmm;
        for (int i = 0; ; i++) if (used[i] != tmm) {
        	dp[a][b][len] = i;
        	break;
        }
    }
}
 
char A[3][5432];
 
int solve(int n, char* _up, char* _mid, char* _low) {
    if (n == 1) {
        int cnt = (_up[0] == '#') + (_mid[0] == '#') + (_mid[1] == '#') + (_low[0] == '#');
        if (cnt == 0) return 1;
        if (cnt == 1 && ((_up[0] == '#') || (_low[0] == '#'))) return 2;
        if (cnt == 1) return 1;
        if (cnt == 3) return 1;
        if (_mid[0] == '#' && _mid[1] == '#') return 2;
        return 1;
    }
     
    for (int i = 0; i < n; i++) A[0][i] = _up[i], A[1][i] = _mid[i], A[2][i] = _low[i];
    A[0][n] = A[2][n] = '.';
    A[1][n] = _mid[n];
     
    int pr = -2;
    int jL = 1;
     
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 3; j++) if (A[j][i] == '#') {
            int t = dp[jL][j][i - pr];
            pr = i, jL = j;
            if (t == -1) return 1;
            ans ^= t;
        }
    }
    int t = dp[jL][1][n + 2 - pr];
    if (t == -1) return 1;
    ans ^= t;
    return (ans ? 1 : 2);
}