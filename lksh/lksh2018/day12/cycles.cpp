#define _CRT_SECURE_NO_DEPRECATE
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <iostream>
#include <iterator>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstring>
#pragma comment(linker, "/STACK:66777216")
using namespace std;
#define pb push_back
#define ppb pop_back
#define pi 3.1415926535897932384626433832795028841971
#define mp make_pair
#define x first
#define y second
#define pii pair<int,int>
#define pdd pair<double,double>
#define INF 1000000000
#define FOR(i,a,b) for (int _n(b), i(a); i <= _n; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;i--)
#define all(c) (c).begin(), (c).end()
#define SORT(c) sort(all(c))
#define rep(i,n) FOR(i,1,(n))
#define rept(i,n) FOR(i,0,(n)-1)
#define L(s) (int)((s).size())
#define C(a) memset((a),0,sizeof(a))
#define VI vector <int>
#define ll long long

int a,b,c,d,i,j,n,m,k;
VI sm[300001], sm_light[300001], sm_heavy[300001];
bool is_heavy[300001];
VI heavy, light;
bool used[300001];
int main() {
	freopen("owls.in","r",stdin);
	freopen("owls.out","w",stdout);

	scanf("%d%d", &n, &m);
	k = (int)sqrt(2.0 * m);
	rept(i, m) {
		scanf("%d%d", &a, &b); --a; --b;
		sm[a].pb(b); sm[b].pb(a);
	}

	rept(i, n) {
		if (L(sm[i]) > k) {
			heavy.pb(i);
			is_heavy[i] = 1;
		} else {
			light.pb(i);
		}
	}

	rept(i, n) {
		rept(j, L(sm[i])) {
			if (is_heavy[sm[i][j]]) sm_heavy[i].pb(sm[i][j]); else
			sm_light[i].pb(sm[i][j]);
		}
	}

	int ans = 0;
	// all heavy
	rept(i, L(heavy)) {
		a = heavy[i];
		rept(j, L(sm_heavy[a])) used[sm_heavy[a][j]] = 1;
		rept(j, L(sm_heavy[a])) {
			b = sm_heavy[a][j];
			if (a > b) continue;
			rept(z, L(sm_heavy[b])) {
				c = sm_heavy[b][z];
				if (c < b) continue;
				if (used[c]) ++ans;
			}
		}

		rept(j, L(sm_heavy[a])) used[sm_heavy[a][j]] = 0;
	}

	// 2 heavy, 1 light
	rept(i, L(heavy)) {
		a = heavy[i];
		rept(j, L(sm_heavy[a])) used[sm_heavy[a][j]] = 1;
		rept(j, L(sm_light[a])) {
			b = sm_light[a][j];
			rept(z, L(sm_heavy[b])) {
				c = sm_heavy[b][z];
				if (c < a) continue;
				if (used[c]) ++ans;
			}
		}
		rept(j, L(sm_heavy[a])) used[sm_heavy[a][j]] = 0;
	}

	// 1 heavy, 2 light
	rept(i, L(heavy)) {
		a = heavy[i];
		rept(j, L(sm_light[a])) used[sm_light[a][j]] = 1;
		rept(j, L(sm_light[a])) {
			b = sm_light[a][j];
			rept(z, L(sm_light[b])) {
				c = sm_light[b][z];
				if (c < b) continue;
				if (used[c]) ++ans;
			}
		}
		rept(j, L(sm_light[a])) used[sm_light[a][j]] = 0;
	}

	// all light
	rept(i, L(light)) {
		a = light[i];
		rept(j, L(sm_light[a])) used[sm_light[a][j]] = 1;
		rept(j, L(sm_light[a])) {
			b = sm_light[a][j];
			if (a > b) continue;
			rept(z, L(sm_light[b])) {
				c = sm_light[b][z];
				if (c < b) continue;
				if (used[c]) ++ans;
			}
		}
		rept(j, L(sm_light[a])) used[sm_light[a][j]] = 0;
	}


	printf("%d\n", ans);
}
