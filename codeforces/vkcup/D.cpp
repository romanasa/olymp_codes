#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;
 
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        s[i]--;
    }
 
    vector<string> T;
 
    for (int it = 0; it < n; it++) {
 
        vector<int> st(11, (int)1e9);
        vector<int> num(11);
 
        for (int i = it; i < n; i++) st[s[i]] = min(st[s[i]], i);
        int c = 0;
 
        while (1) {
            int ind = min_element(st.begin(), st.end()) - st.begin();
            if (st[ind] == (int)1e9) break;
            num[ind] = c++;
            st[ind] = (int)1e9;
        }
 
        string cur;
        for (int i = it; i < n; i++) cur += num[s[i]];
        T.push_back(cur);
    }
    sort(T.begin(), T.end());
 
    for (auto c : T) cout << n - (int)c.size() << " ";
 
    return 0;
}