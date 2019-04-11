#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int main() {
	int n;
	scanf("%d", &n);
	
	vector<pair<int, int> > A(n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &A[i].first, &A[i].second);
	}
	
	
	sort(A.begin(), A.end());
	
	
	if (n > 10) {
		
		int ok = 1;
		for (int i = 0; i < n; i++) ok &= A[i].second == 1;
		
		if (ok) {
        	int cur = 0, cost = 0;
          	int ind = n - 1;
          	
          	for (int i = 0; i <= ind; i++) {
          		while (cur < A[i].first) {
          			cur++, cost += A[ind].second;
          			ind--;
          		}
          		cur++;
          	}
          	cout << cost << "\n";
        	return 0;
    	}
    	
    	vector<int> used(n);
    	for (int i = 0; i < n; i++) A[i].second = -A[i].second;
    	
    	int cost = 0, cur = 0;

    	auto tmp = A;
    	A.clear();
    	for (auto c : tmp) {
    		if (c.second == 0) cur++;
    		else A.push_back(c);
    	}
    	
    	n = (int)A.size();
    	
    	for (int i = 0; i < n; i++) {
    		if (used[i]) continue;
    		if (cur >= A[i].first) {
    			cur++;
    			continue;
    		}
    	
    		int ok = 0;
    		while (cur < A[i].first) {
    			
    			int ind = i;	
    			
    			map<int, int> cnt;
    			cnt[A[i].first]++;
    			
    			
    			while (ind + 1 < n && !used[ind + 1] && A[ind + 1].first <= A[ind].first + 1) cnt[A[ind + 1].first]++, ind++;
    			
    			
    			int curcost = A[ind].second;
    			int pos = -1;
    			
    			int was = 0;
    			for (int t = i; t < ind; t++) {
    				if (A[t].second <= curcost && (was || cnt[A[t].first] > 1)) {
    					curcost = A[t].second;
    					pos = t;
    				}
    				if (t + 1 < ind) was |= (A[t].first == A[t + 1].first);
    			}
    			
    			if (pos != -1) ind = pos;
    			
    			
    			int curp = n - 1;
    			while (used[curp]) curp--;
    			
    			if (curp > i && A[curp].second <= curcost) {
    				ind = curp;
    			}
    			
    			int old = curp;
    			
    			while (curp > i && A[curp - 1].first + 1 >= A[curp].first) curp--;
    			
    			if (curp > i) {
    				ind = old;	
    			}
    			
    			//err("i = %d, ind = %d\n", i, ind);
    			
        		if (ind == i) {
        			cur++, cost += A[ind].second;
        			ok = 1;
        			break;
        		}
        		
        		used[ind] = 1;
        		cur++, cost += A[ind].second;
    		}
    		if (!ok) cur++;
    	
    	}
    	cout << cost << "\n";
    	
	}
	
	int ans = (int)2e9 + 1;
	do {
		int cur = 0;
		int cost = 0;
		
		for (int i = 0; i < n; i++) {
			if (cur < A[i].first) cost += A[i].second;
			cur++;
		}
		ans = min(ans, cost);
	} while (next_permutation(A.begin(), A.end()));
	printf("%d\n", ans);
	return 0;
}