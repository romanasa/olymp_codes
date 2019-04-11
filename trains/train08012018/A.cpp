#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

double x[31], y[31];
int n;
	
double ans = 1e20;
double ansA, ansB, ansC;

double get(double a, double b, double c) {
	double s = 0;
	for (int i = 0; i < n; i++) {
		s += abs(a * x[i] * x[i] + b * x[i] + c - y[i]);
	}
	if (s < ans) {
		ans = s;
		ansA = a, ansB = b, ansC = c;
	}
	return s;
}

double get(double a, double b) {
	double l = -1e4, r = 1e4;
	for (int it = 0; it < 100; it++) {
		double m1 = l + (r - l) / 3;
		double m2 = r - (r - l) / 3;
		
		if (get(a, b, m1) < get(a, b, m2)) r = m2;
		else l = m1;
	}
	return get(a, b, l);
}

double get(double a) {
	double l = -1e4, r = 1e4;
	for (int it = 0; it < 100; it++) {
		double m1 = l + (r - l) / 3;
		double m2 = r - (r - l) / 3;
		
		if (get(a, m1) < get(a, m2)) r = m2;
		else l = m1;
	}
	return get(a, l);
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
	
	double l = -1e4, r = 1e4;
	for (int it = 0; it < 100; it++) {
		double m1 = l + (r - l) / 3;
		double m2 = r - (r - l) / 3;
		
		if (get(m1) < get(m2)) r = m2;
		else l = m1;
	}
	
	cout.precision(10);
	cout << fixed << ansA << "\n" << ansB << "\n" << ansC << "\n";

	return 0;
}