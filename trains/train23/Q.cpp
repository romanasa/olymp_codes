#include <bits/stdc++.h>

#define ll long long

using namespace std;

string s1, s2;
char c;

pair<int, int> getPos(string s){
    return make_pair(s[0] - 'a', s[1] - '0');
}

int main() {
    freopen("endspiel.in", "r", stdin);
    freopen("endspiel.out", "w", stdout);
    cin >> s1 >> s2 >> c;
    auto now1 = getPos(s1);
    auto now2 = getPos(s2);
    if (abs(now1.first - now2.first) + abs(now1.second - now2.second) == 1){
        if (c == 'B') cout << "Black ";
        else cout << "White ";
        cout << "wins";
    } else cout << "Draw";
}
