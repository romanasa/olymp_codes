#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

pair<string, int> M[31];

int main() {
M[25] = { "X.XX.X.XX.XX.X.XX.XX.X.XX", 58};
M[24] = { "X.XX.X.XX.XX.X.XX.XX.X.X", 54};
M[23] = { "X.XX.X.XX.X.XX.X.XX.X.X", 50};
M[22] = { "X.XX.X.XX.X.XX.X.XX.XX", 47};
M[21] = { "X.XX.X.XX.X.XX.X.XX.X", 45};
M[20] = { ".X..X.X..X.X..X.X..X", 41};
M[19] = { "X.XX.X.XX.X.XX.X.XX", 38};
M[18] = { "X.XX.X.XX.X.XX.X.X", 35};
M[17] = { "X.XX.X.XX.X.XX.XX", 32};
M[16] = { "X.XX.X.XX.X.XX.X", 30};
M[15] = { "X.XX.XX.XX.XX.X", 26};
M[14] = { "X.XX.X.XX.X.XX", 23};
M[13] = { "X.XX.XX.XX.XX", 21};
M[12] = { "X.XX.XX.XX.X", 19};
M[11] = { ".X..X..X..X", 16};
M[10] = { "X.XX.XX.XX", 14};
M[9] = { "X.XX.XX.X", 12};
M[8] = { ".X..X..X", 9};
M[7] = { "X.XX.XX", 7};
M[6] = { "XXXXXX", 5};
M[5] = { "XXXXX", 4};
M[4] = { "XXXX", 3};
M[3] = { "XXX", 2};
M[2] = { "XX", 1};
M[1] = { "X", 0};
	int n;
	cin >> n;
	cout << M[n].first << "\n" << M[n].second << "\n";

	return 0;
}