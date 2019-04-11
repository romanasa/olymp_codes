#include <cstdio>
#include "twosequences.h"

int main()
{
	freopen("twosequences.in", "r", stdin);
	//freopen("twosequences.out", "w", stdout);

	int n;
	scanf("%d", &n);
	int *a = new int[n];
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
	}

	printf("%d\n", countSequences(n, a));
}