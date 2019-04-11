#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
using namespace std;
 
typedef long long ll;
 
struct pt {
    double x, y;
    bool operator < (pt b) const {
        return x == b.x ? y < b.y : x < b.x;
    }
} P[1234];
int used[1234];
 
int dist(pt A, pt B) { return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y); }
 
 
double get(double x, double y, vector<pt> &P) {
    double cur = 0;
    for (auto p : P) {
        cur += sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }
    return cur;
}
 
pair<double, double> F(double x, vector<pt> &P) {
    double ly = -10000, ry = 10000;
    for (int it = 0; it < 100; it++) {
        double m1 = ly + (ry - ly) / 3;
        double m2 = ry - (ry - ly) / 3;
 
        if (get(x, m1, P) < get(x, m2, P))
            ry = m2;
        else
            ly = m1;
    }
    return { get(x, ly, P), ly };
}
 
pair<double, double> get(vector<pt> &P) {
 
 
    double lx = -10000, rx = 10000;
    for (int it = 0; it < 100; it++) {
        double m1 = lx + (rx - lx) / 3;
        double m2 = rx - (rx - lx) / 3;
 
        if (F(m1, P).first < F(m2, P).first)
            rx = m2;
        else
            lx = m1;
    }
    return { lx, F(lx, P).second };
}
 
 
 
 
vector<pt> solve1(int n, int k, pt *P) {
    fill(used, used + n, 0);
    int curlen = n / k + 1;
    vector<pt> Ans;
    for (int it = 0; it < k; it++) {
        if (it == n % k) curlen--;
 
 
        vector<pair<pt, int> > x;
        for (int i = 0; i < n; i++) if (!used[i]) {
            x.push_back({ P[i], i });
        }
 
        sort(x.begin(), x.end());
        pt O = x[(int)x.size() / 2].first;
 
        vector<pair<int, int> > t;
        for (int i = 0; i < n; i++) if (!used[i]) t.push_back({ dist(P[i], O), i });
        sort(t.begin(), t.end());
 
        //ll sx = 0, sy = 0;
 
        vector<pt> cur;
        for (int i = 0; i < curlen; i++) {
            used[t[i].second] = 1;
            cur.push_back(P[t[i].second]);
        }
 
        auto p = get(cur);
        Ans.push_back({ p.first, p.second });
    }
    return Ans;
}
 
 
vector<pt> solve2(int n, int k, pt *P) {
    fill(used, used + n, 0);
    int curlen = n / k + 1;
    vector<pt> Ans;
    for (int it = 0; it < k; it++) {
        if (it == n % k) curlen--;
 
        int ind = -1;
        for (int i = 0; i < n; i++) if (!used[i] && (ind == -1 ||  P[ind] < P[i])) ind = i;
 
        vector<pair<int, int> > t;
        for (int i = 0; i < n; i++) if (!used[i]) t.push_back({ dist(P[i], P[ind]), i });
        sort(t.begin(), t.end());
 
        //ll sx = 0, sy = 0;
 
        vector<pt> cur;
        for (int i = 0; i < curlen; i++) {
            used[t[i].second] = 1;
            cur.push_back(P[t[i].second]);
        }
        auto p = get(cur);
        Ans.push_back({ p.first, p.second });
    }
    return Ans;
}
 
 
vector<pt> solve3(int n, int k, pt *P) {
    fill(used, used + n, 0);
    int curlen = n / k + 1;
    vector<pt> Ans;
    for (int it = 0; it < k; it++) {
        if (it == n % k) curlen--;
 
        int ind = -1;
        for (int i = 0; i < n; i++) if (!used[i] && (ind == -1 || P[i] < P[ind])) ind = i;
 
        vector<pair<int, int> > t;
        for (int i = 0; i < n; i++) if (!used[i]) t.push_back({ dist(P[i], P[ind]), i });
        sort(t.begin(), t.end());
 
        //ll sx = 0, sy = 0;
 
        vector<pt> cur;
        for (int i = 0; i < curlen; i++) {
            used[t[i].second] = 1;
            cur.push_back(P[t[i].second]);
        }
 
        auto p = get(cur);
        Ans.push_back({ p.first, p.second });
    }
    return Ans;
}
 
 
 
vector<pt> solve4(int n, int k, pt *P) {
	
    int x1 = (int)1e4, x2 = -(int)1e4;
 	int y1 = (int)1e4, y2 = -(int)1e4;
 	
 	for (int i = 0; i < n; i++) {
 		x1 = min(x1, (int)P[i].x);
 		x2 = max(x2, (int)P[i].x);
 		y1 = min(y1, (int)P[i].y);
 		y2 = max(y2, (int)P[i].y);
 	}
 	
 	double ans = 1e18;
 	vector<pt> ansQ(k), Q(k);
 	
 	for (int IT = 0; IT < 100; IT++) {
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
    return ansQ;
}
 
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
 
double calc(vector<pt> Q, pt *P, int n) {
    double ans = 0;
    for (int i = 0; i < n; i++) {
        int d = (ll)1e9;
        for (auto c : Q) d = min(d, dist(P[i], c));
        ans += sqrt(d);
    }
    return ans;
}
 
void out(vector<pt> &P, pt *A, int n) {
 
    srand(137);
 
    int k = (int)P.size();
 
    double cost = calc(P, A, n);
    auto ans = P;
    
    for (int it = 0; it < 10; it++) {
    	map<int, ll> sx, sy, cx, cy;
    	for (int i = 0; i < n; i++) {
    		double d = 1e18;
    		int ind = -1;
    		for (int j = 0; j < k; j++) if (d > dist(A[i], P[j]))
    			d = dist(A[i], P[j]), ind = j;
    		sx[ind] += A[i].x;
    		sy[ind] += A[i].y;
    		cx[ind]++;
    		cy[ind]++;
    	}	
    	for (int i = 0; i < k; i++) {
    		if (!cx[i] || !cy[i]) P[i] = { 0, 0 };
    		else P[i] = { sx[i] * 1.0 / cx[i], sy[i] * 1.0 / cy[i] };
    	}
    	double q = calc(P, A, n);
    	if (q < cost) {
    		cost = q;
    		ans = P;
    	}
    }
 
    cout.precision(10);
    for (auto c : ans) cout << fixed << c.x << " " << c.y << "\n";
}
 
int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> P[i].x >> P[i].y;
 
 
 
    auto t1 = solve1(n, k, P);
    auto t2 = solve2(n, k, P);
    auto t3 = solve3(n, k, P);
    auto t4 = solve4(n, k, P);
 
 
 
    double c1 = calc(t1, P, n);
    double c2 = calc(t2, P, n);
    double c3 = calc(t3, P, n);
    double c4 = calc(t4, P, n);
 
 
    if (c1 <= c2 && c1 <= c3 && c1 <= c4) out(t1, P, n);
    else if (c2 <= c1 && c2 <= c3 && c2 <= c4) out(t2, P, n);
    else if (c3 <= c1 && c3 <= c2 && c3 <= c4) out(t3, P, n);
    else out(t4, P, n);
 
}