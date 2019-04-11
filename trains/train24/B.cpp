#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define mp make_pair
#define pub push_back
#define x first
#define all(a) a.begin(), a.end()
#define y second

#define TASK "elves"

int n;

int main() {
    n = rand() % 15 + 5;
    cout << n << endl;
    int to = 2;
    for (int i = 1; i <= n; i++){
        if (to == i + 1 && i != n){
            cout << to << ' ';
            to++;
        } else {
            if (to != n + 1 && rand() % 2 == 0) cout << to << ' ', to++;
            else cout << "0 ";
        }
        if (to != n + 1 && rand() % 2 == 0) cout << to, to++;
        else cout << 0;
        cout << endl;
    }
}


