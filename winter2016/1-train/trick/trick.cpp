#include <cassert>
#include <algorithm>
#include "trick.h"

using namespace std;

void Initialize() {
}

int F(int x, int y) {
	return (3 * x) ^ (64 * y);	
}

void Assistant(int r, int n, int *hand, int *cards) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum = (sum + hand[i]) % (2 * n + 1);
		
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) if (i != j) {
			if (F(hand[i], hand[j]) % (2 * n + 1) == sum) { 	
				cards[0] = hand[i];
				cards[1] = hand[j];
			}
		}
	}
}

int Magician(int n, int assistant1[2], int assistant2[2]) {
	int c1 = F(assistant1[0], assistant1[1]) % (2 * n + 1);
	int c2 = F(assistant2[0], assistant2[1]) % (2 * n + 1);
	return (4 * n + 2 - c1 - c2) % (2 * n + 1);
}
