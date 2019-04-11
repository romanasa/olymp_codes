#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    char c;

    int a = 0, b = 0;
    while (cin >> c) {

        if (c >= 'a' && c <= 'z') a++;
        if (c >= 'A' && c <= 'Z') a++;
        if (c >= '0' && c <= '9') a++;

        if (c == '.' || c == ',' || c == '-' || c == ':' || c == '!') b++;

    }
    cout << a - b;
    return 0;
}

