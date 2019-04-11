#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
#include "grader.h"
 
using namespace std;
 
typedef long long ll;
 
int Guess(int n, int C) {
 
    int *query = new int[n];
    ll *answers = new ll[n];
 
    for (int i = 0; i < n; i += 25) {
 
        for (int j = 0; j < n; j++)
            query[j] = 0;
 
        for (int j = 0; j < 25; j++) {
            query[i + j] = (1 << j);
        }
        StoreQuery(query);
    }
 
    int t = GetAnswers(answers);
 
    for (int i = 0; i < n; i += 25) {
 
        for (int j = 0; j < 25; j++) {
            if ((answers[i / 25] >> j) & 1)
                return i + j;
        }
    }
    return 0;
}