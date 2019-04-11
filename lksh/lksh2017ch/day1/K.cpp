#include <bits/stdc++.h>

using namespace std;

#define ld long double
#define mp make_pair
#define x first
#define y second

int n;
string name[1007], rang[1007];
int type[1007];
vector<int> q[3][507];
int dp[507][1007];

vector<pair<string, string> > calcDp(){
    for (int i = 0; i < 507; i++) for (int j = 0; j < 1007; j++) dp[i][j] = -1;
    for (int i = 0; i < 507; i++){
        dp[i][0] = 0;
        for (int j = 0; j <= q[0][i].size() + q[1][i].size(); j++){

        }
    }
}

int main() {
    freopen("01.in", "r", stdin);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++){
        string s;
        cin >> name[i] >> s >> rang[i];
        if (s[0] == 's') type[i] = 0;
        if (s[0] == 'a') type[i] = 1;
        if (s[0] == 't') type[i] = 2;
    }
    vector<pair<string, string> > ans;

    for (int i = 0; i < 3; i++) for (int j = 0; j < 507; j++) q[i][j].clear();
    for (int i = 0; i < n; i++) if (rang[i] % 2 == 0){
        q[type[i]][rang[i] / 2].pub(i);
    }
    auto now = calcDp();
    for (auto c : now) ans.pub(now);


    for (int i = 0; i < 3; i++) for (int j = 0; j < 507; j++) q[i][j].clear();
    for (int i = 0; i < n; i++) if (rang[i] % 2 == 1){
        q[type[i]][rang[i] / 2].pub(i);
    }
    now = calcDp();
    for (auto c : now) ans.pub(now);

    cout << ans.size() << endl;
    for (auto c : ans) cout << c.x << ' ' << c.y << endl;
}

