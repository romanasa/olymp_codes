#include <stdio.h>
#include <vector>
#include <algorithm>
#include <memory.h>
 
using namespace std;

#define int64 long long
#define M 200000

int parts;
int counts[M];
int vi[M];
int pos[1000001];

int a[M];
int n;
int64 cres, ad;
int64 res[M];

inline void add(int i) {
	cres += ((int64)a[i]) * (((counts[vi[i]]++) << 1) + 1);
}

inline void sub(int i) {
	cres -= ((int64)a[i]) * (((counts[vi[i]]--) << 1) - 1);
}


class Seg{
	public:
	inline static bool comp(const Seg &a, const Seg &b){
		int parta = (a.L * parts) / n;
		int partb = (b.L * parts) / n;
		if (parta != partb) return (parta < partb);
		return (a.R < b.R);
	};

	int L;
	int R;
	int index;	
};



int main(){
    freopen("power.in", "r", stdin);
    freopen("power.out", "w", stdout);
    
	int t, L, R;
	scanf("%d %d\n", &n, &t);
	vector < Seg > v(t);
	
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);	
	
	for (int i = 0; i < t; i++){
		scanf("%d %d\n", &L, &R);
		v[i].L = L - 1;
		v[i].R = R - 1;
		v[i].index = i;
	}
	int sq = 0, sqsq = 0;
	while (sqsq <= t + 2){
		sq++;
		sqsq += 2 * sq - 1;
	}
	parts = max(1, min(n, sq - 1));
	sort(v.begin(), v.end(), Seg::comp);

	int cnt = 0;
	memset(pos, -1, sizeof(pos));
	for (int i = 0; i < n; i++) {
		if (pos[a[i]] == -1) {
			pos[a[i]] = cnt++;
		}
		vi[i] = pos[a[i]];
	}
	
	int cl = 0, cr = -1;
	for (int i = 0; i < t; i++) {
		L = v[i].L; 
		R = v[i].R;
		while (cl < L) sub(cl++);
		while (cl > L) add(--cl); 
		while (cr < R) add(++cr);
		while (cr > R) sub(cr--);
		res[v[i].index] = cres;
	}
	
	for (int i = 0; i < t; i++) printf("%lld\n", res[i]);
	
	return 0;
	
}
