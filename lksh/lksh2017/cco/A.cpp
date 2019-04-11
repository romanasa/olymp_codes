#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

vector<pair<int, int> > ans;
int nv;

void go(int k, int num) {
	if (k == 0) return;
	
	if (num > 1) {
		ans.push_back({ num - 1, num });
	}
	
	int x = 1;
	while (x * (x - 1) / 2 <= k) x++;
	x--;
	
	nv = num + x - 1;
	
	for (int i = 0; i < x; i++) {
		if (i + 1 < x) 
			ans.push_back({ num + i, num + i + 1 });
		else 
			ans.push_back({ num + i, num });
	}
	go(k - x * (x - 1) / 2, num + x);
}

int main() {
	int k;
	scanf("%d", &k);
	go(k, 1);
	printf("%d %d\n", nv, (int)ans.size());
	for (auto c : ans) printf("%d %d\n", c.first, c.second);
	return 0;
}