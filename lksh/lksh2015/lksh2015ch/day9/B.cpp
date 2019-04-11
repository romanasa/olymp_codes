#include <cassert>
#include <cstdio>

using namespace std;

unsigned long long p[20] = {1, 2, 3, 5, 7, 11, 13, 17, 19,
  23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
  
unsigned long long mx = 0;
unsigned long long x;
unsigned long long n;

void recur(int d, unsigned long long res, unsigned long long m)
{
  if (res > mx || (res == mx && m < x))
  {
    mx = res;
    x = m;
  }
  unsigned long long pow = 1;
  unsigned long long r = p[d];
  while(m * r <= n && m * r > 0)
  {
    recur(d + 1, res * (pow + 1), m * r);
    r*=p[d];
    if (r < 0)
      break;
    pow++;
  }
}

int main( void )
{
  scanf("%lld", &n);
  assert (1 <= n && n <= 1000000000000000000ll);
  recur(1, 1ll, 1ll);
  printf("%lld %lld\n", mx, x);
  return 0;
}
