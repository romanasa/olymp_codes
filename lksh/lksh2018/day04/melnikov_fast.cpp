#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500500;

int n;
int tim;
int comp_count;
vector <int> g[MAXN];
vector <int> gr[MAXN];
vector <int> gc[MAXN];
vector <int> gcr[MAXN];
vector <int> gcu[MAXN];
int comp[MAXN];
int comp_size[MAXN];
int only_vert[MAXN];
bool used[MAXN];
vector <int> order;
bool reach0[MAXN];
bool reachn[MAXN];
bool cutpoint[MAXN];
bool loop[MAXN];
int up[MAXN];
int tin[MAXN];
int source;
int sink;
set<int> alive;

void clear(int n) {
  comp_count = 0;
  order.clear();
  for (int i = 0; i < n; i++) {
    g[i].clear();
    gr[i].clear();
    gc[i].clear();
    gcr[i].clear();
    gcu[i].clear();
    loop[i] = false;
    comp[i] = -1;
    only_vert[i] = -1;
    comp_size[i] = 0;
    used[i] = false;
    reach0[i] = false;
    reachn[i] = false;
    cutpoint[i] = false;
    tin[i] = -1;
    up[i] = -1;
  }
}

void add_edge(int u, int v) {
  g[u].push_back(v);
  gr[v].push_back(u);
}

void read() {
  int m;
  assert(scanf("%d%d", &n, &m) == 2);
  clear(n + 10);
  for (int i = 0; i < m; i++) {
    int u, v;
    assert(scanf("%d%d", &u, &v) == 2);
    --u, --v;
    add_edge(u, v);
    if (u == v) {
      loop[u] = true;
    }
  }
}

void dfs_condense1(int v) {
  used[v] = true;
  for (int nv : g[v]) {
    if (!used[nv]) {
      dfs_condense1(nv);
    }
  }
  order.push_back(v);
}

void dfs_condense2(int v, int c) {
  comp[v] = c;
  comp_size[c]++;
  for (int nv : gr[v]) {
    if (comp[nv] == -1) {
      dfs_condense2(nv, c);
    }
  }
}

void add_edge_condense(int u, int v) {
  gc[u].push_back(v);
  gcr[v].push_back(u);

  gcu[u].push_back(v);
  gcu[v].push_back(u);
}

void condense() {
  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      dfs_condense1(i);
    }
  }
  reverse(order.begin(), order.end());
  comp_count = 0;
  for (int v : order) {
    if (comp[v] == -1) {
      dfs_condense2(v, comp_count);
      if (comp_size[comp_count] == 1) {
        only_vert[comp_count] = v;
      }
      comp_count++;
    }
  }

  for (int u = 0; u < n; u++) {
    int cu = comp[u];
    for (int v : g[u]) {
      int cv = comp[v];
      if (cu != cv) {
        add_edge_condense(cu, cv);
      }
    }
  }

  source = comp_count;
  sink = comp_count + 1;
  add_edge_condense(source, comp[0]);
  add_edge_condense(comp[n - 1], sink);

  /*for (int i = 0; i < n; i++) {
    cerr << i << " color: " << comp[i] << endl;
  }
  */
}

void dfs_reachable1(int v) {
  used[v] = true;
  reach0[v] = true;
  for (int nv : gc[v]) {
    if (!used[nv]) {
      dfs_reachable1(nv);
    }
  }
}

void dfs_reachable2(int v) {
  used[v] = true;
  reachn[v] = true;
  for (int nv : gcr[v]) {
    if (!used[nv]) {
      dfs_reachable2(nv);
    }
  }
}

void mark_reachable() {
  memset(used, false, sizeof(used));
  dfs_reachable1(source);
  memset(used, false, sizeof(used));
  dfs_reachable2(sink);
  /*cerr << "reachability:\n";
  for (int i = 0; i < comp_count; i++) {
    cerr << i << " " << reach0[i] << " " << reachn[i] << endl;
  }
  */
}

void dfs_cutpoints(int v, int par) {
  used[v] = true;
  tin[v] = up[v] = tim++;
  int chd_count = 0;
  for (int nv : gcu[v]) {
    if (!reach0[nv] || !reachn[nv]) {
      continue;
    }
    if (nv == par) {
      continue;
    }
    if (used[nv]) {
      up[v] = min(up[v], tin[nv]);
    } else {
      dfs_cutpoints(nv, v);
      up[v] = min(up[v], up[nv]);
      if (up[nv] >= tin[v] && par != -1) {
        cutpoint[v] = true;
      }
      chd_count++;
    }
  }
  if (par == -1 && chd_count > 1) {
    cutpoint[v] = true;
  }
}

void find_cutpoints() {
  memset(used, false, sizeof(used));
  tim = 0;
  dfs_cutpoints(source, -1);
  /*cerr << "cut_points:\n";
  for (int i = 0; i < comp_count; i++) {
    cerr << i << " " << cutpoint[i] << endl;
  }
  */
}

void solve() {
  condense();
  mark_reachable();
  find_cutpoints();
  vector <int> ans;
  for (int i = 0; i < comp_count; i++) {
    if (comp_size[i] == 1 && reach0[i] && reachn[i] && cutpoint[i]) {
      assert(only_vert[i] != -1);
      assert(tin[i] != -1);
      if (!loop[only_vert[i]]) {
        ans.push_back(i);
      }
    }
  }
  sort(ans.begin(), ans.end(), [](int u, int v) { return tin[u] < tin[v]; });
  printf("%d\n", (int)ans.size());
  bool first = true;
  for (int v : ans) {
    assert(only_vert[v] != -1);
    if (!first) {
      printf(" ");
    }
    printf("%d", only_vert[v] + 1);
    first = false;
  }
  puts("");
}

int main() {
  freopen("dfs.in", "r", stdin);
  freopen("dfs.out", "w", stdout);
  int nt;
  assert(scanf("%d", &nt) == 1);
  for (int tt = 0; tt < nt; tt++) {
    cerr << "test " << tt << endl;
    read();
    solve();
  }
  return 0;
}
