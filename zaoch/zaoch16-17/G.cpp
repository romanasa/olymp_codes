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
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

const int dd = (int)107;

void turn(int tp) {
	printf("turn ");
	if (tp == 1) printf("on");
	else printf("off");
	printf("\n");
	fflush(stdout);
}

void go(int id, int tp) {
	printf("go %d ", id);
	if (tp == 0) printf("keep");
	else printf("lock");
	printf("\n");
	fflush(stdout);
}

char tp[11];
int cnt, id;

void get() {
	scanf("%s", tp);
	if (tp[0] != 'l')
		scanf("%d %d", &cnt, &id);
}

pair<int, int> dfs() {

	get();

	int x = id;

	if (tp[0] == 'l')
		return { -1, -1 };

	if (tp[1] == 'n')
		return { 0, x };

	turn(1);

	int t = cnt;

	for (int i = 1; i <= t; i++) {
		go(i, 0);
		auto c = dfs();
		
		if (c.first == -1) continue;

		go(c.second, c.first);
		get();
	}

	return { 1, x };
}

mt19937 rnd(1488);

int solve() {


	for (int it = 0; it < 5000; it++) {
		get();
		turn(0);
		int id = rnd() % cnt + 1;
		go(id, 0);
	}

	dfs();

	printf("done\n");
	fflush(stdout);

	return 0;
}