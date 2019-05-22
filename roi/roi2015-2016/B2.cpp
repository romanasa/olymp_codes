#include <bits/stdc++.h>

using namespace std;

const int dd = (int)3000 + 7;

int T[dd];

inline int get(int i, int j) {
	
	cout << "? " << i + 1 << " " << j + 1 << endl;
	
	int t;
	cin >> t;
	
	return t;
}

void out(vector<int> A, int k) {
	cout << "Ready!\n" << k << "\n";
	for (int x : A)
		cout << x << " ";
	cout << endl;
}

int main() {
	
	int n;
	scanf("%d", &n);
	
	vector<int> A(n);
	
	int t = 1;
	
	for (int i = 0; i < n; i++) {
		A[i] = -1;
		
		int l = -1, r = i;
		while (r - l > 1) {
			int m = (l + r) / 2;
			if (get(m, i) == T[m]) {
				l = m;
			} else {
				r = m;
			}
		}
		
		if (l == -1)
			A[i] = t++;
		else
			A[i] = A[l];
			
		set<int> S;
		for (int j = i; j >= 0; j--) {
			S.insert(A[j]);
			T[j] = (int)S.size();
		}
	}
	out(A, t - 1);

	return 0;
}