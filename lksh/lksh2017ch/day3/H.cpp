#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
int main() {
#ifdef WIN
    freopen("01.in", "r", stdin);
    //freopen("01.out", "w", stdout);
#endif // WIN
    string s;
    cin >> s;
 
    int neg = 0;
    if (s[0] == '-') neg = 1, s.erase(s.begin());
 
 
    int pos = s.find(".");
    if (pos == -1) {
        sort(s.begin(), s.end());
 
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] > '0') {
                swap(s[0], s[i]);
                break;
            }
        }
 
        if (!neg) {
            cout << s <<"\n";
            sort(s.rbegin(), s.rend());
            cout << s << "\n";
        } else {
            string t = s;
            sort(s.rbegin(), s.rend());
            cout << "-" << s << "\n";
            cout << "-" << t << "\n";
        }
 
    } else {
        s.erase(s.begin() + pos);
 
 
        sort(s.begin(), s.end());
        
        string a;
        a += s[0];
        a += "." + string(s.begin() + 1, s.end());
 
        sort(s.rbegin(), s.rend());
 
 		int pos = (int)s.size() - 1;
 		
 		int ok = 0;
 		for (char c = '1'; c <= '9'; c++) if (s.find(c) != -1) ok = 1;
 		while (!ok && pos - 1 > 0 && s[pos - 1] == '0') pos--;
 
 		
 		
        string b = string(s.begin(), s.begin() + pos) + "." + string(s.begin() + pos, s.end());
 
        if (!neg) cout << a << "\n" << b << "\n";
        else cout << "-" << b << "\n-" << a << "\n";
    }
}