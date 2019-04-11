#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int sz = (1 << 20) - 1;

struct MyHash {
	pair<int, int> T[sz + 7];
	
	MyHash() { fill(T, T + sz + 7, make_pair(-1, 0)); }
	
	int& operator [](ll x) {
		int h = (x & sz);
		for (; T[h].first != -1; h = (h + 1) & sz) {
			if (T[h].first == x) return T[h].second;
		}
		T[h].first = x;
		return T[h].second;
	}
} T;

const int MAXN = 3 * 1e5 + 1;

int deg[MAXN];

MyHash mapp;
vector<int> mas[MAXN];

pair<ll, ll> req[MAXN];

bool cmp(int a, int b)
{
        if (mas[a].size() != mas[b].size())
                return mas[a].size() < mas[b].size();
        else
                return a < b;
}

ll get(int a, int b) {
	return 1ll * MAXN * a + b;
}

int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
        //freopen("input.txt", "r", stdin);
        //freopen("owls.out", "w", stdout);

        ll n, m;
        /*scanf("%d%d", &n, &m);//*/cin >> n >> m;

        for (int i = 0; i < m; ++i)
        {
                ll u, v;
                /*scanf("%d%d", &u, &v);//*/cin >> u >> v;

                --u;
                --v;

                deg[u] += 1;
                deg[v] += 1;
                
                mapp[get(u, v)]++;
                mapp[get(v, u)]++;

                mas[v].emplace_back(u);
                mas[u].emplace_back(v);

                req[i] = { u, v };
        }
        for (int i = 0; i < n; i++)
        {
                sort(mas[i].begin(), mas[i].end(), cmp);
        }

        ll ans = 0;

        for (int i = 0; i < m; ++i)
        {
                ll u = req[i].first;
                ll v = req[i].second;

                if (deg[u] < deg[v] || (deg[u] == deg[v] && u < v))
                        swap(v, u);

                for (auto w : mas[v])
                {
                        if (mas[w].size() > mas[v].size() || (mas[w].size() == mas[v].size() && w > v))
                                break;
                        if (mapp[get(u, w)])
                        {
                                //cout << u << " " << v << " " << w << endl;
                                ans += 1;
                        }
                }
        }

        printf("%d", ans);//cout << ans / 3 << endl;
        return 0;
}