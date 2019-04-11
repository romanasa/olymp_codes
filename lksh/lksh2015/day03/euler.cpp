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

#define TASK "euler"

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

const int MAXN = 1e5 + 7;
int ind[MAXN];

struct edge {
    int to, num;
    bool del;
    edge(int _to, int _num) {
        to = _to, num = _num, del = false;
    }
};

vector<set<int> > was;
vector<vector<edge> > e;
vector<int> ans;

void find_path(int v) {
    while (ind[v] < e[v].size()) {

        if (e[v][ind[v]].del) {
            ind[v]++;
            continue;
        }

        int to = e[v][ind[v]].to;

        e[v][ind[v]].del = true;
        e[to][e[v][ind[v]].num].del = true;
        ind[v]++;

        find_path(to);
    }

    ans.pk(v + 1);
}

int solve() {
    int n, ok = 0, start = 0;
    cin >> n;
    e.resize(n);
    was.resize(n);
    forn(i, n) {
        int k;
        cin >> k;
        if (k % 2) 
            ok++, start = i;
        
        forn(j, k) {
            int to;
            cin >> to;
            to--;
            if (!was[i].count(to)) {
                int num_to = e[i].size(), num_i = e[to].size();
                e[i].pk(edge(to, num_i));
                e[to].pk(edge(i, num_to));
                was[to].insert(i);
            }
        }
    }

    if (ok == 3 || ok == 1)
        cout << -1;
    else {
        find_path(start);
        cout << ans.size() - 1 << "\n";
        forn(i, ans.size())
            cout << ans[i] << " ";
    }

    return 0;
}