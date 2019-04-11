#include "grader.h"


#ifdef HOME
	#include "cluedo.h"
#endif

void Solve() {
	int A[] = { 0, 6, 10, 6 };
	
	int ind = Theory(A[1], A[2], A[3]);
	while (ind) {
		A[ind]--;
		ind = Theory(A[1], A[2], A[3]);
	}
}
