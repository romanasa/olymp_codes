#include "grader.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

ll A[3001][3001];


long long gcd(long long X, long long Y) {
    long long tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

void init(int R, int C) {
	assert(R <= 100 && C <= 100);
}

void update(int P, int Q, long long K) {	
	A[P][Q] = K;
}

long long calculate(int P, int Q, int U, int V) {
    ll ans = 0;
    for (int i = P; i <= U; i++)
    	for (int j = Q; j <= V; j++)
    		ans = gcd(ans, A[i][j]);
    return ans;
}
