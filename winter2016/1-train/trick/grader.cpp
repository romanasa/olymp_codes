#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

#include "trick.h"

static char secret[100];

int main() {
  scanf("%s", secret);
  printf("%s OK\n", secret);
  Initialize();

  int TN;
  assert(scanf("%d", &TN) == 1);
  for (int i = 0; i < TN; i++) {
    int n;
    assert(scanf("%d", &n) == 1);
    vector<int> a(n), b(n);
    for (int &x : a) {
      assert(scanf("%d", &x) == 1);
    }
    for (int &x : b) {
      assert(scanf("%d", &x) == 1);
    }
    int cards1[2], cards2[2];
    Assistant(1, n, &a[0], cards1);
    Assistant(2, n, &b[0], cards2);
    printf("%d\n", Magician(n, cards1, cards2));
  }
  return 0;
}
