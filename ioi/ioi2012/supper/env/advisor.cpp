#include <queue>
#include "advisor.h"

using namespace std;

const int dd = (int)1e5 + 7;

int nxt[dd], pos[dd], used[dd];
priority_queue<pair<int, int> > Q;
queue<int> E[dd];

void ComputeAdvice(int *C, int N, int K, int M) {
	fill(pos, pos + N, N);
	
	for (int i = N - 1; i >= 0; i--) {
		nxt[i] = pos[C[i]];
		pos[C[i]] = i;
	}
	
	for (int i = 0; i < K; i++) {
		used[i] = 1;
		Q.push({ pos[i], i });
	}
	
	for (int i = 0; i < N; i++) {
		if (used[C[i]]) {
			Q.push({ nxt[i], C[i] });
			E[C[i]].push(1);
			continue;
		}
		int cur = Q.top().second;
		Q.pop();
		
		used[cur] = 0, used[C[i]] = 1;
		Q.push({ nxt[i], C[i] });
		
		E[cur].push(0);
		E[C[i]].push(1);
	}
	
	for (int i = 0; i < K; i++) {
		if (E[i].empty()) WriteAdvice(0);
		else if (E[i].front() == 0) WriteAdvice(0), E[i].pop();
		else WriteAdvice(1);
	}
	
	for (int i = 0; i < N; i++) {
		E[C[i]].pop();
		if (E[C[i]].empty()) WriteAdvice(0);
		else if (E[C[i]].front() == 0) E[C[i]].pop(), WriteAdvice(0);
		else WriteAdvice(1);
	}
}

