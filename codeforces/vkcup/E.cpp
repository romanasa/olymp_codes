#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
const int dd = 301;
 
string a[dd], b[dd];
 
unsigned long long hA[dd], hB[dd];
unsigned long long qA[dd], qB[dd];
int P[dd], cntA[dd], cntB[dd];
int used[dd];
int Q[dd];
 
int n;
int found;
 
void go(int len = 0) {
    int vmax = -1;
    for (int i = 0; i < n; i++) if (P[i] == -1) {
        if (vmax == -1 || cntA[vmax] < cntA[i]) {
            vmax = i;
        }
    }
 
    if (vmax == -1) {
       found = 1;
       return;
    }
 
    int v = vmax;
 
    for (int jj = 0; jj < n; jj++) {
        int j = Q[jj];
 
        if (used[j] || cntB[j] != cntA[v] || hA[v] != hB[j] || qA[v] != qB[j]) continue;
 
        int can = 1;
        for (int t = 0; t < n; t++) if (P[t] != -1) {
            if (a[v][t] != b[j][P[t]]) { can = 0; break; }
        }
        if (can) {
            P[v] = j;
            used[j] = 1;
            go(len + 1);
            if (found) return;
            P[v] = -1;
            used[j] = 0;
        }
    }
}
 
int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int t;
    cin >> t;
 
    while (t--) {
        cin >> n;
 
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        for (int i = 0; i < n; i++) P[i] = -1, used[i] = 0;
 
        for (int i = 0; i < n; i++) Q[i] = i;
 
        for (int i = 0; i < n; i++) {
            int c = 0;
            for (int j = 0; j < n; j++) c += (a[i][j] == '1');
            cntA[i] = c;
        }
 
        for (int i = 0; i < n; i++) {
            int c = 0;
            for (int j = 0; j < n; j++) c += (b[i][j] == '1');
            cntB[i] = c;
        }
        
        
        for (int i = 0; i < n; i++) {
        	hA[i] = hB[i] = 0;
        	for (int j = 0; j < n; j++) if (a[i][j] == '1') hA[i] += cntA[j] * cntA[j] * cntA[j];
        	for (int j = 0; j < n; j++) if (b[i][j] == '1') hB[i] += cntB[j] * cntB[j] * cntB[j];
        }
        
        for (int i = 0; i < n; i++) {
        	qA[i] = qB[i] = 0;
        	for (int j = 0; j < n; j++) if (a[i][j] == '1') qA[i] += hA[j] * hA[j] * hA[j];
        	for (int j = 0; j < n; j++) if (b[i][j] == '1') qB[i] += hB[j] * hB[j] * hB[j];
        }
        
 
        //sort(Q, Q + n, [](int a, int b) { return cntB[a] > cntB[b]; });
 
        found = 0;
        go();
 
        for (int i = 0; i < n; i++) cout << P[i] + 1 << " ";
        cout << "\n";
    }
 
    return 0;
}