#include "grader.h"
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
void encode(int N, int M[]) {
	int cnt1 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 8; j += 2) {
			int a = (M[i] >> j) & 1;
			int b = (M[i] >> (j + 1)) & 1;
			int pos = 4 * i + j / 2;
			
			for (int cnt = 0; cnt < 2 * a + b; cnt++) {
				cnt1++;
			}
		}
	}
	
	int cnt2 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 8; j += 2) {
			int a = (M[i] >> j) & 1;
			int b = (M[i] >> (j + 1)) & 1;
			int pos = 4 * i + j / 2;

			a ^= 1, b ^= 1;
				
			for (int cnt = 0; cnt < 2 * a + b; cnt++) {
				cnt2++;
			}
		}
	}
	
	if (cnt1 > cnt2) {
		send(0), send(0), send(0), send(0);
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 8; j += 2) {
			int a = (M[i] >> j) & 1;
			int b = (M[i] >> (j + 1)) & 1;
			int pos = 4 * i + j / 2;

			if (cnt1 > cnt2) a ^= 1, b ^= 1;
				
			for (int cnt = 0; cnt < 2 * a + b; cnt++) {
				send(pos);
			}
		}
	}
}
