#include <bits/stdc++.h>
#define ll long long

using namespace std;

int n, m;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; }

int A[17][17], ansA[17][17];
int used[17][17];

bool check() {
    vector<set<int> > E(n * m);
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) used[i][j] = A[i][j];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) if (A[i][j] == 0) {
            for (int gg = 0; gg < 4; gg++) {
                int ni = i + dx[gg], nj = j + dy[gg];
                if (ok(ni, nj) && A[ni][nj] == 0) {
                    E[i * m + j].insert(ni * m + nj);
                }
            }
        }
    }

    while (1) {
        int ind = -1, okc = 0;
        for (int i = 0; i < n * m; i++) if ((int)E[i].size() == 1) ind = i;
        for (int i = 0; i < n * m; i++) if ((int)E[i].size() > 0) okc = 1;

        //cerr << "ind = " << ind << ", okc = " << okc << endl;

        if (!okc) break;
        if (ind == -1) return false;

        int i = ind / m, j = ind % m;
        int ci = *E[ind].begin() / m, cj = *E[ind].begin() % m;

        used[i][j] = used[ci][cj] = 1;

        for (int gg = 0; gg < 4; gg++) {
            int ni = ci + dx[gg], nj = cj + dy[gg];
            if (ok(ni, nj) && A[ni][nj] == 0) {
                E[ci * m + cj].erase(ni * m + nj);
                E[ni * m + nj].erase(ci * m + cj);
            }
        }
    }
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (!used[i][j]) return false;
    return true;
}

int ans;
int ansok = 0;

void gen(int cur, int cnt) {
    if (cur == n * m) {
        if (!check()) return;

        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) ansA[i][j] = A[i][j];
        ansok = 1;
    } else {
        gen(cur + 1, cnt);
        if (ansok) return;

        if (cnt == ans) return;

        int i = cur / m, j = cur % m;
        if (A[i][j] == 0 && i + 1 < n && A[i + 1][j] == 0) {
            A[i][j] = A[i + 1][j] = 1;
            gen(cur + 1, cnt + 1);
            A[i][j] = A[i + 1][j] = 0;
            if (ansok) return;
        }
        if (A[i][j] == 0 && j + 1 < m && A[i][j + 1] == 0) {
            A[i][j] = A[i][j + 1] = 1;
            gen(cur + 1, cnt + 1);
            A[i][j] = A[i][j + 1] = 0;
            if (ansok) return;
        }
    }
}

int main(){
    //freopen("input.txt", "r", stdin);
    //cin >> n >> m;

    //A[0][0] = A[0][1] = 1;
    //A[1][1] = A[1][2] = 1;

    //cout << check(A);

    for (n = 2; n <= 10; n += 2) {
    	for (m = 1; m <= 10; m++) {
			if (n % 2 == 0 && m % 2 == 0 && m > n) continue;
    		ansok = 0;
    		
            for (ans = 1; ; ans++) {
                gen(0, 0);
                if (ansok) break;
                //cerr << ans << "fail" << endl;
            }
            
            cout << "M[" << n << "][" << m << "] = \"";
            cout << ans << "\\n";
            for (int i = 0; i < n; i++) { for (int j = 0; j < m; j++) cout << ansA[i][j]; cout << "\\n"; }
            cout << "\";" << endl;
    	}
    }
    


    return 0;
}

