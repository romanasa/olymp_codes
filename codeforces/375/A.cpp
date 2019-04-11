#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	int t1 = abs(a - b) + abs(c - b);
	int t2 = abs(b - a) + abs(c - a);
	int t3 = abs(b - c) + abs(a - c);
	cout << min(min(t1, t2), t3);
	return 0;
}