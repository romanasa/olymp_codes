#include <bits/stdc++.h>

#define ll long long

using namespace std;

int n;
int cc;

vector<int> a;
bool was[188];

ll calc(){
    if (a.size() == 8) {
        //return 1;
        if (a[0] == 0 && a.back() == n - 1) return 0;
        return 1;
    }
    ll ans = 0;

    for (int i = a.back() + 2; i < n; i++) if (!was[i]){
            a.push_back(i);
            was[i + cc] = 1;
            ans += calc();
            was[i + cc] = 0;
            a.pop_back();
    }

    return ans;
}

int main() {
    for (n = 69; n > 16; n--) {
        cc = n / 2;
        if (n % 2 == 1) cc = 100;

        ll sum = 0;
        for (int i = 0; i < n; i++) {
            a.push_back(i);
            was[i + cc] = 1;
            sum += calc();
            a.pop_back();
            was[i + cc] = 0;
        }
        cerr << n << endl;
        cout << "M[" << n << "] = " << sum << ";\n" << endl;
    }
}
