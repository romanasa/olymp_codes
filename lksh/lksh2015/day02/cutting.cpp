#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:66777216")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (int i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "cutting"

const double eps = 1e-7;
const double pi = acos(-1.0);

const int INF = (int)2e9 + 1;
const ll LINF = (ll)8e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef _DEBUG
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
    //freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
    solve();
    return 0;
}

//int tmm = 1, used[MAXN], enter[MAXN], up[MAXN];
//
//void dfs(int v) {
//    used[v] = true;
//    enter[v] = up[v] = tmm++;
//    forn(i, e[v].size()) {
//        int to = e[v][i];
//        if (!used[to]) {
//            dfs(to);
//            if (up[to] >= enter[to]) {
//                //u, v - most;
//            }
//            up[v] = min(up[v], up[to]);
//        }
//        else {
//            up[v] = min(up[v], enter[to]);
//        }
//    }
//}

const int MAXN = 1e5 + 7;
int p[MAXN], cnt[MAXN];

int get(int v) {
    return v == p[v] ? v : p[v] = get(p[v]);
}

void un(int a, int b) {
    a = get(a);
    b = get(b);
    if (a != b) {
        if (cnt[a] < cnt[b])
            swap(a, b);
        p[b] = a, cnt[a] += cnt[b];
    }
}

int solve() {
    int n, m, k;
    cin >> n >> m >> k;
    forn(i, n + 1)
        p[i] = i, cnt[i] = 1;
    
    forn(i, m) {
        int a, b;
        cin >> a >> b;
    }
    vector<string> quer(k), ans;
    vector<int> first(k), second(k);
    forn(i, k)
        cin >> quer[i] >> first[i] >> second[i];
    for (int i = k - 1; i >= 0; i--) {
        if (quer[i] == "ask")
            if (get(first[i]) == get(second[i]))
                ans.pk("YES");
            else
                ans.pk("NO");
        else
            un(first[i], second[i]);
    }
    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i] << "\n";
    return 0;
}