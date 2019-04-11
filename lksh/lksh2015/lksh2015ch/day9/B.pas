#include <cassert>
#include <cstdio>

using namespace std;

int p[20] = {1, 2, 3, 5, 7, 11, 13, 17, 19,
  23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
int q[20];
long long mx = 0;
long long x;
long long n;

void recur(int d, long long res, long long m)
{
  if (res > mx || (res == mx && m < x))
  {
    mx = res;
    x = m;
  }
  long long pow = 1;
  long long r = p[d];
  while(pow <= q[d - 1] && m * r <= n && m * r > 0)
  {
    q[d] = pow;
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
  q[0] = 1000000000;
  recur(1, 1ll, 1ll);
  printf("%lld %lld\n", mx, x);
  return 0;
}
