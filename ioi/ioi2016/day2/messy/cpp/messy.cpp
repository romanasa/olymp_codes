#include <bits/stdc++.h>

using namespace std;

void add_element(std::string x);
bool check_element(std::string x);
void compile_set();

vector<int> P;

void get(int len, int i, vector<int> &G, int n) {
	if (len == 0) {
		P[i] = G[0];
		return;
	}
	
	string s(n, '1');
	for (int j = 0; j < 2 * len; j++)
		s[G[j]] = '0';

	vector<int> A, B;	
	for (int j = 0; j < 2 * len; j++) {
		string cur = s;
		cur[G[j]] = '1';
		//cout << "ask " << cur << "\n";
		if (check_element(cur))
			A.push_back(G[j]);
		else
			B.push_back(G[j]);
	}

	get(len / 2, i, A, n);
	get(len / 2, i + len, B, n);
}

vector<int> restore_permutation(int n, int w, int r) {
	P.resize(n);
	
	for (int len = n / 2; len >= 1; len /= 2) {
		for (int i = 0; i < n; i += 2 * len) {
			string s(n, '1');
			for (int j = 0; j < 2 * len; j++)
				s[i + j] = '0';
			for (int j = 0; j < len; j++) {
				string cur = s;
				cur[i + j] = '1';
				add_element(cur);
				//cout << "add " << cur << "\n";
			}
		}
	}
	
	compile_set();

	vector<int> T(n);
	for (int i = 0; i < n; i++) 
		T[i] = i;
		
	get(n / 2, 0, T, n);
	
	for (int i = 0; i < n; i++)
		T[P[i]] = i;
	return T;
}
