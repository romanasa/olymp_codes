#include "grader.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;

string make(string &t, char c) {
	string s = t;
	for (int i = 0; i < (int)t.size(); i++) {
		int p = (i + 1 < (int)t.size() ? i + 1 : 0);
		if (t[i] == c && t[p] != c) s[p] = c;
	}
	return s;
}

void solve(const char* s, int m, const request_t* r, char* ans) {
	int n = strlen(s);
	
	string t;
	for (int i = 0; i < n; i++) t += s[i];
	
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < r[i].cnt; j++) {
			t = make(t, r[i].c);
		}
	}
	for (int i = 0; i < n; i++) ans[i] = t[i];
}
