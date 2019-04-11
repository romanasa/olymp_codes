#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
string d[10];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    d[1] = "541236879";
    d[2] = "326798145";
    d[3] = "789145236";
    d[4] = "432879561";
    d[5] = "865321497";
    d[6] = "197564382";
    d[7] = "653982714";
    d[8] = "918457623";
    d[9] = "274613958";
    int i, j;
    cin >> i >> j;
    cout << d[i][j - 1];
    return 0;
}

