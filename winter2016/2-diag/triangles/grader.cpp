#include <algorithm>
#include <array>
#include <cstdio>
#include <iomanip>
#include <ios>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <string>

#include "grader.h"

using namespace std;

static int isRun = 0;

namespace {

int questions = 0;

struct Question {
	double a, b, c;
};
using Point = array<int, 2>;
using Claim = array<Point, 3>;

const double MIN_SQR = 0.25e-6;
const double MAX_SQR = 4.00e+6;
const int MAX_Q = 1000;
const int MAX_X = 1000;
const double MAX_A = 2e3;
const double MAX_C = 4e6;

static array<Point, 3> zone;

double part(double u, double v) {
	return u / (u - v);
}

pair<double, double> solve(double a, double b, double c) {
	vector<double> pos, neg;
	for (int i = 0; i < 3; ++i) {
		double v = a * zone[i][0] + b * zone[i][1] - c;
		if (v >= 0) pos.emplace_back(v);
		else if (v < 0) neg.emplace_back(v);
		else {
			printf("FAIL a x + b y - c is NaN despite precondition checks");
		}
	}
	if (pos.empty())
		return make_pair(1.0, 0.0);
	else if (neg.empty())
		return make_pair(0.0, 1.0);
	else if (pos.size() > neg.size()) {
		double p = part(neg[0], pos[0]) * part(neg[0], pos[1]);
		return make_pair(p, 1.0 - p);
	} else {
		double q = part(pos[0], neg[0]) * part(pos[0], neg[1]);
		return make_pair(1.0 - q, q);
	}
}

string to_string(const Point &a) {
	string s("(");
	s.append(std::to_string(a[0]));
	s.append(",");
	s.append(std::to_string(a[1]));
	s.append(")");
	return s;
}

template<class T, size_t N>
string to_string(const array<T, N> &a) {
	string s("[");
	for (size_t i = 0; i < N; ++i) {
		if (i) s.append(" ");
		s.append(to_string(a[i]));
	}
	s.append("]");
	return s;
}

}

void question(double a, double b, double c, double *p, double *q) {
	if (++questions > MAX_Q) {
		printf("WA Used more than %d queries", MAX_Q);
		exit(0);
	}
	double sqr = a * a + b * b;
	if (!(MIN_SQR <= sqr && sqr <= MAX_SQR)) {
		printf("WA Double a^2+b^2=%f violates the range [%f, %f]",
				sqr, MIN_SQR, MAX_SQR);
		exit(0);
	}
	if (!(-MAX_A <= a && a <= MAX_A)) {
		printf("WA Double a=%f violates the range [%f, %f]",
				a, MAX_A, MAX_A);
		exit(0);
	}
	if (!(-MAX_A <= b && b <= MAX_A)) {
		printf("WA Double b=%f violates the range [%f, %f]",
				b, MAX_A, MAX_A);
		exit(0);
	}
	if (!(-MAX_C <= c && c <= MAX_C)) {
		printf("WA Double c=%f violates the range [%f, %f]",
				c, MAX_C, MAX_C);
		exit(0);
	}
	auto x = solve(a, b, c);
	*p = x.first;
	*q = x.second;
}

int main() {
	if (isRun) {
		printf("SV User tries to hack the system");
		exit(3128);
	}
	isRun = 1;

	int group;
	scanf("%d", &group);
	for (int i = 0; i < 3; ++i) {
		scanf("%d %d", &zone[i][0], &zone[i][1]);
		assert(-MAX_X <= zone[i][0] && zone[i][0] <= MAX_X);
		assert(-MAX_X <= zone[i][1] && zone[i][1] <= MAX_X);
	}
	int answer[3][2];
	int *buff[3] = {answer[0], answer[1], answer[2]};
	solution(group, buff);
	Claim claim;
	for (int i = 0; i < 3; ++i) {
		claim[i][0] = answer[i][0];
		claim[i][1] = answer[i][1];
	}
	sort(begin(zone), end(zone));
	sort(begin(claim), end(claim));
	if (zone == claim) {
		printf("OK ja=%s pa=%s\n",
				to_string(zone).c_str(), to_string(claim).c_str());
	} else {
		printf("WA ja=%s pa=%s\n",
				to_string(zone).c_str(), to_string(claim).c_str());
		//assert(0);
	}
	return 0;
}
