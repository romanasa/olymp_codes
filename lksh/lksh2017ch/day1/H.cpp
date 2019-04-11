
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
set<string> se, se2;

int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
#else
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    cin >> n;
    while(n--){
        string s, type;
        int x;
        cin >> s >> type;
        if (type == "WA"){
            cin >> x;
            if (x >= 6) se.insert(s);
            if (x == 7) se2.insert(s);
        } else if (type == "TL"){
            cin >> x;
            if (x >= 6) se.insert(s);
            if (x == 7) se2.insert(s);
        } else if (type == "ML"){
            cin >> x;
            if (x >= 6) se.insert(s);
            if (x == 7) se2.insert(s);
        } else if (type == "AC"){
            se.insert(s);
        }
    }
    cout << se2.size() << ' ' << se.size();
}

