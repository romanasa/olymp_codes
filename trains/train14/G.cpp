#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define x first
#define y second

using namespace std;

int n;
bool was[222][222];
bool bad[222];

int main(){
    //freopen("input.txt", "r", stdin);
    freopen("routes.in", "r", stdin);
    freopen("routes.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++){
        int c = -1;
        for (int j = 1; j <= 2 * n; j++) if (!bad[j]){
            c = j;
            break;
        }
        bad[c] = 1;
        cout << c << ' ';
        for (int j = 1; j < 2 * n; j++){
            bool f = 0;
            for (int to = 1; to <= 2 * n; to++) if (to != c && !was[c][to]){
                if (j == 2 * n - 1 && bad[to]) continue;
                was[c][to] = 1;
                was[to][c] = 1;
                f = 1;
                c = to;
                break;
            }
            cout << c << ' ';
            if (!f) assert(0);
        }
        bad[c] = 1;
        cout << "\n";
    }

}
