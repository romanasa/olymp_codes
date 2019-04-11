#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
#include "grader.h"
 
using namespace std;
 
typedef long long ll;
 
int Guess(int n, int C) {
 
    int *query = new int[n];
    ll *answers = new ll[n];
 
    for (int i = 0; i < n; i++)
        query[i] = i;
 
    StoreQuery(query);
 
    GetAnswers(answers);
    return answers[0];
}