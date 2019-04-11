#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)

typedef long long ll;
 
using namespace std;
 
int A[411][411];
 
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int t;
            cin >> t;
             
            for (int x = 0; x < n; x++) 
                for (int y = 0; y < m; y++) 
                    A[x][y] += max(0, t - (abs(x - i) + abs(y - j)));
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}