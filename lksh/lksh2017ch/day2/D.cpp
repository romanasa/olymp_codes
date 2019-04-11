#include <bits/stdc++.h>

using namespace std;

string ss;
int n;
char s[5002];
int sum[5002];
int minBal[5002];
short int minBal2[5002][5002];
short int minBal3[5002][5002];

int getSum(int l, int r){
    if (l > r) return 0;
    return sum[r] - sum[l - 1];
}

int getVal(char c){
    if (c == '(') return 1;
    if (c == ')') return -1;
}

bool check(int l, int r){
    if (l != 1) if (minBal[l - 1] < 0) return 0;
    if (minBal2[l][r] < 0) return 0;
    if (r != n && minBal3[l][r + 1] < 0) return 0;
    if (getSum(1, l - 1) - getSum(l, r) + getSum(r + 1, n) != 0) return 0;
    return 1;
}

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#endif
    cin >> ss; n = ss.size();
    for (int i = 0; i < ss.size(); i++) s[i + 1] = ss[i];
    for (int i = 1; i <= n; i++){
        sum[i] = getVal(s[i]) + sum[i - 1];
    }

    for (int i = 1; i <= n; i++) minBal[i] = min(minBal[i - 1], getSum(1, i));

    for (int i = 1; i <= n; i++) for (int j = i; j <= n; j++){
        int now = getSum(1, i - 1) - getSum(i, j);
        minBal2[i][j] = now;
        if (j != i + 1) minBal2[i][j] = min(minBal2[i][j], minBal2[i][j - 1]);
    }

    for (int j = 2; j <= n; j++){
        int now = getSum(j, j);
        for (int s = j; s <= n; s++) now = min(now, getSum(j, s));
        for (int i = j - 1; i >= 1; i--){
            int sumNow = getSum(1, i - 1) - getSum(i, j - 1);
            minBal3[i][j] = now + sumNow;
        }
    }

    for (int i = 1; i <= n; i++) for (int j = i; j <= n; j++) if (check(i, j)) cout << "possible", exit(0);

    if (getSum(1, n) == 0 && minBal[n] >= 0) cout << "possible";
    else cout << "impossible";
}

