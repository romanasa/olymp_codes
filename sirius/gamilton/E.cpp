#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e3 + 7;
string s;
int G[dd][dd];

int cur[dd], ind;
int A[dd], iA, B[dd], iB;
int used[dd], tmp[dd];

int main() {
	int n;
	cin >> n;
	
	getline(cin, s);
	for (int i = 0; i < n; i++) {
		getline(cin, s);
		for (int j = 0; j < i; j++) {
			if (s[j] == '0') G[j][i] = 1;
			else G[i][j] = 1;
		}
	}
	
	for (int i = 1; i < n; i++) {
		if (G[0][i]) A[iA++] = i;
		else B[iB++] = i;
	}
	
	for (int i = 0; i < iA && !ind; i++) {
		for (int j = 0; j < iB && !ind; j++) {
			if (G[A[i]][B[j]]) {
				cur[1] = 0;
				cur[0] = B[j], cur[2] = A[i];
				used[0] = 1, used[A[i]] = 1, used[B[j]] = 1;
				ind = 3;
			}
		}
	}
	
	for (int it = 0; it < n - 3; it++) {
	
      	//for (int i = 0; i < ind; i++) err("%d, ", cur[i]); err("\n");
		int ok = 0;
		
		for (int i = 0; i < n; i++) if (!used[i]) {
    		for (int j = 0; j < ind; j++) {
    			int p = j - 1;
    			if (p < 0) p += ind;
    			
    			if (G[cur[p]][i] && G[i][cur[j]]) {
    				memcpy(tmp, cur + j, sizeof(int) * (ind - j));
    				cur[j] = i;
    				memcpy(cur + j + 1, tmp, sizeof(int) * (ind - j));
    				ind++, ok = 1;
    				used[i] = 1;
    				break;
    			}
    		}
 
    		if (ok) break;
		}

		if (ok) continue;
		
		iA = 0, iB = 0;
    	for (int q = 0; q < n; q++) if (!used[q]) {
    		if (G[cur[1]][q]) A[iA++] = q;
    		else B[iB++] = q;
    	}
    	
    	for (int i = 0; i < n; i++) if (!used[i]) {
    		int ok = 0;
          	if (G[cur[1]][i]) {
        		for (int b = 0; b < iB; b++) if (G[i][B[b]]) {
        			memcpy(tmp, cur + 1, sizeof(int) * (ind - 1));
        			cur[1] = i, cur[2] = B[b];
        			memcpy(cur + 3, tmp, sizeof(int) * (ind - 1));
        			ind += 2;
        			used[i] = 1;
        			used[B[b]] = 1;
        			ok = 1;
        			break;
        		}
            } else {
      			for (int a = 0; a < iA; a++) if (G[A[a]][i]) {
      				memcpy(tmp, cur + 1, sizeof(int) * (ind - 1));
      				cur[1] = A[a], cur[2] = i;
      				memcpy(cur + 3, tmp, sizeof(int) * (ind - 1));
      				ind += 2;
      				used[i] = 1;
      				used[A[a]] = 1;
      				ok = 1;
      				break;
      			}
            }
            if (ok) break;
      	}
      	
      	//for (int i = 0; i < ind; i++) err("%d, ", cur[i]); err("\n");
	}

	for (int i = 0; i < n; i++) assert(G[cur[i]][cur[(i + 1) % n]]);	
	for (int i = 0; i < n; i++) {
		cout << cur[i] + 1 << " ";
	}
	
	return 0;
}