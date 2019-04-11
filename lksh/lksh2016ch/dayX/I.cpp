#include <bits/stdc++.h>

using namespace std;

struct matrix {
	vector<vector<int> > T(4, vector<int>(4, 0));
	
	matrix operator * (matrix B) {
		vector<vector<int> > A(4, vector<int>(4, 0));
		for (int k = 0; k < 4; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					A[i][j] = (A[i][j] + B[i][k] * B[k][j]) % 2;
		return { A };
	}
} A, B;

int main() {
	


	return 0;
}
