#include <cstdio>

#define LGBOUND 17
#define BOUND (1 << LGBOUND)
#define INF int(1e9)

int n, m;
int data[LGBOUND + 1][BOUND];

void build_data(int level, int left, int right)
{
	if (!level) return;
	int middle = (left + right) / 2;
	build_data(level - 1, left, middle);
	build_data(level - 1, middle + 1, right);
	int p = left, q = middle + 1, r = left;
	while (p <= middle || q <= right)
	{
		if (p <= middle && (q == right + 1 || data[level - 1][p] < data[level - 1][q]))
			data[level][r++] = data[level - 1][p++];
		else data[level][r++] = data[level - 1][q++];
	}
}

int get(int level, int left, int right, int l, int r, int p, int q)
{
	if (l > right || r < left) return 0;
	if (l <= left && r >= right)
	{
		int x1 = left - 1, x2 = right + 1;
		while (x2 - x1 > 1)
		{
			int xm = (x1 + x2) / 2;
			if (data[level][xm] < p) x1 = xm;
			else x2 = xm;
		}
		int a1 = x2;
		x1 = left - 1, x2 = right + 1;
		while (x2 - x1 > 1)
		{
			int xm = (x1 + x2) / 2;
			if (data[level][xm] > q) x2 = xm;
			else x1 = xm;
		}
		int a2 = x1;
		if (a1 > a2) return 0;
		return a2 - a1 + 1;
	}
	int middle = (left + right) / 2;
	return get(level - 1, left, middle, l, r, p, q) + get(level - 1, middle + 1, right, l, r, p, q);
}

int main()
{
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d", &data[0][i]);
	for (int i = n; i < BOUND; i++)
		data[0][i] = INF;
	build_data(LGBOUND, 0, BOUND - 1);
	for (int i = 0; i < m; i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		a--, b--;
		printf("%d\n", get(LGBOUND, 0, BOUND - 1, a, b, c, d));
	}
	return 0;
}
