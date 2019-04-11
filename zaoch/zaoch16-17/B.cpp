#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:256000000")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <numeric>
#include <queue>
#include <cassert>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef long double ld;

#define TASK "sorting"

int solve();

int main() {
#ifdef HOME
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
}

const int dd = (int)3e5 + 7;

char S[dd];
int P[dd];

int solve() {
	int k;
	scanf("%d", &k);
	scanf("%s", S);
	
	int n = strlen(S);

	while (S[n - 1] == '0') --n;

	for (int i = 0; i < n; i++) P[i + 1] = P[i] + (S[i] == '1');

	for (int i = 0; i < n; i++) {
		if (S[i] == '0') continue;
		int ind = lower_bound(P + 1, P + n + 1, P[i + 1] + k) - P;
		if (ind == n + 1) {
			printf("%d ", (n - i - 1) * 2);
		} else {
			printf("%d ", (ind - i - 1) * 2);
		}
	}
	return 0;
}