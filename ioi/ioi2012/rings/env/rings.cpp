#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

#include "grader.h"

using namespace std;

int N;

const int dd = 1e6 + 7;

vector<vector<int> > E;

struct dsu {
	int P[dd], R[dd];
	void clear() { for (int i = 0; i < dd; i++) P[i] = i, R[i] = 1; }
	int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }
	void un(int a, int b) {
		a = get(a), b = get(b);
		if (a != b) {
			if (R[b] > R[a]) swap(a, b);
			P[b] = a, R[a] += R[b];
		}
	}
} J, G[4];

int state = 1;
int cnt;


void Init(int N_) {
	N = N_;
	E.resize(N);
	J.clear();
	for (int i = 0; i < 4; i++) G[i].clear();
}

int used[dd], deg[dd];
int cycle[dd];
vector<int> C;

bool dfs(int v, int pr = -1) {
	used[v] = 1;
	
	for (int to : E[v]) {
		if (pr != to && used[to] == 1) {
			cnt++;
			cycle[v] = true;
			C.push_back(v);
			return true;
		}
		if (used[to] == 0 && dfs(to, v)) {
			cnt++;
			cycle[v] = true;
			C.push_back(v);
			return true;
		}
	}
	used[v] = 2;
	return false;
}

int blocked[4];
int lin[4], Q[4][dd];

void make(int bl, int ind) {
	blocked[ind] = bl;
	lin[ind] = 1;
	for (int v = 0; v < N; v++) {
		for (int to : E[v]) {
			if (v == bl || to == bl) continue;
			if (v > to) continue;
			if (G[ind].get(v) == G[ind].get(to)) {
				lin[ind] = 0;
			}
			Q[ind][v]++, Q[ind][to]++;
			G[ind].un(v, to);
		}
	}
}



void Link(int A, int B) {
	//err("add %d---%d, state = %d\n--------\n", A, B, state);
	
	E[A].push_back(B);
	E[B].push_back(A);
	deg[A]++, deg[B]++;
	
	if (state == 1) {
		if (J.get(A) == J.get(B)) {
			dfs(A);
			state = 2;
		} else {
			if (deg[A] == 3) {
				make(A, 0);
				make(E[A][0], 1);
				make(E[A][1], 2);
				make(E[A][2], 3);
				state = 3;
			} else if (deg[B] == 3) {
				make(B, 0);
				make(E[B][0], 1);
				make(E[B][1], 2);
				make(E[B][2], 3);
				state = 3;
			}
		}
	} else if (state == 2) {
		
		if (deg[A] < 3 && deg[B] < 3) {
			if (J.get(A) == J.get(B)) {
				state = 4;
			} 
		} else {
			if (deg[A] == 3) {
				make(A, 0);
				make(E[A][0], 1);
				make(E[A][1], 2);
				make(E[A][2], 3);
				state = 3;
			} else if (deg[B] == 3) {
				make(B, 0);
				make(E[B][0], 1);
				make(E[B][1], 2);
				make(E[B][2], 3);
				state = 3;
			}
		}
	
	} else if (state == 3) {

		for (int ind = 0; ind < 4; ind++) {
			if (!lin[ind]) continue;

			if (A == blocked[ind] || B == blocked[ind]) continue;

			Q[ind][A]++, Q[ind][B]++;

			if (Q[ind][A] == 3 || Q[ind][B] == 3) {
				lin[ind] = 0;
				continue;
			}

			if (G[ind].get(A) == G[ind].get(B))
				lin[ind] = 0;
			G[ind].un(A, B);
		}

	}
	
	J.un(A, B);
	//err("state = %d\n", state);

	/*if (state == 3) {
		for (int ind = 0; ind < 4; ind++) {
			err("ind = %d\n", ind);

			err("lin = %d, blocked = %d\n", lin[ind], blocked[ind]);


		}
	}*/
}

int CountCritical() {
	if (state == 1) {
		return N;
	}
	if (state == 2) {
		return cnt;
	}
	if (state == 3) {
		int ans = 0;
		for (int i = 0; i < 4; i++) ans += lin[i];
		return ans;
	}
	return 0;
}
