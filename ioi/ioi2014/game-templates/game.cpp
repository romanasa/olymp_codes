#include "grader.h"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int dd = (int)1507;

int cnt[dd];

void initialize(int n) { }

int hasEdge(int u, int v) {
	return ++cnt[max(u, v)] == max(u, v);
}
