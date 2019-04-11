#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
#include "grader.h"
 
using namespace std;
 
typedef long long ll;
 
int Guess(int n, int C) {
 
    int *query = new int[n];
    ll *answers = new ll[n];
 
    for (int i = 0; i < n; i++)
        query[i] = 0;
 
    srand(1488);
 
    int ind = rand() % n;
 
    query[ind] = 1;
 
    StoreQuery(query);
    GetAnswers(answers);
 
    if (answers[0] > 0) {
        return ind;
    }
    int t = rand() % n;
 
    return t;
}