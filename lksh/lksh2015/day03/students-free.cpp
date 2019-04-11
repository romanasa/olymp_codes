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

#define TASK "students-free"

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

const int MAXN = 2e5 + 7;
int ind[MAXN], used[MAXN];

struct edge {
    int to, num;
    bool del;
    edge(int _to, int _num) {
        to = _to, num = _num, del = false;
    }
};

vector<vector<edge> > e;
vector<int> ans;

void find_path(int v) {
    used[v] = true;
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

    ans.pk(v);
}

char nextc(char c) {
    return c == 'W' ? 'M' : 'W';
}

vector<map<int, char> > num;
int s, n;

bool ok(int v) {
    return (v >= 1 && v <= s);
}

int solve() {
    vector<pair<int, int> > edges;
    cin >> s >> n;
    num.resize(s * 4 + 7);
    e.resize(s + s + 7);
    forn(j, n) {
        int i, to;
        cin >> i >> to;
        edges.pk(mp(i, to));
        i--, to--;
        to += s;
        int num_to = e[i].size(), num_i = e[to].size();
        e[i].pk(edge(to, num_i));
        e[to].pk(edge(i, num_to));
    }
    forn(i, s)
        if (e[i].size() % 2) {
            int to = s + s;
            int num_to = e[i].size(), num_i = e[to].size();
            e[i].pk(edge(to, num_i));
            e[to].pk(edge(i, num_to));
        }

    fornn(i, s, s + s)
        if (e[i].size() % 2) {
            int to = s + s + 1;
            int num_to = e[i].size(), num_i = e[to].size();
            e[i].pk(edge(to, num_i));
            e[to].pk(edge(i, num_to));
        }

    if (e[s + s].size() % 2) {
        int i = s + s, to = s + s + 1;
        int num_to = e[i].size(), num_i = e[to].size();
        e[i].pk(edge(to, num_i));
        e[to].pk(edge(i, num_to));
    }

    forn(i, s + s) {
        if (used[i])
            continue;
        ans.clear();
        find_path(i);
        
        forn(i, ans.size()) {
            if (ans[i] >= s && ans[i] < s + s)
                ans[i] -= s;
            ans[i]++;
        }

        vector<pair<int, int> > res;

        forn(i, ans.size() - 1) {
            if (i % 2 == 0)
                res.pk(mp(ans[i], ans[i + 1]));
            else
                res.pk(mp(ans[i + 1], ans[i]));
        }

        char c = 'M';
        forn(i, res.size()) {
            num[res[i].first][res[i].second] = c;
            c = nextc(c);
        }
    }

    
    forn(i, edges.size())
        if (ok(edges[i].first) && ok(edges[i].second))
            cout << num[edges[i].first][edges[i].second];
    return 0;
}