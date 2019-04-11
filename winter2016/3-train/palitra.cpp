#include "hamming.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
  
using namespace std;
  
typedef long long ll;
 
const int dd = 1 << 20;
 
int dist[dd], p[dd], K;
  
void init(int k) {
    K = k;
    fill(dist, dist + dd, 31);
}
  
void add_color(int c) {
    queue<int> q;
    q.push(c);
    dist[c] = 0, p[c] = c;
    while (q.size()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < K; i++) {
            if (dist[v ^ (1 << i)] > dist[v] + 1) {
                dist[v ^ (1 << i)] = dist[v] + 1, p[v ^ (1 << i)] = c;
                q.push(v ^ (1 << i));
            }
        }
    }
}
  
int find_nearest(int c) {
    return p[c];
}