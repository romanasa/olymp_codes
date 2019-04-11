#include "grader.h"
#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;


const int dd = (int)3e5 + 7;

map<int, int> used;
int pos[dd];

int valid(int n, int inputSeq[]) {
	
	int ind = 0;
	for (int i = 0; i < n; i++)
		if (inputSeq[ind] > inputSeq[i])
			ind = i;		
	
	int q = inputSeq[ind];
	
	if (q <= n) {
		while (q > 1)
			ind--, q--;
		while (ind < 0)
			ind += n;
	}
			
	int t = 1;
	for (int j = ind; j < ind + n; j++) {
		int i = j;
		if (i >= n) i -= n;
		
		//err("%d %d\n", inputSeq[i], t);
				
		if (inputSeq[i] != t++ && inputSeq[i] <= n)
			return 0;
			
		if (inputSeq[i] > n) {
			if (used[inputSeq[i]])
				return 0;
			used[inputSeq[i]] = 1;
		}
	}
	return 1;
}

int replacement(int n, int gondolaSeq[], int replacementSeq[]) {
	fill(pos, pos + dd, -1);	

	int ind = 0;
	for (int i = 0; i < n; i++)
		if (gondolaSeq[ind] > gondolaSeq[i])
			ind = i;		
			
	int q = gondolaSeq[ind];
	
	if (q <= n) {
		while (q > 1)
			ind--, q--;
		while (ind < 0)
			ind += n;
	}

	//err("%d\n", ind);
	
	int maxN = 1;
	
	vector<pair<int, int> > T;
	
	int t = 1;
	for (int j = ind; j < ind + n; j++) {
		int i = j;
		if (i >= n) i -= n;
		pos[gondolaSeq[i]] = t++;	
		maxN = max(maxN, gondolaSeq[i]);
		
		if (gondolaSeq[i] > n)
			T.push_back({ gondolaSeq[i], pos[gondolaSeq[i]] });
	}
	
	sort(T.begin(), T.end());
	
	int l = 0;
	
	int prev = n;
	for (auto c : T) {
		while (c.second < c.first) {
			replacementSeq[l++] = c.second;
			c.second = ++prev;
		}
	}
	
	return l;
}

const int mod = (int)1e9 + 9;

int bp(int a, int n) {
	if (n == 0)
		return 1;
	if (n & 1) 
		return 1ll * bp(a, n - 1) * a % mod;
	int t = bp(a, n / 2);
	return 1ll * t * t % mod;
}

int countReplacement(int n, int inputSeq[]) {
	if (!valid(n, inputSeq))
		return 0;
		
	vector<int> A(1, n);
	for (int i = 0; i < n; i++)
		if (inputSeq[i] > n)
			A.push_back(inputSeq[i]);
	sort(A.begin(), A.end());
	
	int N = (int)A.size();
	int ans = 1;
	
	for (int i = 1; i < N; i++) {
		ans = 1ll * ans * bp(N - i, A[i] - A[i - 1] - 1) % mod;
	}
	if (N == n + 1)
		ans = 1ll * ans * n % mod;
	
	return ans;
}
