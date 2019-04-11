/**
 * Author: Catalin Francu
 * Method:
 * - Precompute all numbers of the form b^x + b^y where x >= 4.
 * - Sort the queries and answer them in increasing order.
 * - Maintain the highest fitting perfect cube and its root.
 * - For every query, first look it up in the precomputed list.
 * - If it fails, solve the cases x = 3, 2, 1 by hand.
 **/
#include <algorithm>
#include <math.h>
#include <stdio.h>

#define MAX_QUERIES 100000
#define MAX_CUBE 2642246 // first number for which x^3 exceeds 64 bits

// length of the precomputed list, determined experimentally
#define NUM_POWERS 322000
#define EPS 0.000001

typedef unsigned long long u64;

typedef struct {
  u64 value;
  int base;
} power;

typedef struct {
  u64 n, answer;
} query;

power p[NUM_POWERS];
u64 buf[64]; // stores 1, b, b^2, b^3, ... for a given base
query q[MAX_QUERIES];

// indirection -- traversing q in the order of ind sorts q.n
int ind[MAX_QUERIES];

// Returns 1 iff a + b overflows 64 bits.
inline int overflowsS(u64 a, u64 b) {
  return a + b < a;
}

// Returns 1 iff a * b overflows 64 bits.
// Assumes b fits in 32 bits.
// Method: write a as ah|al (two halves on 32 bits each),
// then a * b = (ah * b) << 32 + (al * b)
int overflowsP(u64 a, u64 b) {
  u64 hi = (a >> 32) * b;
  u64 lo = (a & 0xffffffffull) * b;

  return (hi > 0xffffffffull) || overflowsS(hi << 32, lo);
}

int powerCmp(power a, power b) {
  return (a.value < b.value) || ((a.value == b.value) && (a.base < b.base));
}

int indCmp(int a, int b) {
  return (q[a].n < q[b].n);
}

int main(void) {

  // generate all numbers b^x + b^y with x >= 4 and x > y
  int np = 0;
  for (unsigned b = 2; b < (1 << 16); b++) {
    // append to buf[] all the powers of b that fit on 64 bits
    u64 v = 1;
    int x = 0; // v = b^x
    while (!overflowsP(v, b)) {
      buf[x++] = v;
      v *= b;
    }
    buf[x++] = v;

    // append to p[] all the sums b^x + b^y
    for (int i = 4; i < x; i++) {
      for (int j = 0; j < i; j++) {
        if (!overflowsS(buf[i], buf[j])) {
          p[np].value = buf[i] + buf[j];
          p[np].base = b;
          np++;
        }
      }
    }
  }
  p[np].value = 0xffffffffffffffffull; // sentinel
  std::sort(p, p + np, powerCmp);

  int numQueries;
  // read the data

  scanf("%d", &numQueries);
  for (int i = 0; i < numQueries; i++) {
    scanf("%llu", &q[i].n);
  }

  for (int i = 0; i < numQueries; i++) {
    ind[i] = i;
  }
  std::sort(ind, ind + numQueries, indCmp);

  int ppos = 0;
  u64 cubeRoot = 1, cube = 1;

  for (int i = 0; i < numQueries; i++) {
    // answer the query q[ind[i]].n
    u64 n = q[ind[i]].n;

    // look for n in p
    while (p[ppos].value < n) {
      ppos++;
    }

    if ((ppos < np) && (p[ppos].value == n)) {
      q[ind[i]].answer = p[ppos].base;
    } else {

      // try x = 3
      while ((cubeRoot < MAX_CUBE) && (cube < n)) {
        cubeRoot++;
        cube = cubeRoot * cubeRoot * cubeRoot;
      }
      cubeRoot--; 
      cube = cubeRoot * cubeRoot * cubeRoot;

      if ((cube + 1 == n) || (cube + cubeRoot == n) || (cube + cubeRoot * cubeRoot == n)) {
        q[ind[i]].answer = cubeRoot;
      } else {

        // try x = 2
        u64 squareRoot = (u64)(sqrtl(n) + EPS);
        u64 square = squareRoot * squareRoot;
        if ((square + 1 == n) || (square + squareRoot == n)) {
          q[ind[i]].answer = squareRoot;
        } else {
          q[ind[i]].answer = n - 1; // n = 11 in base (n - 1)
        }
      }
    }
  }

  for (int i = 0; i < numQueries; i++) {
    printf("%llu\n", q[i].answer);
  }
   
  return 0;
}
