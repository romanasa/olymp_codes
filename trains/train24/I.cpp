#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define mp make_pair
#define pub push_back
#define x first
#define all(a) a.begin(), a.end()
#define y second

#define TASK "table"

int n;
vector<int> a[111];
char c[1000][1000];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++){
        int sz;
        cin >> sz;
        a[i].resize(sz);
        for (int j = 0; j < sz; j++) cin >> a[i][j];
    }
    for (int i = 0; i < 1000; i++) for (int j = 0; j < 1000; j++) c[i][j] = ' ';
    for (int i = 0; i < n; i++){
        int pos = i * 2;
        int now = -1;
        for (int j = 0; j < a[i].size(); j++){
            now++;
            c[pos][now] = '-';
            c[pos + 1][now] = '|';
            c[pos + 2][now] = '-';
            for (int s = 0; s < a[i][j]; s++){
                now++;
                c[pos][now] = '-';
                c[pos + 2][now] = '-';
            }
        }
        now++;
        c[pos][now] = '-';
        c[pos + 1][now] = '|';
        c[pos + 2][now] = '-';
    }

    for (int i = 0; i < 1000; i++) for (int j = 0; j < 1000; j++){
        if (c[i][j] == '-'){
            if (i && c[i - 1][j] == '|') c[i][j] = '+';
            if (c[i + 1][j] == '|') c[i][j] = '+';
        }
    }

    for (int i = 0; i < n * 2 + 1; i++){
        int ma = 0;
        for (int j = 0; j < 1000; j++) if (c[i][j] != ' ') ma = j;
        for (int s = 0; s <= ma; s++) cout << c[i][s];
        cout << "\n";
    }
}


