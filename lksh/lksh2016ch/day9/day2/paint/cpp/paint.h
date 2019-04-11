#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)

using namespace std;

const int dd = (int)2e5 + 7;

int P[dd][107];
int S[dd][107];

int T[dd], W[dd], Q[dd], B[dd];

int n, k;

void calcP(vector<int> c, string s) {
	
	for (int i = 0; i < n; i++)
		T[i + 1] = T[i] + (s[i] == '_');
	
	P[0][0] = 1;
	
	for (int i = 1; i <= n; i++)
		if (P[i - 1][0] && s[i - 1] != 'X')
			P[i][0] = 1;
			
	for (int j = 1; j <= k; j++) {
		for (int i = 1; i <= n; i++) {
			if (s[i - 1] != 'X' && P[i - 1][j])
				P[i][j] = 1;			
				
			if (s[i - 1] != '_') {
				int len = c[j - 1];
				
				if (i < len) continue;
				if (T[i] - T[i - len] > 0) continue;
				if (i > len && s[i - len - 1] == 'X') continue;
				if (P[max(0, i - len - 1)][j - 1])
					P[i][j] = 1;
			}
		}
	}
}

void calcS(vector<int> c, string s) {
	
	for (int i = 0; i < n; i++)
		T[i + 1] = T[i] + (s[i] == '_');
	
	S[0][0] = 1;
	
	for (int i = 1; i <= n; i++)
		if (S[i - 1][0] && s[i - 1] != 'X')
			S[i][0] = 1;
			
	for (int j = 1; j <= k; j++) {
		for (int i = 1; i <= n; i++) {
			if (s[i - 1] != 'X' && S[i - 1][j])
				S[i][j] = 1;			
				
			if (s[i - 1] != '_') {
				int len = c[j - 1];
				
				if (i < len) continue;
				if (T[i] - T[i - len] > 0) continue;
				if (i > len && s[i - len - 1] == 'X') continue;
				if (S[max(0, i - len - 1)][j - 1])
					S[i][j] = 1;
			}
		}
	}
}


string solve_puzzle(string s, vector<int> c) {
	
	n = (int)s.size();
	k = (int)c.size();
	
	calcP(c, s);
	
	reverse(s.begin(), s.end());
	reverse(c.begin(), c.end());
	
	calcS(c, s);
	
	reverse(s.begin(), s.end());
	reverse(c.begin(), c.end());

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= k; j++) {
			if (s[i] != 'X' && P[i][j] && S[n - i - 1][k - j])
				W[i] = 1;
		}
	}
	
	for (int i = 0; i < n; i++)
		T[i + 1] = T[i] + (s[i] == '_');
	
		
	for (int j = 0; j < k; j++) {
		for (int i = 0; i + c[j] <= n; i++) {
			if (i && s[i - 1] == 'X') continue;
			if (i + c[j] < n && s[i + c[j]] == 'X') continue;
			if (T[i + c[j]] - T[i] > 0) continue;
			if (P[max(0, i - 1)][j] && S[max(0, n - i - c[j] - 1)][k - j - 1])
				B[i]++, B[i + c[j]]--;
		}
	}
		
	int cur = 0;
	
	for (int i = 0; i < n; i++) {
		cur += B[i];
		if (cur)
			Q[i] = 1;
	}
	
    string t;
    for (int i = 0; i < n; i++) {
  		if (Q[i] && W[i])
  			t += '?';
  		else if (Q[i])
  			t += 'X';
  		else
  			t += '_';
    }
	return t;
}
