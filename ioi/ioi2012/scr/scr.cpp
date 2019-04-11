#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
#include "grader.h"
using namespace std;

typedef long long ll;

const int dd = (int)1e6 + 7;

int nv = 1;
int P[dd], len[dd], G[dd];
char C[dd];

int up[21][dd];

void Init() {
}

void TypeLetter(char L) {
    int cur = nv++;

    P[cur] = cur - 1;
    C[cur] = L;
    len[cur] = len[cur - 1] + 1;
    G[cur] = cur;


    up[0][cur] = G[P[cur]];
    for (int i = 1; i <= 20; i++) {
        up[i][cur] = up[i - 1][up[i - 1][cur]];
    }
}

void UndoCommands(int U) {
    int cur = nv++;
    int ind = cur - U - 1;
    P[cur] = ind;
    C[cur] = '#';
    len[cur] = len[ind];
    G[cur] = G[P[cur]];

    up[0][cur] = G[P[cur]];
    for (int i = 1; i <= 20; i++) {
        up[i][cur] = up[i - 1][up[i - 1][cur]];
    }
}

char GetLetter(int i) {
    int cur = nv - 1;
    int c = len[cur] - i;
    char ans = '#';

    if (C[cur] == '#')
        cur = G[cur];

    for (int i = 20; i >= 0; i--) {
        if ((c - (1 << i)) >= 1) {
            c -= (1 << i);
            cur = up[i][cur];
        }
    }

    return C[cur];
}