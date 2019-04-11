/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <cstdio>
#include <cstring>
#include <cassert>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int blen = 4;
const int base = 1e4;
const int mlen = 1 << 16;

typedef long long ll;

int len = 1, a[mlen], b[mlen];
ll c[2 * mlen];
int need = 0;

void Read( int *a ) {
  static char *s = new char[mlen * blen + 1];
  scanf("%s", s);
  
  if (s[0] == '-') need ^= 1, s++;
  
  int j = 0, x = 1, i = strlen(s) - 1;
  while (i >= 0) {
    if (x == base) j++, x = 1;
    a[j] += (s[i--] - '0') * x, x *= 10;
  }
  while (len <= j) len <<= 1;
}

void Out( ll *a, int n ) {
  int i = n - 1;
  while (i && !a[i])
    i--;
  printf("%d", (int)a[i--]);
  while (i >= 0)
    printf("%0*d", blen, (int)a[i--]);
  puts("");
}

void Mul( int n, ll *c, int *a, int *b ) {
  if (n <= 16) {
    memset(c, 0, sizeof(c[0]) * (n * 2));
    forn(i, n) forn(j, n) c[i + j] += (ll)a[i] * b[j];
    return;
  }

  int n1 = n / 2;
  Mul(n1, c, a, b);
  Mul(n1, c + n, a + n1, b + n1);

  ll c1[n];
  int a1[n1], b1[n1]; // we may get rid of these additional arrays
  forn(i, n1) a1[i] = a[i] + a[i + n1], b1[i] = b[i] + b[i + n1];
  Mul(n1, c1, a1, b1);
  forn(i, n) c1[i] -= c[i] + c[i + n];
  forn(i, n) c[i + n1] += c1[i];
}

void Cor( ll *c, int n ) {
  forn(i, n - 1)
    c[i + 1] += c[i] / base, c[i] %= base; 
}

int main() {
  //assert(freopen("mul.in", "r", stdin));
  //assert(freopen("mul.out", "w", stdout));

  Read(a);
  Read(b);
  Mul(len, c, a, b);
  Cor(c, 2 * len);
  
  if (need) putchar('-');
  Out(c, 2 * len);
}
