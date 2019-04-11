#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

#define MAXM 3030

typedef long long ll;

ll n, m, k, expr[MAXM];

ll a, b, c, t, resp;

priority_queue<int> heap;

int main(){
	
	cin >> n >> m >> k >> a >> b >> c >> t;
	
	for(int i=0;i<m;i++) cin >> expr[i];
	
	if((n-1)*b<=t) resp++;
	
	for(int i=0;i<m-1;i++){
				
		ll ini=(expr[i]-1)*b;
		
		if(ini>t) break;
		
		ll qtd=(t-ini)/a;
		
		ll range=min(expr[i+1]-1,expr[i]+qtd);
		
		resp+=range-expr[i]+1;
		
		if(i==0) resp--;
		
		for(int j=0;j<k and range<expr[i+1]-1;j++){
			
			ll tempo=ini+(range+1-expr[i])*c;
			
			if(tempo>t) break;
			
			ll q=(t-tempo)/a;
			
			ll new_range=min(expr[i+1]-1,range+1+q);
			
			heap.push(new_range-range);
			
			range=new_range;
		}
	}
		
	for(int i=m;i<k;i++){
		
		if(heap.empty()) break;
		
		err("+= %d\n", heap.top());
		resp+=heap.top();
		
		heap.pop();
	}
		
	cout << resp << "\n";
	
	return 0;
	
}