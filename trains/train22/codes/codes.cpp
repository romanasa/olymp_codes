#include "grader.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
int go[dd][31];
int term[dd], cnt[dd];

int root = 0;
int nv = 1;
int ans = 0;

vector<const char*> A;

int init(int n, char const * const * s) {
	for (int i = 0; i < dd; i++) fill(go[i], go[i] + 31, -1);
	
	for (int i = 0; i < n; i++) {
		
		int len = strlen(s[i]);
		A.push_back(s[i]);
		
		int v = root;
		
		for (int j = 0; j < len; j++) {
			if (go[v][s[i][j] - 'a'] == -1) go[v][s[i][j] - 'a'] = nv++;
			v = go[v][s[i][j] - 'a'];
			cnt[v]++;
		}
		term[v]++;
	}
	
	for (int v = 0; v < nv; v++) {
		if (term[v] == 1 && cnt[v] == 1) ans++;
	}
	return ans;
}

int add(const char* s) {
	A.push_back(s);
	int v = root;
	int len = strlen(s);
	for (int j = 0; j < len; j++) {
		if (go[v][s[j] - 'a'] == -1) go[v][s[j] - 'a'] = nv++;
		v = go[v][s[j] - 'a'];
		
		ans -= (term[v] == 1 && cnt[v] == 1);
		cnt[v]++;
		ans += (term[v] == 1 && cnt[v] == 1);
	}
	ans -= (term[v] == 1 && cnt[v] == 1);
	term[v]++;
	ans += (term[v] == 1 && cnt[v] == 1);
	return ans;
	//return 3;
}

int rem(int id) {
	
	int v = root;
	int len = strlen(A[id]);
	
	for (int j = 0; j < len; j++) {
		if (go[v][A[id][j] - 'a'] == -1) go[v][A[id][j] - 'a'] = nv++;
		v = go[v][A[id][j] - 'a'];
		
		ans -= (term[v] == 1 && cnt[v] == 1);
		cnt[v]--;
		ans += (term[v] == 1 && cnt[v] == 1);
	}
	ans -= (term[v] == 1 && cnt[v] == 1);
	term[v]--;
	ans += (term[v] == 1 && cnt[v] == 1);
	return ans;
}

int revert(int id) {
    return 2;
}
