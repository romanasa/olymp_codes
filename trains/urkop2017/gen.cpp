#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()

using namespace std;

typedef long long ll;
typedef double db;

int a[1111];

int main() {
    freopen("input.txt", "w", stdout);
    ios_base::sync_with_stdio(0); //cin.tie(0);
    srand(time(NULL));
    int n = rand() % 5 + 1;
    int m = rand() % 5 + 1;
    cout << n << ' ' << m << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << rand() % 100 << ' ';
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++) a[i] = i + 1;
    random_shuffle(a, a + n);
    for (int i = 0; i < n; i++) cout << a[i] << ' ';;
}
