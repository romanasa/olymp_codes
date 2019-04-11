#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
 
typedef long long ll;
 
using namespace std;
 
const int dd = (int)1e5 + 1;
int a[dd];
 
ll Q[dd];
vector<vector<int> > E;
 
const int maxC = (int)6e6 + 1;
vector<int> G[dd];
bitset<maxC> F;
int I[maxC];
 
int cur[10], ind;
 
struct st {
    unordered_map<int, int> M, T;
 
    void add(int x, int val) {
        ind = 0;
        if (x != 1) for (int t : G[I[x]]) cur[ind++] = t;
        //assert(ind < 8);
 
        for (int msk = 0; msk < (1 << ind); msk++) {
            int p = 1;
            for (int i = 0; i < ind; i++) if ((msk >> i) & 1) p *= cur[i];
            M[p] += val;
        }
        T[x] += val;
    }
 
    int get(int x) {
        ind = 0;
        if (x != 1) for (int t : G[I[x]]) cur[ind++] = t;
 
        int res = 0;
        for (int msk = 0; msk < (1 << ind); msk++) {
            int p = 1, c = 1;
            for (int i = 0; i < ind; i++) if ((msk >> i) & 1) p *= cur[i], c = -c;
            auto it = M.find(p);
            if (it != M.end()) {
                res += it->second * c;
            }
        }
        return res;
    }
 
    int size() {
        return (int)T.size();
    }
};
 
st dfs(int v, int pr = -1) {
    st cur;
 
    for (int to : E[v]) {
        auto t = dfs(to, v);
 
        Q[v] += Q[to];
 
        if (t.size() > cur.size()) swap(t, cur);
 
        for (auto c : t.T) {
            Q[v] += cur.get(c.first) * c.second;
        }
 
        for (auto c : t.T) {
            cur.T[c.first] += c.second;
        }
        for (auto c : t.M) {
            cur.M[c.first] += c.second;
        }
    }
    Q[v] += cur.get(a[v]);
    cur.add(a[v], 1);
    return cur;
}
 
int main() {
    for (int i = 2; i < maxC; i++) F[i] = 1;
    fill(I, I + maxC, -1);
    for (int i = 2; i * i <= maxC; i++) {
        if (F[i])
            for (int j = i * i; j < maxC; j += i)
                F[j] = 0;
    }
 
    int n;
    scanf("%d", &n);
    E.resize(n);
 
    int root = -1;
 
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
 
        if (I[a[i]] != -1 || a[i] == 1) continue;
        I[a[i]] = i;
        for (int j = 1; j * j <= a[i]; j++) {
            if (a[i] % j) continue;
            if (F[j]) G[i].push_back(j);
            if (j * j != a[i] && F[a[i] / j]) G[i].push_back(a[i] / j);
        }
    }
 
    //for (int i = 0; i < 20; i++) {
    //    err("G[%d] = {", i); for (int x : G[i]) err(" %d,", x); err(" }\n");
    //}
 
    for (int i = 0; i < n; i++) {
        int p;
        scanf("%d", &p);
        if (p == 0) root = i;
        else E[p - 1].push_back(i);
    }
    dfs(root);
    for (int i = 0; i < n; i++) printf("%lld ", Q[i]);
    printf("\n");
    return 0;
}