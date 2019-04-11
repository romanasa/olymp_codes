#include "grader.h"
#ifdef HOME
	#include "memory.h"
#endif
#include <bits/stdc++.h>

using namespace std;

map<char, vector<int> > Q;

void play() {
	for (int i = 1; i <= 50; i++) {
		char c = faceup(i);
		Q[c].push_back(i);
	}

	for (auto c : Q) {
		faceup(c.second[0]);
		faceup(c.second[1]);
	}
}
