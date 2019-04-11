#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define TASK "numbers"

int n;
set<int> se[1111];

ll getVal(string s){
    if (s[0] == '0') return -1;
    ll x = 0;
    for (char c : s) x = x * (ll)10 + c - '0';
    return x;
}

string parse(string s){
    //cout << "===" << s << endl;
    if (s.size() == 3) return s;
    if (s.size() == 4){
        string ss;
        ss += s[0];
        ss += s[1];
        ss += '-';
        ss += s[2];
        ss += s[3];
        return ss;
    }
    if (s.size() == 5){
        string ss;
        ss += s[0];
        ss += s[1];
        ss += s[2];
        ss += '-';
        ss += s[3];
        ss += s[4];
        return ss;
    }
    if (s.size() == 6){
        string ss;
        ss += s[0];
        ss += s[1];
        ss += '-';
        ss += s[2];
        ss += s[3];
        ss += '-';
        ss += s[4];
        ss += s[5];
        return ss;
    }
    if (s.size() == 7){
        string ss;
        ss += s[0];
        ss += s[1];
        ss += s[2];
        ss += '-';
        ss += s[3];
        ss += s[4];
        ss += '-';
        ss += s[5];
        ss += s[6];
        return ss;
    }
    assert(0);
}

string solve(string s){
    for (int i = 1; i <= 3; i++) for (int j = 3; j <= 5; j++){
        string s1, s2, ost;
        for (int g = 0; g < i; g++) s1 += s[g];
        for (int g = 0; g < j; g++) s2 += s[i + g];
        for (int g = 0; g < 11 - i - j; g++) ost += s[i + j + g];
        ll now1 = getVal(s1), now2 = getVal(s2);
        if (now1 == -1 || now2 == -1 || ost[0] == '0') continue;
        if (se[now1].find(now2) != se[now1].end()){
            return "+" + s1 + "(" + s2 + ")" + parse(ost);
        }
    }
    return "Incorrect";
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);
#endif // WIN
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++){
        int c1, c2;
        cin >> c1 >> c2;
        for (int j = 0; j < c2; j++){
            int x;
            cin >> x;
            se[c1].insert(x);
        }
    }
    cin >> n;
    while(n--){
        string s;
        cin >> s;
        cout << solve(s) << "\n";
    }
    return 0;
}

