#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double ld;

int solve();
#define TASK "split"
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

int main() {
	solve();
}

const int dd = (int)5e5 + 7;

vector<int> E[dd];
vector<int> Q;
int cnt;

void add(int a, int b) {
	E[a].push_back(b);
	++cnt;
}

int n, m, p;

int nv;

void go(int l, int r, vector<int> &T) {
	//err("[%d, %d], T = {", l, r);
	//for (int x : T) err(" %d,", x); err(" }\n");
	if (r - l <= 1) {
		for (int x : T) {
			for (int j = l; j <= r; j++)
				add(x, Q[j]);
		}
	} else {

		int m = (l + r) / 2;

		vector<int> A, B;

		
		for (int i = l; i <= m; i++) {
			A.push_back(nv++);
		}

		for (int i = m + 1; i <= r; i++) {
			B.push_back(nv++);
		}
		
		//if (A.size() > B.size()) B.push_back(nv++);

		//err("A = {"); for (int x : A) err(" %d,", x); err(" }\n");
		//err("B = {"); for (int x : B) err(" %d,", x); err(" }\n");
		
		for (int i = 0; i < (int)T.size(); i++) {
			int cur = i % (int)A.size();
			add(T[i], A[cur]);
			if (cur == (int)B.size())
				cur--;
			add(T[i], B[cur]);
		}

		go(l, m, A);
		go(m + 1, r, B);

	}
}

int solve() {
	int test;
	scanf("%d %d %d %d", &test, &n, &m, &p);

	nv = 2 * n;
	
	int CC = 4;	
	vector<int> T;
	for (int i = 0; i < n; i += CC) {
		int cur = nv++;
		for (int j = i; j < min(i + CC, n); j++)
			add(j, cur);
		T.push_back(cur);
	}
	
	for (int i = 0; i < n; i += CC) {
		int cur = nv++;
		for (int j = i; j < min(i + CC, n); j++)
			add(cur, j + n);
		Q.push_back(cur);
	}
	
		
	go(0, (int)Q.size() - 1, T);

	vector<int> used(nv);
	queue<int> q;
	
	for (int i = 0; i < n; i++) {
		q.push(i);
		used[i] = 1;
	}
	
	while (q.size()) {
		int v = q.front();
		q.pop();
		
		for (int to : E[v]) {
			if (!used[to]) {
				used[to] = 1;
				q.push(to);
			}
		}
	}
	
	int qq = 0;
	
	for (int v = 0; v < nv; v++) {
		for (int to : E[v]) {
			qq += (used[v] && used[to]);
		}
	}
	
	printf("%d %d\n", nv, qq);
	for (int v = 0; v < nv; v++) {
		for (int to : E[v]) {
			if (used[v] && used[to])
				printf("%d %d\n", v + 1, to + 1);
		}
	}

	return 0;
}
