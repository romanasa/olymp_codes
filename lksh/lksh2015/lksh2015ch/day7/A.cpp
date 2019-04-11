//#define _CRT_SECURE_NO_WARNINGS
//#pragma comment(linker, "/STACK:66777216")
//#include <iostream>
//#include <cstdio>
//#include <cmath>
//#include <vector>
//#include <ctime>
//#include <map>
//#include <set>
//#include <string>
//#include <queue>
//#include <deque>
//#include <cassert>
//#include <cstdlib>
//#include <bitset>
//#include <algorithm>
//#include <string>
//#include <list>
//#include <fstream>
//#include <cstring>
//
//using namespace std;
//
//typedef unsigned long long ull;
//typedef long long ll;
//typedef long double ld;
//
//#define forn(i, n) for (int i = 0; i < (int)n; i++)
//#define fornn(i, q, n) for (int i = q; i < (ll)n; i++)
//#define mp make_pair
//#define pk push_back
//#define all(v) v.begin(), v.end()
//#define times clock() * 1.0 / CLOCKS_PER_SEC
//#define prev pprev
//
//#define TASK "sum2"
//
//const double eps = 1e-7;
//const double pi = acos(-1.0);
//
//const ll INF = (ll)2e9 + 1;
//const ll LINF = (ll)8e18;
//const ll inf = (ll)2e9 + 1;
//const ll linf = (ll)8e18;
//const ll MM = (ll)1e9 + 7;
//
//bool used[MAXN];
//
//int d[MAXN];
//
//vector<int> g[MAXN];
//
//void bfs(int s)
//{
//    used[s] = 1;
//    queue<int> q;
//    d[s] = 0;
//    q.push(s);
//    while (!q.empty())
//    {
//        int v = q.front();
//        q.pop();
//        int to = (v + 1) % n;
//        int to1 = (v * 2) % n;
//        if (!used[to] && d[to] > d[v] + 1)
//        {
//            used[to] = 1;
//            q.push(to);
//            d[to] = d[v] + 1;
//        }
//        if (!used[to1])
//        {
//            used[to1] = 1;
//            q.push(to1);
//        }
//    }
//        
//    }
//}
//
//int main()
//{
//#ifdef _DEBUG
//	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
//#else
//	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
//	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
//#endif
//	solve();
//	return 0;
//}
//
//int p[207];
//
//int solve() {
//    cin >> n >> a >> b;
//    bfs(a);
//    cout << d[b];
//}