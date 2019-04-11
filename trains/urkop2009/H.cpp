#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const double pi = atan2(1.0, 1.0) * 4;

#define db double
double r, a;

db getFunc(db val){
    val = val / (db)180 * pi;
    return sqrt(max(0.0, 2 * r * r - 2 * r * r * cos(val)));
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN
    cin >> r >> a;
    int cnt = 0;
    for (int it = 0; ;it++){
        if (2 * a * (it + 1) >= 360){
            cnt = it;
            break;
        }
    }

    db ost = 360 - 2 * a * cnt;

    cout.precision(10);
    cout << fixed << r + (cnt - 1) * getFunc(2 * a) + getFunc(ost) << "\n";
    return 0;
}

