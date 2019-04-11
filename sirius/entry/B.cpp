#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define double long double

using namespace std;

typedef __int128 ll;
//typedef long long ll;

const double EPS = 1e-3;
const int INF = (int)1e9;

bool good(double x) {
	return fabs(x - round(x)) < EPS;
}

int gauss (vector < vector<double> > a, vector<double> & ans) {
	int n = (int) a.size();
	int m = (int) a[0].size() - 1;
 
	vector<int> where (m, -1);
	for (int col=0, row=0; col<m && row<n; ++col) {
		int sel = row;
		for (int i=row; i<n; ++i)
			if (abs (a[i][col]) > abs (a[sel][col]))
				sel = i;
		if (abs (a[sel][col]) < EPS)
			continue;
		for (int i=col; i<=m; ++i)
			swap (a[sel][i], a[row][i]);
		where[col] = row;
 
		for (int i=0; i<n; ++i)
			if (i != row) {
				double c = a[i][col] / a[row][col];
				for (int j=col; j<=m; ++j)
					a[i][j] -= a[row][j] * c;
			}
		++row;
	}
 
	ans.assign (m, 0);
	for (int i=0; i<m; ++i)
		if (where[i] != -1)
			ans[i] = a[where[i]][m] / a[where[i]][i];
	for (int i=0; i<n; ++i) {
		double sum = 0;
		for (int j=0; j<m; ++j)
			sum += ans[j] * a[i][j];
		if (abs (sum - a[i][m]) > EPS)
			return 0;
	}
 
	for (int i=0; i<m; ++i)
		if (where[i] == -1)
			return INF;
	return 1;
}

int main() {
	int k;
	scanf("%d", &k);
	
	for (int M = 1; ; M++) {
	
    	vector<vector<double> > A;
    	vector<double> ans;
    	
    	for (int n = 1; n <= k + 2; n++) {
    		A.push_back(vector<double>(0));
    		
    		ll t = 1;
    		ll sum = 0;
    		
    		for (int p = 0; p <= k + 1; p++) {
    			A.back().push_back(t);
    			t *= n;
    		}
    		
    		for (int i = 1; i <= n; i++) {
    			ll cur = 1;
    			for (int j = 0; j < k; j++) cur *= i;
    			sum += cur;
    		}
   			A.back().push_back(sum * M);
   		}
   		
   		gauss(A, ans);
   		
   		int ok = 1;
   		for (auto x : ans) if (!good(x)) ok = 0;
   		//for (auto x : tmp) cout << x << ", "; cout <<"\n";
   		if (ok) {
   			cout << M << " ";
   			reverse(ans.begin(), ans.end());
   			for (auto x : ans) cout << (int)x << " ";
   			return 0;
   		}
   	}
	return 0;
}