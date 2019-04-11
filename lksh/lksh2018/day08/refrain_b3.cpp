#include <cassert>
#include <cstdio>
#include <cstring>

#include <iostream>

using namespace std;

struct Node {
  Node *next[10];
  Node *suff;
  int l;
  int term;
  int d1, d2;

  Node () {
    memset (next, 0, sizeof (next));
    suff = 0, l = 0, term = 0;
    d1 = d2 = -1;
  }
};

long long ans = -1;
int n, ans_st, ans_k;
Node *ans_x;

void dfs ( Node *x ) {
  x->d1 = x->term;
  x->d2 = 0;
  for (int i = 0; i < 10; i++) {
    if (!x->next[i])
      continue;
    if (x->next[i]->d1 == -1)
      dfs (x->next[i]);
    x->d1 += x->next[i]->d1;
    x->d2 = x->next[i]->d2 + 1;
  }
  long long res = (long long)x->l * x->d1;
  if (res > ans) {
    ans = res;
    ans_st = n - x->d2 - x->l;
    ans_k = x->l;
    ans_x = x;
  }
}

int main () {
  assert (freopen ("refrain.in", "r", stdin));
  assert (freopen ("refrain.out", "w", stdout));

  Node *st = new Node;
  Node *u = st;

  int n, m;
  assert (scanf ("%d%d", &n, &m) == 2);
  ::n = n;
  int a[n];
  for (int i = 0; i < n; i++) {
    assert (scanf ("%d", &a[i]) == 1);
    a[i]--;
    Node *x = new Node;
    x->l = u->l + 1;
    for (Node *t = u; t != 0; t = t->suff) {
      Node *b = t->next[a[i]];
      if (!b) {
        t->next[a[i]] = x;
        continue;
      }
      if (t->l + 1 == b->l) {
        x->suff = b;
      } else {
        Node *bx = new Node;
        memcpy (bx->next, b->next, sizeof (b->next));
        bx->l = t->l + 1;
        bx->suff = b->suff;
        b->suff = x->suff = bx;
        while (t && t->next[a[i]] == b) {
          t->next[a[i]] = bx;
          t = t->suff;
        }
      }
      break;
    }
    if (!x->suff)
      x->suff = st;
    u = x;
  }
  for (Node *t = u; t != 0; t = t->suff)
    t->term = 1;

  dfs (st);
  cout << ans << endl;
  printf ("%d\n", ans_k);
  Node *x = st;
  for (int i = 0; i < ans_k; i++) {
    assert (x->next[a[ans_st + i]]);
    x = x->next[a[ans_st + i]];
    printf ("%d%c", a[ans_st + i] + 1, "\n "[i < ans_k - 1]);
  }
  assert (x == ans_x);

  return 0;
}

