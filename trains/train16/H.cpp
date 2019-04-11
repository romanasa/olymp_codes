#include <bits/stdc++.h>

using namespace std;

const int dd = (int)107;

int ud[dd][dd]; // >
int lr[dd][dd]; // ^

int main() {
    int h, w;
    cin >> w >> h;

    vector<int> a(w - 1), b(h - 1);

    for (int i = 0; i + 1 < w; i++) cin >> a[i];
    for (int i = 0; i + 1 < h; i++) cin >> b[i];

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> ud[i][j] >> lr[i][j] >> s[i][j];
        }
    }





    return 0;
}
