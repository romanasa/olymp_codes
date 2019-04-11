#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int getSum(int x){
    int sum = 0;
    while(x){
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int> > t;
    for (int i = 1; i < 100000; i++) t.push_back(make_pair(getSum(i), i));
    sort(t.begin(), t.end());
    reverse(t.begin(), t.end());
    vector<int> ans;

    for (auto c : t){
        if (c.first <= n){
            n -= c.first;
            ans.push_back(c.second);
        }
    }

    cout << ans.size() << "\n";
    for (int x : ans) cout << x << ' ';
}

