#include "teams.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)

typedef long long ll;

using namespace std;

const int dd = (int)1e5 + 7;

pair<int, int> G[dd];
int n;
int pr[dd], used[dd];
vector<vector<int> > E;

void init(int N, int A[], int B[]) {
	n = N;
	for (int i = 0; i < n; i++)
		G[i] = { A[i], B[i] };
	sort(G, G + n);
}

int can(int M, int K[]) {

	if (accumulate(K, K + M, 0) > n)
		return 0;

	sort(K, K + M);

	int j = 0;
	multiset<int> S;

	for (int i = 0; i < M; i++) {
		while (j < n && G[j].first <= K[i]) {
			S.insert(G[j].second);
			j++;
		}

		//err("k = %d, S = { ", K[i]);
		//for (int x : S) err("%d, ", x); err("}\n");

		for (int i1 = 0; i1 < K[i]; i1++) {
			auto it = S.lower_bound(K[i]);
			if (it == S.end())
				return 0;
			S.erase(it);
		}
	}
	return 1;
}