#include "grader.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>
#include <random>
#include <ctime>
 
using namespace std;
 
typedef long long ll;
 
int n, k;
 
void Init(int _n, int _k) {
    n = _n, k = _k;
}
 
double Q[] = { 0, 1, 2.6, 3, -1, 4, -1, -1, -1, -1, 5.5 };
 
int Guess() {
 
    if (k == 1) {
        int l = 1, r = n;
        while (r != l) {
            int m = (l + r + 1) / 2;
            if (Ask(m) == 0)
                r = m - 1;
            else
                l = m;
        }
        return l;
    }
 
    int l = 1, r = n;
    int pos = 0;
 
    vector<pair<int, int> > T;
 
    while (l != r) {
 
        int m = l + (r - l) * 1.0 / Q[k];
        m = max(m, l + 1);
        m = min(m, r);
 
        int x = Ask(m);
        T.push_back({ l, m - 1 });
 
        if ((int)T.size() - pos >= k && x == 0) {
            int ind = (int)T.size() - k;
            l = T[ind].first;
            r = T[ind].second;
            pos = (int)T.size();
        } else {
            l = m;
        }
 
    }
 
    int q = (int)T.size();
 
    for (int i = 0; i < k; i++) {
 
        int x = Ask(1);
        T.push_back({ -1, -1 });
 
        if ((int)T.size() - pos >= k && x == 0) {
            int ind = (int)T.size() - k;
            l = T[ind].first;
            r = T[ind].second;
            pos = (int)T.size();
            break;
        }
    }
 
    return l;
}