#include "grader.h"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int dd = (int)1e6 + 7;

struct ev { int w, s, ind; };

inline bool cmp1(ev a, ev b) { return a.w < b.w; }

inline bool cmp2(ev a, ev b) { return a.s < b.s; }

ev H[dd], G[dd];
int U[dd];

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {

    sort(X, X + A);
	sort(Y, Y + B);

	for (int i = 0; i < T; i++) {
		if (W[i] >= X[A - 1] && S[i] >= Y[B - 1])
			return -1;
		H[i] = { W[i], S[i], i };
		G[i] = { W[i], S[i], i };
	}

	sort(H, H + T, cmp1);
	sort(G, G + T, cmp2);

	int l = 0, r = T + 1;

    while (r - l > 1) {
    	int m = (l + r) / 2;
    	int ok = 1;
    	
		{
			priority_queue<pair<int, int> > J;

			memset(U, 0, sizeof(int) * T);

			int j = 0;
			for (int i = 0; i < A; i++) {
				while (j < T && H[j].w < X[i]) {
					J.push({ H[j].s, H[j].ind });
					j++;
				}

				for (int k = 0; k < m; k++) {
					if (!J.size())
						break;
					int v = J.top().second;
					J.pop();
					U[v] = 1;
				}
			}
		}

		{
			priority_queue<pair<int, int> > J;

			int j = 0;
			for (int i = 0; i < B; i++) {
				while (j < T && G[j].s < Y[i]) {
					J.push({ G[j].w, G[j].ind });
					j++;
				}

				for (int k = 0; k < m; ) {
					if (!J.size())
						break;

					int v = J.top().second;
					J.pop();

					if (!U[v]) {
						U[v] = 1;
						k++;
					}

				}
			}
		}

    	if (*min_element(U, U + T) == 1)
    		r = m;
    	else
    		l = m;
    }

	return r;
}