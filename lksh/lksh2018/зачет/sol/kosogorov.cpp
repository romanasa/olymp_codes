#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 228;
int t[4 * N], K, a[N], out[N];

struct R {
    int l, r, id;
};

R b[N];

void update(int v, int l, int r, int i, int del) {
    if (l == r - 1)
        t[v] += del;
    else {
        int mid = (l + r) / 2;
        if (i < mid)
            update(v * 2 + 1, l, mid, i, del);
        else
            update(v * 2 + 2, mid, r, i, del);
        t[v] = t[v * 2 + 1] + t[v * 2 + 2];
    }
}

int sum(int v, int l, int r, int la, int ra) {
    if (ra <= la)
        return 0;
    if (l == la && r == ra)
        return t[v];
    int mid = (l + r) / 2;
    return sum(v * 2 + 1, l, mid, la, min(mid, ra)) + sum(v * 2 + 2, mid, r, max(mid, la), ra);
}

bool cmp(R a, R b) {
    return (a.l / K < b.l / K) || ((a.l / K == b.l / K) && a.r < b.r);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        --a[i];
    }
    cin >> m;
    K = 1337;
    int l = 0, r = 1, ans = 0;
    update(0, 0, n, a[l], 1);
    for (int i = 0; i < m; i++) {
        cin >> b[i].l >> b[i].r;
        b[i].l--;
        b[i].id = i;
    }
    sort(b, b + m, cmp);
    for (int i = 0; i < m; i++) {
    
    	if (r > b[i].r) {
    	
    		r = l - 1;
    		fill(t, t + 4 * N, 0);
    		ans = 0;
    	}
    
        while (l < b[i].l) {
            ans -= sum(0, 0, n, 0, a[l]);
            update(0, 0, n, a[l], -1);
            l++;
        }
        while (l > b[i].l) {
            l--;
            ans += sum(0, 0, n, 0, a[l]);
            update(0, 0, n, a[l], 1);
        }
        while(r < b[i].r) {
            ans += sum(0, 0, n, a[r] + 1, n);
            update(0, 0, n, a[r], 1);
            r++;
        }
        
        out[b[i].id] = ans;
    }
    for (int i = 0; i < m; i++)
        cout << out[i] << '\n';
    return 0;
}