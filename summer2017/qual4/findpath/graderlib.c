#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "findpath.h"

static int n, m, maxq;
static int qmade;
static int* len;
static int** edges;
static int* u;
static int* v;
static int* p;
static int* q;
static int* a;
static int* myqueue;
static int* dist;
static int* used;
static int ql, qr;

static void readTest()
{
    scanf("%d%d%d", &n, &m, &maxq);    

    len = (int*) malloc(sizeof(int) * n);
    edges = (int**) malloc(sizeof(int*) * n);    
    u = (int*) malloc(sizeof(int) * m);
    v = (int*) malloc(sizeof(int) * m);
    myqueue = (int*) malloc(sizeof(int) * n);
    dist = (int*) malloc(sizeof(int) * n);
    used = (int*) malloc(sizeof(int) * n);
    p = (int*) calloc(sizeof(int), n);
    q = (int*) calloc(sizeof(int), n);
    a = (int*) calloc(sizeof(int), n);

    for (int i = 0; i < m; i++) {
    	scanf("%d%d", &u[i], &v[i]);
    	u[i]--;
    	v[i]--;

    	len[u[i]]++;
    	len[v[i]]++;
    }

    for (int i = 0; i < n; i++) {
    	edges[i] = (int*) malloc(sizeof(int) * len[i]);
    	len[i] = 0;
    }

    for (int i = 0; i < m; i++) {
    	edges[u[i]][len[u[i]]] = v[i];
    	edges[v[i]][len[v[i]]] = u[i];
    	len[u[i]]++;
    	len[v[i]]++;
    }
}

static void finishWrong(const char* comment) {
	printf("-1\n%s\n", comment);

	exit(0);
}

static void checkPath(int pathlen) {
   	if (pathlen < 2 || pathlen > n) {
		finishWrong("Incorrect path length");
	}
	if (p[0] != 0) {
		finishWrong("Starting vertex should be 0");
	}
	if (p[pathlen - 1] != n - 1) {
		finishWrong("Finish vertex should be n - 1");
	}

	for (int i = 0; i < n; i++)
		used[i] = 0;
	for (int i = 0; i < pathlen; i++) {
		if (p[i] < 0 || p[i] >= n) {
			finishWrong("Incorrect vertex index");
		}
		if (used[p[i]]) {
			finishWrong("Vertex visited twice");
		}
		used[p[i]] = 1;
	}

	for (int i = 0; i < pathlen - 1; i++) {
		int flag = 0;
		for (int j = 0; j < len[p[i]]; j++) {
			if (edges[p[i]][j] == p[i + 1])
				flag = 1;
		}

		if (!flag) {
			finishWrong("Some edges are missing");
		}
	}
}

static void bfs() {
	while (ql < qr) {
		int cur = myqueue[ql];
		ql++;
		for (int i = 0; i < len[cur]; i++) {
			int tg = edges[cur][i];
			if (dist[tg] == n + 1) {
				dist[tg] = dist[cur] + 1;
				myqueue[qr] = tg;
				qr++;
			}
		}
	}
}

void ask(int k) {
	qmade++;
	if (qmade > maxq) {
		finishWrong("Too many question, viscount");
	}

    if (k < 0) {
        finishWrong("negative k is prohibited");
    }

	int cnt = 0;
	ql = 0;
	qr = 0;
	for (int i = 0; i < n; i++) {
		if (q[i] == 0) {
			dist[i] = n + 1;
			continue;
		}
		if (q[i] == 1) {
			dist[i] = 0;
			myqueue[qr] = i;
			qr++;
			cnt++;
			continue;		
		}

		finishWrong("Incorrect value in array q");
	}

	if (cnt == 0) {
		finishWrong("Empty interesting set");
	}

	bfs();

	for (int i = 0; i < n; i++) {
		if (dist[i] <= k)
			a[i] = 1;
		else
			a[i] = 0;
	}
}

int _main(int (*solve)(int, int*, int *, int *))
{
	readTest();
	int pathlen = solve(n, p, q, a);

	checkPath(pathlen);

	printf("%d\n", pathlen);
	printf("%d\n", qmade);

    return 0;
}

