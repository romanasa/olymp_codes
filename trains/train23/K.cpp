#include <bits/stdc++.h>

#define ll long long

using namespace std;

string a[111];
int n;

int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

bool win(){
    for (int i = 0; i < n; i++) for (int j = 0; j < a[i].size(); j++) for (int s = 0; s < 8; s++){
        bool f = 1;
        for (int w = 0; w < 5; w++){
            int nx = i + dx[s] * w;
            int ny = j + dy[s] * w;
            if (nx < 0 || ny < 0 || nx >= n || ny >= a[0].size()){
                f = 0;
                break;
            }
            if (a[nx][ny] != a[i][j] || a[i][j] == '.'){
                f = 0;
                break;
            }
        }
        if (f) return 1;
    }
    return 0;
}

int main() {
    //freopen("01", "r", stdin);
    freopen("xo.in", "r", stdin);
    freopen("xo.out", "w", stdout);
    string s;
    n = 0;
    int ma = 0;
    while(getline(cin, s)){
        a[n++] = s;
        ma = max(ma, (int)s.size());
    }
    for (int i = 0; i < n; i++) while(a[i].size() < ma) a[i] += '.';
    int k1 = 0, k2 = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < a[i].size(); j++) if (a[i][j] == 'X') k1++; else if (a[i][j] == 'O') k2++;
    if (abs(k1 - k2) > 1) cout << "INCORRECT", exit(0);
    if (k2 > k1) cout << "INCORRECT", exit(0);
    int go = 0;
    if (k1 > k2) go = 1;
    //cout << k1 << ' ' << k2 << endl;
    if (!win()) cout << "CORRECT", exit(0);
    for (int i = 0; i < n; i++) for (int j = 0; j < a[i].size(); j++){
        if (a[i][j] == 'X' && go == 1){
            a[i][j] = '.';
            if (!win()) cout << "CORRECT", exit(0);
            a[i][j] = 'X';
        }
        if (a[i][j] == 'O' && go == 0){
            a[i][j] = '.';
            if (!win()) cout << "CORRECT", exit(0);
            a[i][j] = 'O';
        }
    }
    cout << "INCORRECT";
}
