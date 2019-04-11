#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
#include "grader.h"
 
using namespace std;
 
typedef long long ll;
 
const int dd = (int)1e5 + 1;
 
int query[dd];
ll answers[dd];
 
int Guess(int n, int C) {
 
 
    int cnt1 = 1;
    int cnt2 = 1;
    int cnt = 10;
 
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            cnt1 = i;
            cnt2 = n / i;
        }
    }
 
    //err("%d %d\n", cnt1, cnt2);
 
    for (int i = 0; i < n; i++)
        query[i] = 0;
 
    for (int i = 0; i < n; i += cnt2 * (30 / cnt)) {
        for (int k = 0; k < 30 / cnt; k++) {
            for (int j = i + cnt2 * k; j < i + cnt2 * k + cnt2 && j < n; j++) {
                query[j] = 1 << (k * cnt);
            }
        }
 
        StoreQuery(query);
 
        for (int k = 0; k < 30 / cnt; k++) {
            for (int j = i + cnt2 * k; j < i + cnt2 * k + cnt2 && j < n; j++) {
                query[j] = 0;
            }
        }
    }
 
    GetAnswers(answers);
 
    int l = -1, r = -1;
 
    for (int i = 0, t = 0; i < n; i += cnt2 * (30 / cnt), t++) {
        for (int k = 0; k < 30; k++) {
            if ((answers[t] >> k) & 1) {
                l = i + cnt2 * (k / cnt);
                r = i + cnt2 * (k / cnt) + cnt2;
            }
        }
    }
 
    //err("l = %d, r = %d\n", l, r);
 
    r = min(r, n);
 
    for (int i = l; i < r; i += 30) {
 
        for (int j = 0; j < 30 && i + j < r; j++)
            query[i + j] = (1 << j);
        StoreQuery(query);
        for (int j = 0; j < 30 && i + j < r; j++)
            query[i + j] = 0;
    }
 
    GetAnswers(answers);
 
    for (int i = l, t = 0; i < r; i += 30, t++) {
        for (int j = 0; j < 30; j++) {
            if ((answers[t] >> j) & 1)
                return i + j;
        }
    }
    return 0;
}