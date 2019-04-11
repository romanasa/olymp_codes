#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
   
using namespace std;
   
typedef long long ll;
   

struct AhoCorasick {
    vector<string> A;
    int sz = 0, is;
       
    AhoCorasick() { root = newnode(); }
    
    vector<vector<int> > go;
    vector<int> suf, p, cnt;
    vector<char> c, term;
      
    void reserve(int n) {
    	go.reserve(n), suf.reserve(n), p.reserve(n);
    	cnt.reserve(n), c.reserve(n), term.reserve(n);
    }
    
    void clear() {
    	sz = 0, is = 0; 
    	A.resize(0), go.resize(0);
    	suf.resize(0), p.resize(0), c.resize(0), cnt.resize(0), term.resize(0);
    	root = newnode();
    }
    
    int root;
      
    int newnode() {
    	go.push_back(vector<int>(3, -1));
    	suf.push_back(-1), p.push_back(-1), c.push_back(-1);
    	cnt.push_back(-1), term.push_back(0);
    	return (int)go.size() - 1;
    }
       
    void add(string &s) {
        sz += (int)s.size();
        int cur = root;
        for (char c : s) {
            if (go[cur][c - 'a'] == -1) go[cur][c - 'a'] = newnode();
            cur = go[cur][c - 'a'];
        }
        term[cur]++;
    }
       
    void build() {
    	deque<int> q;

        is = 1;
        q.push_back(root);
           
        while (q.size()) {      
            int v = q.front();
            q.pop_front();
               
            if (v == root) suf[v] = v;
            else suf[v] = (p[v] == root ? root : go[suf[p[v]]][c[v]]);
               
            cnt[v] = (v == root ? 0 : cnt[suf[v]] + term[v]);
 
            for (int i = 0; i < 3; i++) if (go[v][i] != -1) {
                p[go[v][i]] = v;
                c[go[v][i]] = i;
                q.push_back(go[v][i]);
            }
              
            for (int i = 0; i < 3; i++) if (go[v][i] == -1)
                go[v][i] = (v == root ? v : go[suf[v]][i]);
        }
    }
       
    ll ask(string &s) {
        if (!is) return 0;
        ll res = 0, cur = root;
        for (char c : s) {
            cur = go[cur][c - 'a'];
            res += cnt[cur];
        }
        return res;
    }
};
   
unordered_set<string> cur;
   
AhoCorasick A[25];
AhoCorasick B[25];
       
void addA(string s) {
    vector<string> Q;
    Q.push_back(s);
    int cur = (int)s.size();
      
    for (int i = 0; i < 25; i++) {
        if (A[i].sz + cur >= (1 << i)) {
            for (auto c : A[i].A) Q.push_back(c);
            cur += A[i].sz;
            A[i].clear();           
        } else {
        	A[i].clear();
        	A[i].reserve(1 << i);
            for (auto c : Q) A[i].A.push_back(c);
            for (auto c : A[i].A) A[i].add(c);
            A[i].build();
            break;
        }
    }
}
   
ll askA(string &s) {
    ll res = 0;
    for (int i = 0; i < 25; i++) if (A[i].is) {
        res += A[i].ask(s);
    }
    return res;
}
   
void addB(string s) {
    vector<string> Q;
    Q.push_back(s);
    int cur = (int)s.size();
    for (int i = 0; i < 25; i++) {
        if (B[i].sz + cur >= (1 << i)) {
            for (auto c : B[i].A) Q.push_back(c);
            cur += B[i].sz;
            B[i].clear();
        } else {
        	B[i].clear();
        	B[i].reserve(1 << i);
            for (auto c : Q) B[i].A.push_back(c);
            for (auto c : B[i].A) B[i].add(c);
            B[i].build();
            break;
        }
    }
}
   
ll askB(string &s) {
    ll res = 0;
    for (int i = 0; i < 25; i++) if (B[i].is) {
        res += B[i].ask(s);
    }
    return res;
}
   
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);  
    
    int n;
    cin >> n;
       
    ll x = 0;
       
    while (n--) {
        char c;
        cin >> c;
           
        string s;
        cin >> s;
   
        int q = x % (int)s.size();
          
        string t = s + s;
        s = string(t.begin() + q, t.begin() + q + (int)s.size());
           
        if (c == '+') {
            if (cur.count(s)) continue;
            cur.insert(s);
            addA(s);
        } else if (c == '-') {
            if (!cur.count(s)) continue;
            cur.erase(s);
            addB(s);
        } else {
            ll cur = askA(s) - askB(s); 
            cout << cur << "\n";
            x = cur;
        }
    }
    return 0;
}