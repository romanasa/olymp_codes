#include <bits/stdc++.h>
#define ll long long

using namespace std;

int n;

 bool can(int w1, int w2){
    if (w1 < n && w2 < n) return 1;
    if (w1 >= n && w2 >= n) return 1;
    if (abs(w2 - w1) == n) return 1;
    return 0;
 }

int main(){
    //freopen("input.txt", "r", stdin);
    cin >> n;
    vector<int> t;
    for (int i = 0; i < 2 * n; i++) t.push_back(i);
    int ans = 0, ans2 = 0;

    do{
        vector<int> st;
        for (int x : t){
            st.push_back(x);
            while(1){
                if (st.size() < 3) break;
                if (can(st[(int)st.size() - 1], st[(int)st.size() - 3])){
                    st.pop_back();
                    int tmp = st.back();
                    st.pop_back();
                    st.pop_back();
                    st.push_back(tmp);
                } else break;
            }
        }
        if (st.size() == 2){
            ans++;
            //for (int x : t) cout << x << ' ';
            //cout << endl;
        }
        ans2++;
    } while(next_permutation(t.begin(), t.end()));

    int w1 = ans;
    int w2 = ans2;
    int cc = __gcd(w1, w2);
    cc = 1;
    cout << w1 / cc << ' ' << w2 / cc;
}

