#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

map<char, string> M;

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#endif

M['a'] = "@";
M['n'] = "[]\\[]";
M['b'] = "8";
M['o'] = "0";
M['c'] = "(";
M['p'] = "|D";
M['d'] = "|)";
M['q'] = "(,)";
M['e'] = "3";
M['r'] = "|Z";
M['f'] = "#";
M['s'] = "$";
M['g'] = "6";
M['t'] = "']['";
M['h'] = "[-]";
M['u'] = "|_|";
M['i'] = "|";
M['v'] = "\\/";
M['j'] = "_|";
M['w'] = "\\/\\/";
M['k'] = "|<";
M['x'] = "}{";
M['l'] = "1";
M['y'] = "`/";
M['m'] = "[]\\/[]";
M['z'] = "2";

    string s, ans;
    getline(cin, s);
    for (char c : s) {
        if (isalpha(c)) ans += M[tolower(c)];
        else ans += c;
    }
    cout << ans;
    return 0;
}
