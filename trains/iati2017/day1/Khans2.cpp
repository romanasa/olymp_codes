/*
ID: espr1t
TASK: Khans
KEYWORDS: Hard, Ternary Mask DP
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
FILE* in = stdin; FILE* out = stdout;

const int MAX = 10;
const int LIM = 100;
const int MASK3 = 729;

int numRows, numCols, numSteps;
int board[MAX][MAX];

int prv[MAX][MAX];
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

short dp[MAX][MAX][4][MASK3][LIM];
short go(int row, int col, int last, int rest, int step) {
    if (step == numSteps - 1)
        return board[row][col];
    short& ans = dp[row][col][last][rest][step];
    if (ans != -1)
        return ans;
    ans = -32000;

    int save = prv[row][col];
    prv[row][col] = step;
    for (int d = 0; d < 4; d++) {
        // Don't go back where we came from
        if (step > 0 && last == d)
            continue;
        int nrow = row + dir[d][0]; if (nrow < 0 || nrow >= numRows) continue;
        int ncol = col + dir[d][1]; if (ncol < 0 || ncol >= numCols) continue;
        int delay = step - prv[nrow][ncol];
        if (delay < 30 && (1 << (delay - 1)) < board[nrow][ncol])
            continue;
        int nlast = (d + 2) % 4;
        int nrest = (rest / 3) + !!step * 243 * (last < d ? last : last - 1);
        ans = max(ans, (short)(board[row][col] + go(nrow, ncol, nlast, nrest, step + 1)));
    }
    prv[row][col] = save;
    return ans;
}

int solve() {
    memset(dp, -1, sizeof(dp));
    memset(prv, -11, sizeof(prv));
    return go(0, 0, 0, 0, 0);
}

int main(void) {
    // in = fopen("Khans.in", "rt");
    
    fscanf(in, "%d %d %d", &numRows, &numCols, &numSteps);
    for (int row = 0; row < numRows; row++)
        for (int col = 0; col < numCols; col++)
            fscanf(in, "%d", &board[row][col]);
    fprintf(out, "%d\n", solve());
    return 0;
}

