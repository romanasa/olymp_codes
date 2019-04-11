#include <bits/stdc++.h>

using namespace std;

int main() {
	int a = 5;
	cout << (a ^ (a = 0) == a);
	return 0;
}