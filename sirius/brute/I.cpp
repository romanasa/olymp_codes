#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)1e4 + 1;
vector<vector<int> > E1, ER1, E2, ER2;
short deg[dd][dd];
bitset<dd> W[dd], L[dd], used[dd];


int lq, R; 
pair<short, short> q[dd * dd];

void bfs() {
    
	while (lq < R) {
		int i = q[lq].first;
		int j = q[lq].second;
		lq++;
        
        for (int to : ER1[i]) {
            if (used[to][j]) continue;
            if (L[i][j]) W[to][j] = 1;
            else if (--deg[to][j] == 0) L[to][j] = 1;
            else continue;
            used[to][j] = 1;
            q[R++] = { to, j };
        }
         
        for (int to : ER2[j]) {
            if (used[i][to]) continue;
            if (L[i][j]) W[i][to] = 1;
            else if (--deg[i][to] == 0) L[i][to] = 1;
            else continue;
            used[i][to] = 1;
            q[R++] = { i, to };
        }
    }
}
 
int main() {
    int n1, m1;
    scanf("%d %d", &n1, &m1);
     
    E1.resize(n1);
    ER1.resize(n1);
     
    for (int i = 0; i < m1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        E1[a - 1].push_back(b - 1);
        ER1[b - 1].push_back(a - 1);
    }
     
    int n2, m2;
    scanf("%d %d", &n2, &m2);
     
    E2.resize(n2);
    ER2.resize(n2);
    for (int i = 0; i < m2; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        E2[a - 1].push_back(b - 1);
        ER2[b - 1].push_back(a - 1);
    }
     
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            int cnt = (int)E1[i].size() + (int)E2[j].size();
            if (cnt == 0) L[i][j] = 1;
            deg[i][j] = cnt;
        }
    }
     
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (deg[i][j] == 0) {
                used[i][j] = 1;
                q[R++] = { i, j };
            }
        }
    }
    
    bfs();
     
    int q;
    scanf("%d", &q);
    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--, b--;
        if (W[a][b]) puts("first");
        else if (L[a][b]) puts("second");
        else puts("draw");
    }
     
    return 0;
}