#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

int A[543][543];
int B[543][543];
int pos[543 * 543];
int dx[543], cnt[543 * 543], G[543];

void no() {
	cout << "-1\n";
	exit(0);
}

int main() {
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> A[i][j];
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> B[i][j];
	
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
		pos[B[i][j]] = i * n + j;
		
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
		A[i][j] = pos[A[i][j]];
		
	/*for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			err("%d%c", A[i][j], " \n"[j == n - 1]);
	*/	
	
	for (int i = 0; i + 1 < n; i++) dx[i] = A[0][i + 1] - A[0][i];
	
	for (int i = 0; i < n; i++) {
		int l = *min_element(A[i], A[i] + n);
		int r = *max_element(A[i], A[i] + n);
		
		//err("i = %d, l = %d, r = %d\n", i, l, r);
		
		if (l % n) no();
		if (l + n - 1 != r) no();
		if (cnt[l]++) no();
		G[i] = l;
	
		
		for (int j = 0; j + 1 < n; j++) 
			if (A[i][j + 1] - A[i][j] != dx[j]) no();
	}
	
	vector<pair<int, int> > Q, W;
	
	for (int i = 0; i < n; i++) {
		int ind = i;
		for (int j = i; j < n; j++) if (A[0][j] < A[0][ind])
			ind = j;
			
		if (ind > i) Q.push_back({ i, ind });
		swap(A[0][i], A[0][ind]);
	}
	
	
	for (int i = 0; i < n; i++) {
		int ind = i;
		for (int j = i; j < n; j++) if (G[j] < G[ind])
			ind = j;
		
		if (ind > i) W.push_back({ i, ind });
		swap(G[i], G[ind]);
	}
	
	cout << (int)Q.size() + (int)W.size() << "\n";
	for (auto c : Q) cout << "2 " << c.first + 1 << " " << c.second + 1 << "\n";
	for (auto c : W) cout << "1 " << c.first + 1 << " " << c.second + 1 << "\n";
	
	return 0;
}