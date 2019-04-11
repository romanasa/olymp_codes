#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cassert>
#include <vector>
#include <set>
#include <string>

using namespace std;

typedef double db;

db pi = atan2(1.0, 1.0) * 4;

struct pt {
	db x, y;
	pt() {}
	pt(db x1, db y1) { x = x1, y = y1; }
	db operator% (pt nxt) const { return x * nxt.y - y * nxt.x; }
	db operator* (pt nxt) const { return x * nxt.x + y * nxt.y; }
	pt operator- (pt nxt) const { return pt(x - nxt.x, y - nxt.y); }
};

#define line pair<pair<db, db>, db>
#define mp make_pair

line getLine(pt s, pt t) {
	db a = t.y - s.y;
	db b = s.x - t.x;
	db c = -(a * s.x + b * s.y);
	return mp(mp(a, b), c);
}

db getSquare(vector<pt> a) {
	int n = (int)a.size();
	db ans = 0;
	for (int i = 0; i < n; i++) ans += a[i] % a[(i + 1) % n];
	return abs(ans) / (db)2;
}

pt inter(line A, line B) {
	db x = -(A.second * B.first.second - B.second * A.first.second) / (A.first.first * B.first.second - B.first.first * A.first.second);
	db y = -(A.first.first * B.second - B.first.first * A.second) / (A.first.first * B.first.second - B.first.first * A.first.second);
	return pt(x, y);
}

db getSignDist(line A, pt M) {
	return A.first.first * M.x + A.first.second * M.y + A.second;
}

pt rot(pt A, db angle) {
	angle = -angle;
	db x = A.x, y = A.y;
	return pt(x*cos(angle) - y*sin(angle), y*cos(angle) + x*sin(angle));
}

void add(vector<pt> &cur, line m) {
	if (cur.empty()) return;
	int ind1 = -1, ind2 = -1;
	pt M, N;

	int ok = 0;
	for (int i = 0; i < (int)cur.size(); i++) {
		if (getSignDist(m, cur[i]) > 0) ok = 1;
	}
	if (!ok) {
		cur.clear();
		return;
	}

	for (int i = 0; i < (int)cur.size(); i++) {
		pt A = cur[i];
		pt B = cur[(i + 1) % (int)cur.size()];

		if (getSignDist(m, A) >= 0 && getSignDist(m, B) < 0) {
			ind1 = i;
			M = inter(getLine(A, B), m);
		}
		if (getSignDist(m, A) < 0 && getSignDist(m, B) >= 0) {
			ind2 = (i + 1) % (int)cur.size();
			N = inter(getLine(A, B), m);
		}
	}
	if (ind1 == -1 || ind2 == -1) return;
	if (ind1 == ind2) return;

	if (ind1 < ind2) {
		cur.erase(cur.begin() + ind1 + 1, cur.begin() + ind2);
		cur.insert(cur.begin() + ind1 + 1, N);
		cur.insert(cur.begin() + ind1 + 1, M);
	} else {
		cur.erase(cur.begin() + ind1 + 1, cur.end());
		cur.erase(cur.begin(), cur.begin() + ind2);
		cur.insert(cur.end(), M);
		cur.insert(cur.end(), N);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	db alpha;

	cin >> n >> alpha;

	vector<string> A(2 * n);
	for (int i = 0; i < 2 * n; i++) {
		cin >> A[i];
	}


	for (int ni = 0; ni < 2 * n; ni++) {
		for (int nj = 0; nj < 2 * n; nj++) {

			int nx = -n + nj;
			int ny = (n - 1) - ni;
			int out = 0;

			//cerr << "ni = " << ni << ", nj = " << nj << endl;

			for (int i = max(0, ni - 2); i < min(2 * n, ni + 2); i++) {
				for (int j = max(0, nj - 2); j < min(2 * n, nj + 2); j++) {

					int x = -n + j;
					int y = (n - 1) - i;

					//cerr << "ok2" << endl;

					vector<pt> cur = { pt(x, y), pt(x + 1, y), pt(x + 1, y + 1), pt(x, y + 1) };
					for (int t = 0; t < 4; t++) cur[t] = rot(cur[t], alpha);


					//cerr << "ok5" << endl;

					vector<pt> cur2 = { pt(nx, ny), pt(nx + 1, ny), pt(nx + 1, ny + 1), pt(nx, ny + 1) };

					//cerr << "i = " << i << ", j = " << j << endl;

					for (int it = 0; it < 4; it++) {
						line cl = getLine(cur2[it], cur2[(it + 1) % 4]);
						if (getSignDist(cl, cur2[(it + 2) % 4]) < 0) cl.first.first *= -1, cl.first.second *= -1, cl.second *= -1;


						//cerr << "cur = "; for (auto c : cur) cerr << "(" << c.x << ", " << c.y << "), "; cerr << endl;
						//cerr << "add " << cl.first.first << ", " << cl.first.second << ", " << cl.second << endl;
						add(cur, cl);
					}
					//cerr << "cur = "; for (auto c : cur) cerr << "(" << c.x << ", " << c.y << "), "; cerr << endl;

					if (getSquare(cur) > 0.5) {
                        //cerr << "opa" << endl;
                        cout << A[i][j];
                        assert(!out);
                        out = 1;
					}
					//cerr << "ok" << endl;
				}
				//cerr << "ok3" << endl;
			}
			if (!out) cout << ".";
		}
		cout << "\n";
	}
}


