#include <bits/stdc++.h>
#define err printf

using namespace std;

const int C = 2528;
const int maxN = (int)6e5 + 7;

pair<int, int> J[maxN];

struct req {
	int l, r;
	int push;
	int size() {
		return r - l;
	}
};

vector<req> T;
vector<pair<int, int> > H;



void out() {
	err("T :\n");
	for (int i = 0; i < (int)T.size(); i++) {
		err("(%d; %d)\n", T[i].l, T[i].r);
		for (int j = 0; j < (int)T[i].size(); j++)
			err("(%d; %d), ", J[T[i].l + j].first, J[T[i].l + j].second + T[i].push);
		err("\n---------------\n");
	}
	err("\n\n");
}

inline int split(int i) {
	int j = 0;
	
	for (int k = 0; k < (int)T.size(); k++)
		if (T[k].l <= i && i < T[k].r) {
			j = k;
			break;
		}
		
	if (i > T[j].l) {
		req cur;
		cur.l = T[j].l, cur.r = i, cur.push = T[j].push;
		
		H.clear();
		for (int k = 0; k < (int)T[j].J.size(); k++) {
			if (T[j].J[k].second + T[j].push < i)
				cur.J.push_back(T[j].J[k]);
			else
				H.push_back(T[j].J[k]);
		}
		T[j].J = H;
		T.insert(T.begin() + j, cur);
		return j + 1;
	}
	return j;
}


int G[maxN];
int cG;
const int inf = (int)1e9 + 7;

void build() {
	T.clear();
	G[cG++] = inf;
	
	for (int i = 0; i < cG; i += C) {
		req cur;
		cur.l = i, cur.r = min(i + C, cG), cur.push = 0;
		for (int j = i; j < i + C && j < cG; j++)		
			cur.J.push_back({ G[j], j });
		sort(cur.J.begin(), cur.J.end());
		T.push_back(cur);
	}
}

void Start(int n, int *t) {
	cG = n + n;
	copy(t, t + n, G);
	build();
}

void rebuild() {
	cG = 0;
	for (int i = 0; i < (int)T.size(); i++) {
		sort(T[i].J.begin(), T[i].J.end(), [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });
		for (int j = 0; j < (int)T[i].J.size(); j++) {
			G[cG++] = T[i].J[j].first;
		}
	}
	build();
}	

int cnt = 0;

void Add(int i, int x) {
	req cur;
	cur.l = i, cur.r = i + 1, cur.push = 0;
	cur.J.push_back({ x, i });
	
	int t = split(i);
	
	T.insert(T.begin() + t, cur);
	
	for (int j = t + 1; j < (int)T.size(); j++)
		T[j].push++, T[j].l++, T[j].r++;
		
    if (++cnt == C)
        rebuild(), cnt = 0;
}

void Del(int i) {
	split(i + 1);
	int t = split(i);
	T.erase(T.begin() + t);
	
	for (int j = t; j < (int)T.size(); j++)
		T[j].push--, T[j].l--, T[j].r--;
		
    if (++cnt == C)
        rebuild(), cnt = 0;
}

int Get(int l, int r, int x) {
	int L = split(l), R = split(r + 1);
	int ans = 0;
	
	for (int i = L; i < R; i++) 
		ans += lower_bound(T[i].J.begin(), T[i].J.end(), make_pair(x, maxN)) - T[i].J.begin();
	
    if (++cnt == C)
        rebuild(), cnt = 0;
    
	return ans;
}

#ifdef HOME
int main() {
    int n;
    cin >> n;
     
    int A[n];
    
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);
         
    Start(n, A);
    
    //out();
    
	int m;
	scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        char c;
        scanf("\n%c", &c);
         
        if (c == '+') {
            int a, b;
            scanf("%d %d", &a, &b);
            Add(a, b);
        }
        if (c == '?') {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            cout << Get(a, b, c) << "\n";
        }
        if (c == '-') {
            int a;
            scanf("%d", &a);
            Del(a);
        }
    }
    cerr << clock() * 1.0 / CLOCKS_PER_SEC << "\n\n\n";
}
#endif