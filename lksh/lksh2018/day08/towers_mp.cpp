#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

#define begin dfasfadsf

const int N = 1 << 17;
const int A = 100 + 2;
int n, total, c[N], suf[N], new_c[N], new_suf[N], begin[N], where[N], s[N], pos, x, real_n;
long long res;

int safe(int x) {
	return x >= n ? x - n : x;
}

void build() {
	memset(begin, 0, sizeof(begin));
	for (int i = 0; i < n; ++i) {
		c[i] = s[i];
		begin[c[i] + 1]++;
		suf[i] = i;
	}
	for (int i = 0; i + 1 < A; ++i)
		begin[i + 1] += begin[i];
	for (int l = 0; l < n; l = (l ? l * 2 : 1)) {
		for (int i = 0; i < n; ++i) {
			pos = safe(suf[i] - l + n);
			new_suf[begin[c[pos]]++] = pos;
		}
		total = 0;
		for (int i = 0; i < n; ++i) {
			if ((i == 0) || (c[new_suf[i - 1]] != c[new_suf[i]]) || (c[safe(new_suf[i - 1] + l)] != c[safe(new_suf[i] + l)]))
				begin[total++] = i;
			new_c[new_suf[i]] = total - 1;
		}
		memcpy(suf, new_suf, n * sizeof(suf[0]));
		memcpy(c, new_c, n * sizeof(c[0]));
	}
}

int main() {
	freopen("towers.in", "r", stdin);
	freopen("towers.out", "w", stdout);
	while ((scanf("%d", &n) == 1) && (n > 0)) {
		for (int i = 0; i < n; ++i)
			scanf("%d", &s[i]), s[i]++, s[n + i] = s[i];
		s[2 * n] = 0, real_n = n, n = 2 * n + 1;
		build();
		for (int i = 0; i < n; ++i)
			where[suf[i]] = i;	
		res = 0;
		for (int i = 0; i < n; ++i)
			if (where[i] == n - 1)
				x = 0;
			else {
				while ((x < real_n) && (s[i + x] == s[suf[where[i] + 1] + x]))
					++x;
				if (i < real_n)
					res += x;
				x = max(0, x - 1);
			}
		cout << res << endl;
		// printf("%lld\n", res);
	}
	return 0;
}
