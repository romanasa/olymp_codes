#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
struct pt {
    double x, y;
    bool operator < (pt b) const {
        return x == b.x ? y < b.y : x < b.x;
    }
} P[1234], Q[123], ansQ[123];

 
double dist(pt A, pt B) { return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y); }
 
int main() {
    int n, k;
    cin >> n >> k;
 
    for (int i = 0; i < n; i++) cin >> P[i].x >> P[i].y;
    
    int x1 = (int)1e4, x2 = -(int)1e4;
 	int y1 = (int)1e4, y2 = -(int)1e4;
 	
 	for (int i = 0; i < n; i++) {
 		x1 = min(x1, (int)P[i].x);
 		x2 = max(x2, (int)P[i].x);
 		y1 = min(y1, (int)P[i].y);
 		y2 = max(y2, (int)P[i].y);
 	}
 	
 	double ans = 1e18;
 	
 	for (int IT = 0; IT < 200; IT++) {
 	
        for (int i = 0; i < k; i++) Q[i] = { 1.0 * (rand() % (x2 - x1) + x1), 1.0 * (rand() % (y2 - y1) + y1) };
       
        
        for (int it = 0; it < 10; it++) {
        
        	map<int, ll> sx, sy, cx, cy;
        	for (int i = 0; i < n; i++) {
        		double d = 1e18;
        		int ind = -1;
        		for (int j = 0; j < k; j++) if (d > dist(P[i], Q[j]))
        			d = dist(P[i], Q[j]), ind = j;
        			
        		sx[ind] += P[i].x;
        		sy[ind] += P[i].y;
        		cx[ind]++;
        		cy[ind]++;
        	}	
        	
        	for (int i = 0; i < k; i++) {
        		if (!cx[i] || !cy[i]) Q[i] = { 0, 0 };
        		else Q[i] = { sx[i] * 1.0 / cx[i], sy[i] * 1.0 / cy[i] };
        	}
        }
        
        double cur = 0;
        for (int i = 0; i < n; i++) {
        	double d = 1e18;
        	for (int j = 0; j < k; j++) if (d > dist(P[i], Q[j]))
        		d = dist(P[i], Q[j]);
        	cur += sqrt(d);
        }
        
        if (cur < ans) {
        	ans = cur;
        	for (int j = 0; j < k; j++) ansQ[j] = Q[j];
        }
    }
    
    cout.precision(10);
    for (int i = 0; i < k; i++) cout << fixed << ansQ[i].x << " " << ansQ[i].y << "\n";
 
 
    return 0;
}