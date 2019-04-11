#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    freopen("vars.in", "r", stdin);
    freopen("vars.out", "w", stdout);

    string s;

    map<string, int> M;

    M["boolean"] = 0;
    M["char"] = 0;
    M["double"] = 0;
    M["integer"] = 0;


    while (getline(cin, s)) {
        string a;
        int cnt = 1;
        int ok = 0;
        for (char c : s) {
            if (ok && c != ' ') a += c;
            if (c == ',') cnt++;
            if (c == ':') ok = 1;
        }
        if (a.size() && a.back() == ';') a.pop_back();
        M[a] += cnt;
    }
    for (auto c : M) cout << c.first << ": " << c.second << "\n";

    return 0;
}

