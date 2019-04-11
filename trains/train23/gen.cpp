#include <bits/stdc++.h>

#define ll long long
#define db double
#define x first
#define y second
#define mp make_pair
#define pub push_back

using namespace std;

int main() {
    freopen("01", "w", stdout);
    int n = rand() % 5 + 1;
    cout << n << endl;
    for (int i = 0; i < n; i++) cout << rand() % 360 << ' ';
}
