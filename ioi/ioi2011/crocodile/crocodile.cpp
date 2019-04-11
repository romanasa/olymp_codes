#ifdef HOME
	#include "crocodile.h"
#else
	#include "grader.h"
#endif

#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

vector<vector<pair<ll, ll> > > E;

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]) {
	E.resize(N);

	for (int i = 0; i < M; i++) {
		E[R[i][0]].push_back({ R[i][1], L[i] });
		E[R[i][1]].push_back({ R[i][0], L[i] });
	}

	vector<ll> dist1(N, (ll)1e9);
	vector<ll> dist2(N, (ll)1e9);

	set<pair<ll, int> > S;

	for (int j = 0; j < K; j++) {
		int i = P[j];
		dist1[i] = dist2[i] = 0;
        S.insert({ dist2[i], i });
	}

	for (int i = 0; i < N; i++) {
	}

	while (S.size()) {
		int v = S.begin()->second;
		S.erase(S.begin());

		for (auto e : E[v]) {

			ll cur = dist2[v] + e.second;

			int to = e.first;

			if (cur < dist1[to]) {

                S.erase({ dist2[to], to });

				dist2[to] = dist1[to];
				dist1[to] = cur;

                S.insert({ dist2[to], to });

			} else if (cur < dist2[to]) {
				S.erase({ dist2[to], to });
				dist2[to] = cur;
				S.insert({ dist2[to], to });
			}
		}
	}
	return dist2[0];
}


