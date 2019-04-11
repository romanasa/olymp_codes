#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <bitset>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <cassert>
#include <random>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
  
using namespace std;
  
typedef long long ll;
typedef double ld;
  
int solve();
  
#define TASK "distance"
  
int main() {
    solve();
}
  
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
  
const int dd = (int)2001;
int A[dd][dd];
char tp[dd][dd];
short L[dd][dd], R[dd][dd], U[dd][dd], D[dd][dd];
  
int n;
  
bool ok(int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < n;
}


struct magic {
	//map<pair<int, int>, int> A;
	int T[dd][dd], A[dd][dd];
	int tmm = 1;
	void clear() { tmm++; }
	
	void check(int i, int j) { 
		if (A[i][j] != tmm) T[i][j] = 1e9, A[i][j] = tmm;
	}
	
	void uin(int &a, int b) {
		if (a > b) a = b;
	}
	
	void upd(int x, int y, int val) {
		for (int i = x + 1; i; i -= (i&-i))
			for (int j = y + 1; j; j -= (j&-j)) 
				check(i, j), uin(T[i][j], val);
	}
	
	int get(int x, int y) {
		int res = (int)1e9;
		for (int i = x + 1; i < dd; i += (i&-i))
			for (int j = y + 1; j < dd; j += (j&-j)) {
				check(i, j);
				uin(res, T[i][j]);
			}
		return res;
	}
} T;

int solve() {
    scanf("%d", &n);
  
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }
  
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int gg = 0; gg < 4; gg++) {
                int ni = i + dx[gg], nj = j + dy[gg];
                if (ok(ni, nj) && A[ni][nj] == A[i][j]) tp[i][j] = gg;
            }
        }
    }
  
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            U[i][j] = (tp[i][j] != 1) * ((i ? U[i - 1][j] : 0) + 1);
            L[i][j] = (tp[i][j] != 2) * ((j ? L[i][j - 1] : 0) + 1);
        }
    }
  
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            D[i][j] = (tp[i][j] != 3) * (D[i + 1][j] + 1);
            R[i][j] = (tp[i][j] != 0) * (R[i][j + 1] + 1);
        }
    }
  
    int pi = -1, pj = -1;
    int ans = -1;
  
    for (int c = -n; c < n; c++) {
    	T.clear();
  		
  		for (int i = 1; i + 1 < n; i++) {
 			int j = c + i;
 			if (j <= 0 || j >= n - 1) continue;
 			

 			int k = min(L[i][j], U[i][j]) - 1;
 			int cur = T.get(i - k, i);

 			int len = i - cur;
 			if (len > ans) {
				ans = len, pi = cur, pj = c + pi;
 			}	
 			T.upd(i, i + min(R[i][j], D[i][j]) - 1, i);
 		}
    }
    printf("%d %d %d\n", ans + 1, pi + 1, pj + 1);
    return 0;
} 