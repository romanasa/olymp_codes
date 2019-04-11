#include <bits/stdc++.h>

using namespace std;

int n;
int st[60];
int p[15];

set<int> S;

int K;
void calc(int v, int curh, int sum){
    if (v == n) {
        for (int i = 0; i < n; i++) cout << st[i] << ' ';
        exit(0);
    }
    if (S.count(curh)) return;
    S.insert(curh);
    for (int i = 0; i < 13; i++) if (curh % p[i + 1] / p[i] && sum % (i + 1) == 0) {
        st[n - v - 1] = i + 1;
        calc(v + 1, curh - p[i], sum - (i + 1));
    }
}

int main(){
	p[0] = 1;
	for (int i = 1; i <= 13; i++) p[i] = p[i - 1] * 5;
	
    cin >> n;
    int curh = 0, sum = 0;
    for (int i = 0; i < n; i++) {
    	int x;
    	cin >> x;
    	curh += p[x - 1];
    	sum += x;
    }
    calc(0, curh, sum);
    cout << -1;    
    return 0;
}
