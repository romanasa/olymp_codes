#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
#include "grader.h"
 
using namespace std;
 
typedef long long ll;
 
int Guess(int n, int C) {
 
    int *query = new int[n];
    ll *answers = new ll[n];
 
    int l = 0, r = n - 1;
 
    while (l != r) {
        int m = (l + r) / 2;
 
        for (int j = 0; j < n; j++)
            query[j] = 0;
 
        for (int j = l; j <= m; j++)
            query[j] = 1;
 
        StoreQuery(query);
        int t = GetAnswers(answers);
 
        if (answers[0] > 0) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}