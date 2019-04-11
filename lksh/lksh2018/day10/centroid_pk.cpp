#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <vector>

#define pb push_back

using namespace std;

typedef long long int64;

template <class T>
T abs(T a){
	return (a<0)?(-a):(a);
}

struct point{
	int64 x,y;
	point():x(0),y(0){
	}
	point(int64 x,int64 y):x(x),y(y){
	}
	void load(){
		int X,Y;
		scanf("%d%d",&X,&Y);
		x=X;y=Y;
	}
};

point operator-(const point& a,const point& b){
	return point( a.x - b.x, a.y - b.y);
}

point operator+(const point& a,const point& b){
	return point( a.x + b.x, a.y + b.y);
}

point operator*(const point& a,int b){
	return point( a.x * b, a.y * b);
}

int64 operator*(const point& a,const point& b){
	return a.x * b.y - a.y * b.x;
}

bool operator<(const point& a,const point& b){
	if (a.y * b.y < 0)
		return a.y > 0;
	if (a.y * b.y == 0){
		if (a.y < 0)
			return false;
		if (b.y < 0)
			return true;
		if (a.y ==0 && b.y ==0)
			return a.x > 0 && b.x < 0;
	}
	return a*b > 0;
}

bool operator== (const point& a,const point& b){
	return a.x == b.x && a.y == b.y;
}

typedef vector<point> polygon;

void read(polygon& a){
	int size;
	scanf("%d",&size);
	a.resize(size);
	for (int i = 0; i < size; i++)
		a[i].load();
}

polygon a,b,c,result;

void toZero(polygon& a,point& start){
	start = start + a[0];
	for (int i = 1, sz = a.size(); i < sz; i++)
		a[i] = a[i] - a[0];
	a[0] = point(0,0);
} 

void toVector(polygon& a){
	assert(a[0] == point(0,0));
	int sz = a.size();
	a.pb(a[0]);
	for (int i = 0; i < sz; i++)
		a[i]=a[i+1]-a[i];
	a.pop_back();	
}

void norm(polygon& a,point& start){
	int n=a.size();
	toZero(a,start);
	toVector(a);
	int mpos=0;
	for (int i = 0; i < n; i++)
		if (a[i] < a[mpos])
			mpos = i;
	for (int i = 0; i < mpos; i++)
	    start=start + a[i];
	rotate(a.begin(), a.begin() + mpos, a.end());	    
}

void toPoint(polygon& a,point start){
	int n = a.size();
	a[0] = a[0] + start;
	for (int i = 1; i < n; i++)
		a[i] = a[i] + a[i-1];		
}

point center;
vector<point> checkpoints;

bool cmpxy(const point& a,const point& b){
	if (a.y == b.y)
		return a.x < b.x;
	return a.y < b.y;
}

void checkPrecalc(){
	int n=result.size();
	int minid = 0;
	for (int i = 0; i < n; i++)
		if (cmpxy(result[i], result[minid]))
			minid = i;   
	rotate(result.begin(), result.begin() + minid, result.end());
	center = result[0];
	for (int i = 0; i < n; i++)
		result[i] = result[i] - center;
	checkpoints=vector<point>(result.begin()+1,result.end());		
}

bool inTriangle(const point& p,const point& a,const point& b,const point& c){
	int64 s1 = abs((b - a) * (c - a));
	int64 s2 = abs((a - p) * (b - p)) +
			   abs((b - p) * (c - p)) +
			   abs((c - p) * (a - p));
	return s1 == s2;
}

bool check(point p){
	p = p * 3;
	p = p - center;
	if (p.y < 0)
		return false;
	if (p.y == 0 && p.x < 0)
		return false;
	if (p < checkpoints[0])
		return false;
	if (checkpoints.back() < p)
		return false;
	int id = lower_bound(checkpoints.begin(), checkpoints.end(), p) - checkpoints.begin();
	for (int i = -1; i < 2; i++){
		int id2= id + i;
		if (id2 >= 0 && id2+1 < (int)checkpoints.size()){
			if (inTriangle(p,point(0,0),checkpoints[id2],checkpoints[id2+1]))
				return true;
		}
	}
	return false;	
}

void deleteoneLine(polygon& a){
	int n=a.size();
	vector<point> res;
	int sz = 0;
	for (int i = 0; i < n; i++){
		while ( (sz > 1) && ((res[sz-1] - res[sz-2]) * (a[i] - res[sz-1]) == 0)){
			res.pop_back();
			--sz;
		}
		res.pb(a[i]);
		++sz;
	}
	if ((res[1] - res[0]) * (res[0] - res[sz-1]) == 0)
		res.erase(res.begin());
	a=res;
}


int main(){
	//#ifdef LOCAL
		freopen("centroid.in","r",stdin);
		freopen("centroid.out","w",stdout);
	//#endif
	read(a);
	read(b);
	read(c);
	deleteoneLine(a);	
	deleteoneLine(b);	
	deleteoneLine(c);	

	point start(0,0);
	norm(a, start);
	norm(b, start);
	norm(c, start);
	result.insert(result.end(), a.begin(), a.end());
	result.insert(result.end(), b.begin(), b.end());
	result.insert(result.end(), c.begin(), c.end());
	inplace_merge(result.begin(), result.begin() + a.size(), result.end() - c.size());	
	inplace_merge(result.begin(), result.end() - c.size(), result.end());
	toPoint(result,start);
//	for (int i=0;i<result.size();i++)
//		cerr << result[i].x <<" " << result[i].y << endl;
	deleteoneLine(result);	
	checkPrecalc();
	
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; i++){
		point p;
		p.load();
//		cerr << p.x << " "<< p.y << endl;
		if (check(p))
			printf("YES\n");
		else
			printf("NO\n");
	}
}
