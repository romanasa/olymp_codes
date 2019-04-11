#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int dd = (int)1e6 + 7;

int P[dd];
int A[dd], B[dd];

vector<int> E[dd], H[dd];

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
		scanf("%d", &P[i]);

	int t;
	scanf("%d", &t);
	
	for (int i = 0; i < t; ++i) {
		int x;
		scanf("%d", &x);	
		P[x - 1] *= -1;
	}
	
	auto no = []() {
		puts("NO");
		exit(0);
	};
	
	vector<int> st;
	for (int i = n - 1; i >= 0; i--) {
		if (P[i] < 0) {
			st.push_back(P[i]);
		} else {
			if (st.size() && P[i] == -st.back()) {
				st.pop_back();
			} else {
				P[i] *= -1;
				st.push_back(P[i]);
			}
		}
	}
	
	st.clear();
	for (int i = 0; i < n; ++i) {
		if (P[i] > 0) {
			st.push_back(P[i]);
		} else {
			if (!st.size() || st.back() != -P[i])
				no();
			st.pop_back();
		}
	}
	
	if (st.size())
		no();
		
	puts("YES");
	for (int i = 0; i < n; ++i)
		printf("%d ", P[i]);
	return 0;
		
}