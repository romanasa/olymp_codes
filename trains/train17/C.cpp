#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

string a[6] = {"rgwb", "bgwr", "grbw", "rwbg", "wrgb", "gbrw"};

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    string ss;
    cin >> ss;
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 4; j++){
            bool f = 1;
            for (int s = 0; s < 4; s++){
                if (a[i][(j + s) % 4] != ss[s]){
                    f = 0;
                    break;
                }
            }
            if (f) cout << i + 1, exit(0);
        }
    }
}
