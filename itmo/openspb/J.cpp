#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

string P, R;
int N, K, Q;

vector<int> J;

void init(int n, int k) {
	N = n;
	K = k;
	
	J.resize(n);
	for (int i = 0; i < n; i++) J.push_back(i);
	for (int i = 0; i < n; i++) P += (char)('0' + rand() % 2);
	for (int i = 0; i < n; i++) R += (char)('0' + rand() % 2);
	
	cout << "Guess " << P << " " << R << endl;
}

string ask() {
	/*string cur = (rand() % 2 ? P : R);
	random_shuffle(J.begin(), J.end());
	for (int i = 0; i < K; i++) cur[J[i]] ^= '0' ^ '1';
	return cur;*/
	cout << "?" << endl;
	string t; cin >> t;
	return t;
}

void out(string A, string B) {
	if (A > B) swap(A, B);
	cout << "! " << A << " " << B << endl;
	exit(0);
}

int get(string &A, string &B) {
	//cout << "A===" << A << endl;
	//cout << "B===" << B << endl;
	assert(A.size() == B.size());
	int c = 0;
	for (int i = 0; i < (int)A.size(); i++) c += (A[i] != B[i]);
	return c;
}

int main() {
	int n, k, q;
	cin >> n >> k >> q;
	
	//init(n, k);
	
	vector<string> T(q);
	vector<int> eq(n, -1);
	for (int it = 0; it < q; it++) T[it] = ask();
	
	for (int i = 0; i < n; i++) {
		int c1 = 0, c2 = 0;	
		for (int j = 0; j < q; j++) {
			if (T[j][i] == '1') c1++;
			else c2++;
		}
		if (c1 >= 80) eq[i] = 1;
		if (c2 >= 80) eq[i] = 0;
	}
	
	int cnt = 0;
	for (int i = 0; i < n; i++) cnt += (eq[i] == -1);
	
	if (cnt < 13) {

		string A(n, '#'), B(n, '#');
		vector<int> t;
		for (int i = 0; i < n; i++) 
			if (eq[i] != -1) A[i] = B[i] = (char)('0' + eq[i]);
			else t.push_back(i);	
			
		for (int msk = 0; msk < (1 << cnt); msk++) {
			for (int i = 0; i < cnt; i++) {
				A[t[i]] = (char)('0' + ((msk >> i) & 1));
				B[t[i]] = '0' + '1' - A[t[i]];
			}
			int ok = 1;
			for (int i = 0; i < q; i++) {
				int c1 = 0, c2 = 0;
				for (int j = 0; j < n; j++) {
					if (T[i][j] != A[j]) c1++;
					if (T[i][j] != B[j]) c2++;
				}
				if (c1 != k && c2 != k) ok = 0;
			}
			if (ok) out(A, B);
		}
		//assert(0);
	} else {
		
		vector<string> Q1, Q2;	
		srand(135);
		random_shuffle(T.begin(), T.end());
		for (int i = 0; i < q; i++) {
			int mx1 = 0;
			int mx2 = 0;
			
			//cout << i << "===" << T[i] << "\n";
			
			for (auto c : Q1) mx1 = max(mx1, get(c, T[i]));
			for (auto c : Q2) mx2 = max(mx2, get(c, T[i]));
			
			if (mx1 > 2 * k) Q2.push_back(T[i]);
			else if (mx2 > 2 * k) Q1.push_back(T[i]);
			else (mx1 <= mx2 ? Q1 : Q2).push_back(T[i]);
			//if (mx1 > k + 5) Q2.push_back(T[i]);
			//else Q1.push_back(T[i]);
		}
		
		string A(n, '#'), B(n, '#');

		for (int i = 0; i < n; i++) {
			int c1 = 0, c0 = 0;
			for (auto s : Q1) (s[i] == '1' ? c1 : c0)++;
			A[i] = (c1 > c0 ? '1' : '0'); 
		}	
		for (int i = 0; i < n; i++) {
			int c1 = 0, c0 = 0;
			for (auto s : Q2) (s[i] == '1' ? c1 : c0)++;
			B[i] = (c1 > c0 ? '1' : '0'); 
		}	
		out(A, B);
	}
	
	return 0;
}