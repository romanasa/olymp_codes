#include <bits/stdc++.h>

using namespace std;

#define ll long long

int getSum(int x){
    int ans = 0;
    while(x){
        ans += x % 10;
        x /= 10;
    }
    return ans;
}


int main() {
    freopen("digits.in", "r", stdin);
    freopen("digits.out", "w", stdout);

    int sum = 0;

    //for (int i = 1; i <= 99999; i++) sum += getSum(i);

    //cout << sum << endl;

    int n;
    cin >> n;
    cout << 45 * (ll)n;
    for (int i = 0; i < n - 1; i++) cout << 0;
}
