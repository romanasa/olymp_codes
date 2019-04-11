#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

struct cond {
	int first, second, ind;
};


int n, L, k;

double get(int i, int j, vector<cond> &A, vector<cond> &B) {
	if (A[i].first < B[j].first) {
		ll d1 = 1ll * A[i].second * (B[j].first - A[i].first);
		if (d1 > L) return 1e18;
		return B[j].first + (L - d1) * 1.0 / (A[i].second + B[j].second);
	} else {
		ll d1 = 1ll * B[j].second * (A[i].first - B[j].first);
		if (d1 > L) return 1e18;
		return A[i].first + (L - d1) * 1.0 / (A[i].second + B[j].second);
	}
}

int main() {
	scanf("%d %d %d", &n, &L, &k);
	vector<cond> A(n), B(n), C(n), D(n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &A[i].first, &A[i].second);
		A[i].ind = i;
	}
	
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &B[i].first, &B[i].second);
		B[i].ind = i;
	}
	
	for (int it = 0; it < k; it++) {
		C.clear(), D.clear();
	
    	for (int i = 0; i < n; i++) {
    		if (C.size() && C.back().second > A[i].second) continue;
    		C.push_back(A[i]);
    		C.back().ind = i;
    	}
    	for (int i = 0; i < n; i++) {
    		if (D.size() && D.back().second > B[i].second) continue;
    		D.push_back(B[i]);
    		D.back().ind = i;
    	}
    	
    	
     	double t = 1e18;
     	int ind1 = -1, ind2 = -1;
    	
    	for (int i = 0; i < (int)C.size(); i++) {
  			int l = 0, r = (int)D.size() - 1;
  			/*
     		while (r - l > 3) {
     			int m1 = l + (r - l) / 3;
     			int m2 = r - (r - l) / 3;
     	
     			if (get(i, m1, A, D) < get(i, m2, A, D))
     				r = m2;
     			else
     				l = m1; 
     		}*/
     		for (int j = l; j <= r; j++) {
         		double tmp = get(i, j, C, D);
         		if (t > tmp) {
         			t = tmp;
         			ind1 = C[i].ind;
         			ind2 = D[j].ind;
         		}
     		}	
      	}
      	
      	int a = A[ind1].ind;
      	int b = B[ind2].ind;
 
      	printf("%d %d\n", a + 1, b + 1);
      	
     	A.erase(A.begin() + ind1);
      	B.erase(B.begin() + ind2);
      	n--;
	}
	return 0;
}