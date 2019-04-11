#include "encoder.h"
#include <cstdio>
#include "encoderlib.h"
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
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
