#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
 
using namespace std;
 
typedef long long ll;
 
const int dd = 207;
int P[dd][dd], C[dd][dd];
struct pt {int x, y; } A[dd];
 
inline int get(int x1, int y1, int x2, int y2) {
    return P[x2][y2] - (x1 ? P[x1 - 1][y2] : 0) - (y1 ? P[x2][y1 - 1] : 0) + (x1 && y1 ? P[x1 - 1][y1 - 1] : 0);
}
 
vector<pair<int, int> > ans;
 
void add(int x1, int y1, int x2, int y2) {
    for (int x = x1; x <= x2; x++)
        for (int y = y1; y <= y2; y++) {
            if (C[x][y] == 0) {
                ans.push_back({ x, y });
            }
        }
}
 
int main() {
 
    int t;
    scanf("%d", &t);
 
    while (t--) {
        int n;
        scanf("%d", &n);
 
        int mx = (int)1e9 + 1, my = (int)1e9 + 1;
 
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &A[i].x, &A[i].y);
            mx = min(mx, A[i].x);
            my = min(my, A[i].y);
        }
 
        mx--, my--;
 
        for (int i = 0; i < n; i++) {
            A[i].x -= mx;
            A[i].y -= my;
            C[A[i].x][A[i].y]++;
            //err("(%d, %d), ", A[i].x, A[i].y);
        }
        //err("\n");
 
        for (int i = 0; i < n + 3; i++) {
            for (int j = 0; j < n + 3; j++) {
                P[i][j] = (i ? P[i - 1][j] : 0) + (j ? P[i][j - 1] : 0) - (i && j ? P[i - 1][j - 1] : 0) + (C[i][j] == 0);
            }
        }
 
        int cur = (int)1e9;
        int a = -1, b = -1, c = -1, d = -1;
 
        for (int x1 = 0; x1 < n + 3; x1++) {
            for (int y1 = 0; y1 < n + 3; y1++) {
                for (int x2 = x1 + 2; x2 < n + 3; x2++) {
                    for (int y2 = y1 + 2; y2 < n + 3; y2++) {
 
                        if (get(x1 + 1, y1 + 1, x2 - 1, y2 - 1) == 0) continue;
 
                        int ans1 = get(x1, y1, x2, y1);
                        int ans2 = get(x1, y1 + 1, x1, y2);
                        int ans3 = get(x1 + 1, y2, x2, y2);
                        int ans4 = get(x2, y1 + 1, x2, y2 - 1);
 
                        int ans = ans1 + ans2 + ans3 + ans4;
 
                        if (ans == 2 * (x2 - x1) + 2 * (y2 - y1)) continue;
 
                        if (C[x1][y1] == 0 || C[x1][y2] == 0 || C[x2][y1] == 0 || C[x2][y1] == 0)
                            ans--;
 
                        //err("(%d, %d, %d, %d) = %d\n", x1, y1, x2, y2, ans);
 
                        if (cur > ans) {
                            cur = ans;
                            a = x1, b = y1, c = x2, d = y2;
                        }
                    }
                }
            }
        }
 
 
        printf("%d\n", cur);
        //err("(%d, %d, %d, %d)\n", a, b, c, d);
 
        //int t = 1;
 
        ans.clear();
 
        int x1 = a, y1 = b, x2 = c, y2 = d;
 
        add(x1, y1, x2, y1);
        add(x1, y1 + 1, x1, y2);
        add(x1 + 1, y2, x2, y2);
        add(x2, y1 + 1, x2, y2 - 1);
 
        /*if ((int)ans.size() < cur) {
            assert(n != 3);
        }*/
 
        for (int i = 0; i < (int)ans.size();i++) {
            if (ans[i] == make_pair( a, b ) || ans[i] == make_pair( a, d ) || ans[i] == make_pair( c, b ) || ans[i] == make_pair( c, d )) {
                //err("%d\n", i);
                ans.erase(ans.begin() + i);
                break;
            }
        }
 
        //if ((int)ans.size() < cur) assert(0);
 
        //assert((int)ans.size() == cur);
 
        for (int i = 0; i < (int)ans.size(); i++)
            printf("%d %d\n", ans[i].first + mx, ans[i].second + my);
 
        //cout << cur << "\n";
        for (int i = 0; i < n + 7; i++) {
            fill(P[i], P[i] + n + 7, 0);
            fill(C[i], C[i] + n + 7, 0);
        }
 
    }
 
    return 0;
}