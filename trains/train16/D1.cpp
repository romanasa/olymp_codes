#include <bits/stdc++.h>

using namespace std;

int n;
int a[111];
int cnt[111];

bool f = 1;

vector<int> st;
void calc(int v, int sum){
    if (v == n){
        //f = 1;
        //return;
        reverse(st.begin(), st.end());
        for (int x : st) cout << x << ' ';
        exit(0);
    }
    for (int i = 1; i <= 13; i++) if (cnt[i] && sum % i == 0){
        cnt[i]--;
        st.push_back(i);
        calc(v + 1, sum - i);
        cnt[i]++;
        st.pop_back();
        //if (f) return;
    }
}

int main(){
    //freopen("01", "r", stdin);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    int sum  = 0;
    for (int i = 0; i < n; i++){
            cnt[a[i]]++;
            sum += a[i];
    }
    calc(0, sum);
    cout << -1;
    exit(0);
    for (int i1 = 0; i1 <= 4; i1++)
    for (int i2 = 0; i2 <= 4; i2++)
    for (int i3 = 0; i3 <= 4; i3++)
    for (int i4 = 0; i4 <= 0; i4++)
    for (int i5 = 0; i5 <= 0; i5++)
    for (int i6 = 0; i6 <= 0; i6++)
    for (int i7 = 0; i7 <= 0; i7++)
    for (int i8 = 0; i8 <= 0; i8++)
    for (int i9 = 0; i9 <= 0; i9++)
    for (int i10 = 0; i10 <= 0; i10++)
    for (int i11 = 0; i11 <= 4; i11++)
    for (int i12 = 0; i12 <= 4; i12++)
    for (int i13 = 0; i13 <= 4; i13++){
        n = i1 + i2 + i3 + i4 + i5 + i6 + i7 + i8 + i9 + i10 + i11 + i12 + i13;
        cnt[13] = i1;
        cnt[12] = i2;
        cnt[11] = i3;
        cnt[10] = i4;
        cnt[9] = i5;
        cnt[8] = i6;
        cnt[7] = i7;
        cnt[6] = i8;
        cnt[5] = i9;
        cnt[4] = i10;
        cnt[3] = i11;
        cnt[2] = i12;
        cnt[1] = i13;
        f = 0;
        calc(0, 0);
        cout << i1 << ' ' << i2 << ' ' << i3 << ' ' << i4 << ' ' << i5 << ' ' << i6 << ' ' << i7 << ' ' << i8 << ' ' << i9 << ' ' << i10 << ' ' << i11 << ' ' << i12 << ' ' << i13 << ' ' << f << endl;
        //exit(0);
    }
    calc(0, 0);
    cout << -1;
    return 0;
}
