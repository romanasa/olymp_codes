#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> pf(string s) {
    int n = (int)s.size();
    vector<int> p(n);

    for (int i = 1; i < n; i++) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }
    return p;
}

vector<int> zf(string s) {
    int n = (int)s.size();
    vector<int> z(n);

    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

vector<int> p, z;

int calc(string s) {
    int n = (int)s.size();

    //for (int i = 0; i < n; i++) cout << p[i] << " "; cout << "\n";
    //for (int i = 0; i < n; i++) cout << z[i] << " "; cout << "\n";

    set<string> S;
    for (int i = p[n - 1]; i > 0; i = p[i - 1]) {

        //cout << "i = " << i << "\n";
        string cur;

        //cout << i << " ";

        int ind = -1;
        for (int j = 0; j <= i; j++) {
            if (j + z[j] >= i) {
                ind = j;
                break;
            }
            if (j < i) cur += s[j];
        }

        assert(ind != -1);
        S.insert(cur);
    }
    return (int)S.size();
}

int calc2(string cur) {
    p = pf(cur), z = zf(cur);

    int curc = 0;

    string s;
    for (int i = 0; i < (int)cur.size(); i++) {
        s += cur[i];
        //Q.clear();
        curc += calc(s);
    }

    return curc;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN

    //cout << calc(".X..X..X..");
    //return 0;

    int n;
    int x;
    cin >> x;
    
    for (n = x; n >= x; n--) {
    	
        cerr << n << endl;
        int ans = -1;
        string ansS;

        for (int msk = 0; msk < (1 << (n - 1)); msk++) {
            string cur;
            for (int i = 0; i < n; i++)
                if ((msk >> i) & 1) cur += '.';
                else cur += 'X';

            int ok = 1; 
            for (int i = 2; i < (int)cur.size(); i++) {
            	if (cur[i] == cur[i - 1] && cur[i] == cur[i - 2]) ok = 0;
            	if (cur[i] && cur[i] == cur[i - 1]) ok = 0;
            }
            
            if (!ok) continue;

            int curc = calc2(cur);
            if (curc > ans) {
                ans = curc, ansS = cur;
            }
        }
        cout << "M[" << n << "] = " << "{ " << ansS << ", " << ans << "};" << endl;
    }
    return 0;
}

