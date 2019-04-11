#include <bits/stdc++.h>

using namespace std;

int n;
vector<string> a[66];
int q[66];

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#else
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; i++){
        string tmp;
        for (int it = 0; it < 3; it++){
            cin >> tmp;
            a[i].push_back(tmp);
        }
        sort(a[i].begin(), a[i].end());
    }
    for (int i = 0; i < n; i++) cin >> q[i];
    string last;
    vector<string> ans;
    for (int i = 0; i < n; i++){
        int uk = q[i] - 1;
        if (i == 0){
            ans.push_back(a[uk][0]);
            last = a[uk][0];
        } else {
            bool f = 0;
            for (int j = 0; j < 3; j++) if (a[uk][j] > last){
                ans.push_back(a[uk][j]);
                last = a[uk][j];
                f = 1;
                break;
            }
            if (!f) cout << "IMPOSSIBLE", exit(0);
        }
    }
    for (auto c : ans) cout << c << endl;
}
