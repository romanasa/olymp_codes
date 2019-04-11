#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()
//236695ZVSVG

using namespace std;

typedef long long ll;
typedef double db;

struct st{
    int type;
    int len;
    set<char> se;
};

string s;
vector<st> g;

bool check(string t){
    bool f = 0;
    reverse(all(t));
    for (int i = 0; i < g.size(); i++){
        if (g[i].type == 0){
            f = 1;
            break;
        }
        if (g[i].type == 1){
            if (t.size() == 0) return 0;
            t.pop_back();
        } else {
            if (g[i].len > t.size()) return 0;
            for (int j = 0; j < g[i].len; j++){
                if (g[i].se.find(t.back()) == g[i].se.end()) return 0;
                t.pop_back();
            }
        }
    }
    reverse(all(t));
    if (!f){
        return t.size() == 0;
    }

    for (int i = (int)g.size() - 1; i >= 0; i--){
        if (g[i].type == 0){
            break;
        }
        if (g[i].type == 1){
            if (t.size() == 0) return 0;
            t.pop_back();
        } else {
            if (g[i].len > t.size()) return 0;
            for (int j = 0; j < g[i].len; j++){
                if (g[i].se.find(t.back()) == g[i].se.end()) return 0;
                t.pop_back();
            }
        }
    }

    return 1;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> s;

    int ott = 0, st = 0;
    set<char> se;

    for (int i = 0; i < s.size(); ){
        if (s[i] == '*'){
            g.pub({0, 0, {}});
        } else if (s[i] == '?'){
            g.pub({1, 0, {}});
        } else {
            if (s[i] == '!'){
                ott = 1;
            } else if (s[i] == '['){
                st = 1;
                se.clear();
            } else if (s[i] == ']'){
                set<char> tmp;
                if (ott == 1){
                    for (char c = 'a'; c <= 'z'; c++) if (se.find(c) == se.end()) tmp.insert(c);
                    for (char c = 'A'; c <= 'Z'; c++) if (se.find(c) == se.end()) tmp.insert(c);
                } else tmp = se;
                i++;
                g.pub({2, s[i] - '0', tmp});
                ott = 0;
                st = 0;
            } else {
                if (st) se.insert(s[i]);
                else g.pub({2, 1, {s[i]}});
            }
        }
        i++;
    }

    int n;
    cin >> n;
    while(n--){
        string t;
        cin >> t;
        if (check(t)) cout << t << "\n";
    }
}

