#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;


struct Q {
	int r, g, b;
};

map<int, Q> D;
map<int, int> sum;
set<pair<int, int>> R, G, B;

int clacR(int id) {
	auto it = R.find({ D[id].r, id });
	auto itL = it, itR = it;
	itR++;
	if (it == R.begin()) itL = R.end();
	itL--;
	if (itR == R.end()) itR = R.begin();
	int ans = itR->first - itL->first;
	if (ans <= 0) ans += 360;
	if (it->first == itL->first || it->first == itR->first) ans = 0;
	return ans;
}

int clacG(int id) {
	auto it = G.find({ D[id].g, id });
	auto itL = it, itR = it;
	itR++;
	if (it == G.begin()) itL = G.end();
	itL--;
	if (itR == G.end()) itR = G.begin();
	int ans = itR->first - itL->first;
	if (ans <= 0) ans += 360;
	if (it->first == itL->first || it->first == itR->first) ans = 0;
	return ans;
}

int clacB(int id) {
	auto it = B.find({ D[id].b, id });
	auto itL = it, itR = it;
	itR++;
	if (it == B.begin()) itL = B.end();
	itL--;
	if (itR == B.end()) itR = B.begin();
	int ans = itR->first - itL->first;
	if (ans <= 0) ans += 360;
	if (it->first == itL->first || it->first == itR->first) ans = 0;
	return ans;
}

int calcSum(int id) {
	return clacR(id) + clacG(id) + clacB(id);
}

set<pair<int, int>> setS;

void removeR(int id) {
	auto it = R.find({ D[id].r, id });
	auto itL = it, itR = it;
	itR++;
	if (it == R.begin()) itL = R.end();
	itL--;
	if (itR == R.end()) itR = R.begin();
	int idL = itL->second, idR = itR->second;
	R.erase(it);
	setS.erase({ sum[idL], idL });
	setS.erase({ sum[idR], idR });
	setS.insert({ sum[idL] = calcSum(idL), idL });
	setS.insert({ sum[idR] = calcSum(idR), idR });
}

void removeG(int id) {
	auto it = G.find({ D[id].g, id });
	auto itL = it, itR = it;
	itR++;
	if (it == G.begin()) itL = G.end();
	itL--;
	if (itR == G.end()) itR = G.begin();
	int idL = itL->second, idR = itR->second;
	G.erase(it);
	setS.erase({ sum[idL], idL });
	setS.erase({ sum[idR], idR });
	setS.insert({ sum[idL] = calcSum(idL), idL });
	setS.insert({ sum[idR] = calcSum(idR), idR });
}

void removeB(int id) {
	auto it = B.find({ D[id].b, id });
	auto itL = it, itR = it;
	itR++;
	if (it == B.begin()) itL = B.end();
	itL--;
	if (itR == B.end()) itR = B.begin();
	int idL = itL->second, idR = itR->second;
	B.erase(it);
	setS.erase({ sum[idL], idL });
	setS.erase({ sum[idR], idR });
	setS.insert({ sum[idL] = calcSum(idL), idL });
	setS.insert({ sum[idR] = calcSum(idR), idR });
}

void remove(int id) {
	setS.erase(setS.begin());
	removeR(id);
	removeG(id);
	removeB(id);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int r, g, b, id;
		cin >> r >> g >> b >> id;
		id = -id;
		D[id] = { r, g, b };
		R.insert({ r, id });
		G.insert({ g, id });
		B.insert({ b, id });
	}

	for (auto it : D) {
		setS.insert({ sum[it.first] = calcSum(it.first), it.first });
	}

	for (int i = 0; i < n - 1; ++i) {
		int idD = setS.begin()->second;
		cout << -idD << "\n";
		remove(idD);
	}
	cout << -setS.begin()->second << "\n";
	return 0;
}