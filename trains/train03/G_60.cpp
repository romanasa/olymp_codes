#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int inf = (int)1e9 + 1;

int A[607][607];

int dist[17][17];
int dp[1 << 17][17];
pair<int, int> p[1 << 17][17];

int get(int i1, int j1, int i2, int j2) {
	int sum = 0;
	for (int i = i1; i <= i2; i++)
		for (int j = j1; j <= j2; j++)
			sum += A[i][j];
	return sum;
}

int main() {
	int q;
	scanf("%d", &q);
	//q = 1;
	while (q--) {
		int h, w, k;
		scanf("%d %d %d", &h, &w, &k);
		
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				scanf("%d", &A[i][j]);

		int c1 = 5;
		int c2 = 4;
		int c3 = 2;
		
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				dist[i][j] = 0;
				if (i == j) continue;
				
				for (int q = c1; q + c1 < w; q++) {
				
					int t1 = (i + 1) * (h / k) - 1;
					int t2 = j * (h / k);
					
					dist[i][j] += abs(get(t1 - c2, q - c3, t1, q + c3) - get(t2, q - c3, t2 + c2, q + c3));
				}				
			}
		}
		
		for (int msk = 0; msk < (1 << k); msk++) {
			fill(dp[msk], dp[msk] + k, inf);
			fill(p[msk], p[msk] + k, make_pair(-1, -1));
		}
			
		for (int i = 0; i < k; i++)
			dp[1 << i][i] = 0;
			
		/*for (int i = 0; i < k; i++)
			for (int j = 0; j < k; j++)
				cout << dist[i][j] << " \n"[j == k - 1];
		*/	
		for (int msk = 0; msk < (1 << k); msk++) {
			for (int v = 0; v < k; v++) if (dp[msk][v] != inf) {
				for (int to = 0; to < k; to++) if (!((msk >> to) & 1)) {
					if (dp[msk | (1 << to)][to] > dp[msk][v] + dist[v][to]) {
						dp[msk | (1 << to)][to] = dp[msk][v] + dist[v][to];
						p[msk | (1 << to)][to] = { v, to };
					}
				}
			}
		}
		
		/*for (int msk = 0; msk < (1 << k); msk++)
			for (int v = 0; v < k; v++)
				cout << dp[msk][v] << " \n"[v == k - 1];
		cout << "\n\n";
		for (int msk = 0; msk < (1 << k); msk++)
			for (int v = 0; v < k; v++)
				printf("(%d, %d)%c", p[msk][v].first, p[msk][v].second, " \n"[v == k - 1]);
		*/
				
		int i = (1 << k) - 1, j = min_element(dp[(1 << k) - 1], dp[(1 << k) - 1] + k) - dp[(1 << k) - 1];
		//printf("%d %d\n", i, j);
		vector<int> ans, res(k);
		while (j != -1) {
			ans.push_back(j);
			int v = p[i][j].first, to = p[i][j].second;
			i ^= (1 << to), j = v;
		}
		reverse(ans.begin(), ans.end());
		for (int i = 0; i < (int)ans.size(); i++)
			res[ans[i]] = i;
		for (int x : res)
			printf("%d ", x + 1);
		printf("\n");
	}
	return 0;
}