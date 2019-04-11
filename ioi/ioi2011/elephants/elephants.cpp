#ifdef HOME
	#include "elephants.h"
#else
	#include "grader.h"
#endif
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)2e5 + 1;
const int C = 290;

int A[dd], B[dd];
int n, L;

struct block {
	int *cur;
	int *cnt, *nxt;
	int sz;
	
	block() {}
	
	void resize(int n) {
		cur = new int[n];
		cnt = new int[n];
		nxt = new int[n];
		sz = n;
	}
	
	void calc() {
		int j = sz - 1;
		for (int i = sz - 1; i >= 0; i--) {			
			while (i <= j && cur[i] + L < cur[j]) j--;
			if (j + 1 == sz)
				cnt[i] = 1, nxt[i] = i;
			else 
				cnt[i] = cnt[j + 1] + 1, nxt[i] = nxt[j + 1];
		}
	}
};

vector<block> blocks;

void out() {
	for (int j = 0; j < (int)blocks.size(); j++) {
    	err("-------\ni = %d, ", j);
    	err("cur = {"); for (int i = 0; i < blocks[j].sz; i++) err(" %d,", blocks[j].cur[i]); err(" }\n");
    	//err("nxt = {"); for (int i = 0; i < blocks[j].sz; i++) err(" %d,", blocks[j].nxt[i]); err(" }\n");
    	//err("cnt = {"); for (int i = 0; i < blocks[j].sz; i++) err(" %d,", blocks[j].cnt[i]); err(" }\n");
	}
}

void build(int *A) {
	for (int i = 0; i < (int)blocks.size(); i++) {
		delete [] blocks[i].cur;
		delete [] blocks[i].nxt;
		delete [] blocks[i].cnt;
	}
	blocks.clear();
	for (int i = 0; i < n; i += C) {
		int l = i, r = min(n, i + C);
		blocks.push_back(block());
		blocks.back().resize(r - l);
		for (int j = l; j < r; j++) blocks.back().cur[j - l] = A[j];
		blocks.back().calc();
		
	}
}

void rebuild() {
	//err("reb\n");
	int ind = 0;
	for (int i = 0; i < (int)blocks.size(); i++) {
		for (int j = 0; j < (int)blocks[i].sz; j++) {
			B[ind++] = blocks[i].cur[j];
		}
	}
	build(B);
}

int calc() {
	int lst = -(int)1e9 - 1;
	int sz = 0, ans = 0;
	for (int i = 0; i < (int)blocks.size(); i++) {
		int ind = upper_bound(blocks[i].cur, blocks[i].cur + blocks[i].sz, lst + L) - blocks[i].cur;
		if (ind != blocks[i].sz) {
			ans += blocks[i].cnt[ind];
			lst = blocks[i].cur[blocks[i].nxt[ind]];
		}
		sz += blocks[i].sz;
	}
	return ans;
}

void init(int N, int L, int X[]) {
	//assert(N <= 100);
	n = N;
	::L = L;
	for (int i = 0; i < n; i++) A[i] = X[i];
	
	copy(A, A + n, B);
	sort(B, B + n);
	build(B);
}

int tmp[dd];
int tmp2[dd];

void del(int ind, int val) {
	int ii = 0, ok = 0, sz = blocks[ind].sz;
	for (int i = 0; i < sz; i++) {
		if (blocks[ind].cur[i] == val && !ok) {
			ok = 1;
			continue;
		}
		tmp[ii++] = blocks[ind].cur[i];
	}
	
	delete [] blocks[ind].cur;
	delete [] blocks[ind].nxt;
	delete [] blocks[ind].cnt;
	
	blocks[ind].resize(sz - 1);
	for (int i = 0; i < sz - 1; i++) blocks[ind].cur[i] = tmp[i];
	blocks[ind].calc();
	
	if (blocks[ind].sz == 0) {
		blocks.erase(blocks.begin() + ind);
	}
}

void make(int ind, int val) {
	int i1 = 0, i2 = 0;
	int sz = blocks[ind].sz;
	
	for (int i = 0; i < sz; i++) {
		if (blocks[ind].cur[i] <= val) tmp[i1++] = blocks[ind].cur[i];
		else tmp2[i2++] = blocks[ind].cur[i];
	}
	
	delete [] blocks[ind].cur;
	delete [] blocks[ind].nxt;
	delete [] blocks[ind].cnt;
	
	blocks[ind].resize(i1);
	for (int i = 0; i < i1; i++) blocks[ind].cur[i] = tmp[i];
	blocks[ind].calc();
	
	blocks.insert(blocks.begin() + ind + 1, block());
	blocks[ind + 1].resize(i2);
	for (int i = 0; i < i2; i++) blocks[ind + 1].cur[i] = tmp2[i];
	blocks[ind + 1].calc();
	
	if (i1 == 0) blocks.erase(blocks.begin() + ind);
	if (i2 == 0) blocks.erase(blocks.begin() + ind + 1);
}

int update(int pos, int y) {
	int ind = -1;
	for (int i = 0; i < (int)blocks.size(); i++) {
		if (blocks[i].cur[0] <= A[pos] && A[pos] <= blocks[i].cur[blocks[i].sz - 1]) {
			ind = i;
			break;
		}
	}
	
	del(ind, A[pos]);
	
	ind = -1;
	for (int i = 0; i < (int)blocks.size(); i++) {
		if (blocks[i].cur[0] <= y && y <= blocks[i].cur[blocks[i].sz - 1]) {
			ind = i;
			break;
		}
	}
	
	if (ind != -1) make(ind, y);
	
	ind = -1;
	for (int i = (int)blocks.size() - 1; i >= 0; i--) {
		if (blocks[i].cur[blocks[i].sz - 1] <= y) {
			ind = i;
			break;
		}
	}
	
	blocks.insert(blocks.begin() + ind + 1, block());
	blocks[ind + 1].resize(1);
	blocks[ind + 1].cur[0] = y;
	blocks[ind + 1].calc();
			
	
	A[pos] = y;
	
	if ((int)blocks.size() > 3 * C) {
		rebuild();
	}
	
	return calc();
}