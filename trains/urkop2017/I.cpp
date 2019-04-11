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

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#endif // WIN
    int x, y;
    cin >> x >> y;
    set<int> se;
    for (int i = 1; i <= 6; i++) se.insert(i);
    se.erase(x);
    se.erase(y);
    se.erase(7 - x);
    se.erase(7 - y);
    cout << "+-+\n";
    cout << "|" << *se.begin() << "|\n";
    cout << "+-+-+-+-+\n";
    cout << "|" << x << "|" << y << "|" << 7 - x << "|" << 7 - y << "|\n";
    cout << "+-+-+-+-+\n";
    cout << "|" << *(--se.end()) << "|\n";
    cout << "+-+";
    return 0;
}
