#include <bits/stdc++.h>

#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#define x first
#define y second
#define mp make_pair
#define pub push_back
#define all(v) (v).begin(), (v).end()

using namespace std;

typedef long long ll;
typedef double db;

int MAX_VAL = 12 * 1000000;
int n;
vector<int> a[12 * 1000000 + 7];

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    cin >> n;
    for (int i = 2; i * i <= MAX_VAL; i++){
        for (int j = 1; j < i; j++){
            if (j > n) break;
            a[i * i - j * j].pub(j);
        }
    }
    for (int i = 0; i < MAX_VAL + 7; i++) sort(all(a[i]));
    ll ans = 0;

    for (int i = 1; i <= n; i++) for (int j = i; j <= n; j++){
        int pos = i * i + j * j;
        int vl = -1, vr = a[pos].size();
        while(vl + 1 < vr){
            int vm = (vl + vr) >> 1;
            if (a[pos][vm] < j)
                vl = vm;
            else
                vr = vm;
        }
        if (i == 1 && j == 4){
            cout << a[pos][vr] << endl;
        }
        cout << i << ' ' << j << ' ' << (int)a[pos].size() - vr << endl;
        ans += (int)a[pos].size() - vr;
    }

    cout << ans;
    return 0;
}
