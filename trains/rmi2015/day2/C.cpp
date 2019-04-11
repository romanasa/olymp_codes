#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
  
using namespace std;
  
typedef long long ll;
  
const int M = (int)33e6 + 5;
const int N = (int)3e6 + 5;
  
char s[M];
char ans[N];
int cnt[127], need[127];
  
#define TASK "password"
  
int main() {
#ifndef HOME
    freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
    gets(s);
      
    int i = 0;
    for (; s[i] != ' '; i++) cnt[s[i]]++;
    for (i++; s[i]; i++) cnt[s[i]]--, need[s[i]]++;
      
    for (int i = 0; i < 127; i++) if (cnt[i] < 0) return 0 * puts("impossible");
      
    int ind = 0;
    for (int i = 0; s[i] != ' '; i++) {
        if (need[s[i]]) {
            while (ind && cnt[ans[ind - 1]] && s[i] < ans[ind - 1]) {
                need[ans[ind - 1]]++;
                cnt[ans[ind - 1]]--;
                ind--;
            }
            ans[ind++] = s[i];
            need[s[i]]--;
        } else {
            cnt[s[i]]--;
        }
    }
    cout << ans;
    return 0;
}

