#include<iostream>
#include<algorithm>
#include<cassert>
#include<vector>
#include <cstdio>
using namespace std;
typedef long long ll;

#define F first
#define S second

const int INF = 1<<29;
const int MAXN = 100*1000+1;

int h[MAXN+10]; // refers to array a ( increasing starting from 1 )
int c[MAXN+10]; // refers to array b ( decreasing to 0 )
ll d[MAXN+10];
int n;

void input();
void dyn();

int main()
{
	ios::sync_with_stdio(false);
	input();
	dyn();
	cout << d[n-1] << endl;
	return 0;
}

struct seg{
	int Id;
	double begin;
	seg(int _Id=0,double _begin=0) : Id(_Id) , begin(_begin) {}
};

double intersect(int a,int b) { return ((double)d[b]-d[a])/(c[a]-c[b]); }
	
int p = 0;
vector<seg> q; 

void push(int a)
{
	if( q.empty() )
	{
		q.push_back(seg(a,-INF));
		return;
	} 
	while( intersect( q.back().Id , a ) <= q.back().begin )
		q.pop_back();
	// after the first push there's always at least one element in the queue even after all the pop_back's
	assert( !q.empty() ); 
	q.push_back(seg( a , intersect( q.back().Id , a ) ));
	if( p >= (int)q.size() )
		p = (int)q.size()-1;
}

void dyn()
{
	d[0] = 0;
	push(0);
	for(int i=1; i<n; i++)
	{
		while( p+1 < (int)q.size() && q[p+1].begin <= h[i] )
			p++;
		d[i] = d[q[p].Id]  +  (ll)c[q[p].Id] * h[i];
		push(i);
	}
}

void input()
{
    freopen("lumber.in", "r", stdin);
    freopen("lumber.out", "w", stdout);
	cin >> n;
	for(int i=0; i<n; i++)
		cin >> h[i];
	for(int i=0; i<n; i++)
		cin >> c[i];
}
