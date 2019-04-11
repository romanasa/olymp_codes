#include <bits/stdc++.h>
#define ll long long

using namespace std;

int lca(string &a, string &b) {
	int res = 0;
	for (; res < min((int)a.size(), (int)b.size()) && a[res] == b[res]; res++);
	return res;
}


int main() {
	int n;
	cin >> n;
	vector<string> A(n);
	
	for (int i = 0; i < n; i++)
		cin >> A[i];

	int ind = 0;	
	for (int i = 0; i < n; i++) {
		if ((int)A[i].size() > (int)A[ind].size()) {
			ind = i;
		}
	}
	
	swap(A[0], A[ind]);
		
	string s = A[0];
	
	sort(A.begin() + 1, A.end(), [&s](string a, string b) {
		return make_pair(-lca(s, a), a) < make_pair(-lca(s, b), b);
	});
	
	reverse(A.begin(), A.end());
	/*
	cout << "A = {";
	for (int i = 0; i < n; i++)
		cout << A[i] << ", ";
	cout << "}\n";
	*/
	vector<char> T;
	
	int pos = 0;
	for (int i = 0; i < n; i++) {

		if (i == 0) {
			for (char c : A[i])
				T.push_back(c);
			T.push_back('P');
		} else {
		
			int t = lca(A[i], A[i - 1]);	
			
			for (int j = (int)A[i - 1].size(); j > t; j--)
				T.push_back('-');
			
			for (int j = t; j < (int)A[i].size(); j++) {
				T.push_back(A[i][j]);
			}
			T.push_back('P');
		}
	
	}
	
	cout << (int)T.size() << "\n";
	for (auto c : T)
		cout << c << "\n";
	
	return 0;
}