#include <bits/stdc++.h>
//#include "grader.h"
   
using namespace std;
/*
const int MAX_MEM = 2e8;
char MEM[MAX_MEM];
int mpos;

inline void* operator new (size_t n) {
	char *res = MEM + mpos;
	mpos += n;
	return (void*)res;
}

inline void operator delete(void *) {}
*/
struct req {
    int l, r;
    vector<pair<int, int> > J;
    vector<int> S;
    int push;
};
   
vector<req> T;
   
int C = 1897;
int n;
const int inf = (int)1e9 + 1;
const int dd = (int)2e5 + 3000 + 7;
const int maxN = (int)2e5 + 7;
 
   
inline int get(int i) {
    for (int j = 0; j < (int)T.size(); j++) {
        if (T[j].l <= i && i < T[j].r)
            return j;
    }
    return 0;
}
 
vector<pair<int, int> > A, B;
vector<int> X, Y;
   
inline int split(int i) {
    int j = get(i);
       
    if (T[j].l < i) {
     
        A.clear(), B.clear(), X.clear(), Y.clear();     
           
        for (auto c : T[j].J) {
            if (c.second + T[j].push < i)
                A.push_back(c);
            else
                B.push_back(c);
        }
         
        for (int k = T[j].l; k < T[j].r; k++) {
            if (k < i)
                X.push_back(T[j].S[k - T[j].l]);
            else
                Y.push_back(T[j].S[k - T[j].l]);
        }
           
        T.insert(T.begin() + j, { T[j].l, i, A, X, T[j].push }); 
           
        T[j + 1].l = i;
        T[j + 1].J = B;
        T[j + 1].S = Y;
           
        return j + 1;
    }
    return j;
}
 
int H[maxN];
int cH = 0;
   
int cntbuilds = 0;

inline void build() {
	cntbuilds++;
	
    T.clear();
       
    for (int i = 0; i < maxN; i += C) {
        T.push_back({ i, i + C }); 
    }
   
    for (int i = 0; i < maxN; i++) {
        T[i / C].J.push_back({ H[i], i });
        T[i / C].S.push_back(H[i]);
    }
       
    for (int i = 0; i < (int)T.size(); i++)
        sort(T[i].J.begin(), T[i].J.end()), T[i].push = 0;
}
 
inline void rebuild() {
    cH = 0;
    for (int i = 0; i < (int)T.size(); i++)
        for (int j = 0; j < (int)T[i].S.size(); j++)
            H[cH++] = T[i].S[j];
	build();
}
 
int cnt = 0;
   
void Start(int t, int *x) {
    copy(x, x + t, H);  
    build();
}
   
void Add(int i, int x) {
    int j = split(i);
    vector<int> A = { x };
    vector<pair<int, int> > B = { make_pair(x, i) };
    T.insert(T.begin() + j, { i, i + 1, B, A });
     
    for (int k = j + 1; k < (int)T.size(); k++) {
        T[k].push++, T[k].l++, T[k].r++;
    }
     
    if (++cnt == C)
        rebuild(), cnt = 0;    
}
   
void Del(int i) {
    split(i + 1);
    int t = split(i);
     
    T.erase(T.begin() + t);
     
    for (int k = t; k < (int)T.size(); k++) {
        T[k].push--, T[k].l--, T[k].r--;
    }
     
    if (++cnt == C)
        rebuild(), cnt = 0;   
}
   
int Get(int l, int r, int x) {
    int L = split(l), R = split(r + 1);
    int ans = 0;
       
    for (int i = L; i < R; i++)
        ans += upper_bound(T[i].J.begin(), T[i].J.end(), make_pair(x, maxN)) - T[i].J.begin();
           
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
    cerr << clock() * 1.0 / CLOCKS_PER_SEC << "\n\n\n" << cntbuilds << "\n\n\n";
}
#endif