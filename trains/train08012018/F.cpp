#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int n, k;
int need, gr;
int T[234];

int calc() {
	int cur = 0;
	for (int i = 0; i < n; i += gr) {
		int s = 0;
		for (int j = 0; j < gr; j++) s += T[i + j];
		cur += abs(s - need);
	}
	return cur;
}

void out() {
	for (int i = 0; i < n; i += gr) {
		for (int j = 0; j < gr; j++) cout << T[i + j] << " ";
		cout << "\n";
	}
	exit(0);
}

int main() {
	cin >> n >> k;
	
	gr = n / k;
	need = n * (n + 1) / 2 / k;		
	
	for (int i = 0; i < n; i++) T[i] = i + 1;
	
	while (1) {
		random_shuffle(T, T + n);
		
		int cur = calc();
		if (cur == 0) out();
		
		for (int it = 0; it < 5 * n * n; it++) {
			int i = rand() % n, j = rand() % n;
			
			swap(T[i], T[j]);
			
			int t = calc();
			if (t == 0) out();
			
			if (cur < t) swap(T[i], T[j]);
			else cur = t;
		}
		
		if (clock() > 0.9 * CLOCKS_PER_SEC) return 0 * puts("0");
	}
	
	return 0;
}