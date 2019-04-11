#include "decoder.h"
#include "decoderlib.h"
#include <cstring>

int cnt[511];
int A[511];

void decode(int N, int L, int X[]) {
	memset(cnt, 0, sizeof(cnt));
	memset(A, 0, sizeof(A));
		
	for (int i = 0; i < L; i++) cnt[X[i]]++;
	
	int rev = 0;
	if (cnt[0] > 3) rev = 1, cnt[0] -= 4;
	
	for (int i = 0; i < 4 * N; i++) {
		int x = cnt[i];

		int a = i / 4, b = (i % 4) * 2;	
		
		if ((x >> 1) == 1 && !rev) A[a] |= 1 << b;
		if ((x >> 1) == 0 && rev) A[a] |= 1 << b;
		
		if ((x & 1) == 1 && !rev) A[a] |= 1 << (b + 1);
		if ((x & 1) == 0 && rev) A[a] |= 1 << (b + 1);
	}
	
	for (int i = 0; i < N; i++) {
		output(A[i]);
	}
}
