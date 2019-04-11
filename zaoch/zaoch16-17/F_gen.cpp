#include <bits/stdc++.h>
#include <random>
#define ll long long

using namespace std;

const int C = 1e9;

int main(int argc, char* argv[]) {

	int n = 3e6;

	mt19937 rnd(atoi(argv[1]));

	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		printf("%d ", rnd() % (C + C + 1) - C);
	}
	return 0;
}
