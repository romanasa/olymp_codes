/*
	если у вас Linux, то можно использовать /usr/bin/time -f "%e %MKB" ./prog
*/


#include <bits/stdc++.h>

using namespace std;

int main() {
	double start = clock();
	//solve();
	cerr << "Time " << (clock() - start)  * 1.0 / CLOCKS_PER_SEC << "s\n";
	return 0;
}