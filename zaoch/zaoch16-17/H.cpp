#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>
#include <random>

using namespace std;

typedef long long ll;
typedef double ld;

int solve();

#define TASK "fuel"
#define err(...) //fprintf(stdout, __VA_ARGS__), fflush(stdout)

int main() {
#ifdef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

const int dd = (int)1e6 + 7;

char s[dd];

int nv = 2, root = 1;
int go[dd][2], term[dd];
int suf[dd], used[dd], pr[dd], c[dd];
int supersuf[dd], cnt[dd];
int q[dd], iL, iR;

vector<vector<int> > E;

void add() {
	int cur = root;
	int n = strlen(s);

	for (int i = 0; i < n; i++) {
		if (go[cur][s[i] - '0'] == -1) {
			go[cur][s[i] - '0'] = nv++;
		}
		cur = go[cur][s[i] - '0'];
	}
	term[cur]++;
}

int bad[dd], win[dd], deg[dd];

void calc(int v) {
	used[v] = true;
	for (int to : E[v]) {

		if (used[to]) continue;

		if (bad[v]) {
			win[to] = true;
		} else if (--deg[to] == 0) {
			bad[to] = 1;
		} else {
			continue;
		}
		calc(to);
	}
}

int solve() {

	for (int i = 0; i < dd; i++)
		go[i][0] = go[i][1] = -1;
	go[0][0] = go[0][1] = 1;

	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		scanf("%s", s);
		add();
	}

	q[iR++] = root;

	while (iL < iR) {
		int v = q[iL++];

		if (v == root) {
			suf[v] = 0;
			supersuf[v] = 0;
		} else {
			suf[v] = go[suf[pr[v]]][c[v]];
		}
		term[v] += term[suf[v]];

		for (int i = 0; i < 2; i++) {

			if (go[v][i] != -1) {
				q[iR++] = go[v][i];
				pr[go[v][i]] = v;
				c[go[v][i]] = i;
			} else {
				go[v][i] = go[suf[v]][i];
			}

		}
	}


	E.resize(nv);

	for (int v = 0; v < nv; v++) {
		for (int ind = 0; ind < 2; ind++) {
			E[go[v][ind]].push_back(v);
			deg[v]++;
		}
	}

	for (int v = 0; v < nv; v++) {
		if (term[v]) {
			used[v] = 1;
			win[v] = 1;
		}
	}
	
	for (int v = 0; v < nv; v++) {
		if (term[v]) {
			calc(v);
		}
	}

	scanf("%s", s);

	int cur = root;

	for (int i = 0; i < m; i++) {
		cur = go[cur][s[i] - '0'];
	}

	if (bad[cur]) {
		puts("Iskander");
	} else if (win[cur]) {
		puts("Olya");
	} else {
		puts("Friendship");
	}

	return 0;
}