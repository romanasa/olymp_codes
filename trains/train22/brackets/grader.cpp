#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grader.h"
#define SECRET "user"
#define N 500000
#define M 500000

static int is_run = 0;
static int n, m, l[N], r[N], sl, sr, result[N];

int main (void) {
    int i;
    if (is_run) {
        printf("%s SV recursive call of main\n", SECRET);
        exit(-1);
    }
    is_run = 1;

    printf("%s\n", SECRET);
    assert(scanf("%d", &n) == 1);
    for (i = 0; i < n; ++i)
        assert(scanf("%d%d", &l[i], &r[i]) == 2);
    init(n, l, r);
    
    assert(scanf("%d", &m) == 1);
    for (i = 0; i < m; ++i) {
        assert(scanf("%d%d", &sl, &sr) == 2);
        result[i] = get(sl, sr);
    }
    for (i = 0; i < m; ++i)
        printf("%d\n", result[i]);
    
    is_run = 0;
    return 0;
}
