#include "icc.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)

typedef long long ll;

using namespace std;
struct dsu {
	int P[107];

	dsu() { for (int i = 0; i < 107; i++) P[i] = i; }

	int get(int v) { return v == P[v] ? v : P[v] = get(P[v]); }

	void un(int a, int b) {
		a = get(a), b = get(b);
		if (a != b) P[b] = a;
	}
} J;

int a[107], b[107];

int ask(vector<int> A, vector<int> B) {
	int n = (int)A.size();
	int m = (int)B.size();

	for (int i = 0; i < n; i++)
		a[i] = A[i] + 1;
	for (int i = 0; i < m; i++)
		b[i] = B[i] + 1;

	return query(n, m, a, b);
}

void run(int n) {

	for (int it = 0; it < n - 1; it++) {
		vector<int> cur;
		for (int i = 0; i < n; i++) {
			if (J.get(i) == i)
				cur.push_back(i);
		}

		/*err("cur = {");
		for (int x : cur) {
            err(" %d,", x);
		}
		err(" }\n");
        */
		int len = (int)cur.size();

		int lg = 0;
		for (int i = 0; i < 20; i++) {
			if (((len - 1) >> i) & 1)
				lg = i;
		}
		//err("lg = %d\n", lg);

		for (int lev = 0; lev <= lg; lev++) {

			vector<int> A, B;

			for (int i = 0; i < len; i++) {
				if ((i >> lev) & 1) {
                    for (int j = 0; j < n; j++) {
                        if (J.get(j) == J.get(cur[i])) {
                            A.push_back(j);
                        }
                    }
				} else {
                    for (int j = 0; j < n; j++) {
                        if (J.get(j) == J.get(cur[i])) {
                            B.push_back(j);
                        }
                    }
				}
			}

			if (lev == lg || ask(A, B)) {
				vector<int> C, D;
				set<int> Q;

				for (int x : A)
					Q.insert(J.get(x));

				for (int i = 0; i < n; i++) {
					if (Q.count(J.get(i)))
						C.push_back(i);
					else
						D.push_back(i);
				}

				int l = 0, r = (int)C.size();

				while (r - l > 1) {
                    int m = (l + r) / 2;

                    vector<int> F;
                    for (int j = 0; j < m; j++) {
                        F.push_back(C[j]);
                    }

                    if (ask(F, D))
                        r = m;
                    else
                        l = m;
				}

				int ind1 = r - 1;


				l = 0, r = D.size();

				while (r - l > 1) {
                    int m = (l + r) / 2;

                    vector<int> F;
                    for (int j = 0; j < m; j++) {
                        F.push_back(D[j]);
                    }

                    if (ask(C, F))
                        r = m;
                    else
                        l = m;
				}

				int ind2 = r - 1;

				setRoad(C[ind1] + 1, D[ind2] + 1);
                J.un(C[ind1], D[ind2]);
				break;
			}

		}
	}

}
