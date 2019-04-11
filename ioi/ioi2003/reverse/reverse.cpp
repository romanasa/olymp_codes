#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;

using namespace std;

int f(vector<int> &A, int x) {
    for (int i = 0; i < (int)A.size(); i++)
        if (A[i]== x) return i;
    return -1;
}

int main() {
    int k, n;
    cin >> k >> n;

    cout << "FILE reverse " << k << "\n";

    if (1 <= k && k <= 2) {
        for (int i = 0; i < 9; i++) cout << i << " ";
        cout << "\n";
        for (int i = n + 1; i > 0; i--) {
            cout << "P " << i << "\n";
        }
        return 0;
    }

    if (3 <= k && k <= 7) {
        int s = 0;

        vector<int> A(9);

        for (int i = 1; i <= 9; i++) {
            cout << max(n - s, 0) << " ";
            A[i - 1] = max(n - s, 0);
            s += (i + 1);
        }
        cout << "\n";

        s = 0;
        int x = n;
        for (int it = 1; it <= 9; it++) {

            s += (it + 1);
            int cur = n - s;

            for (int q = 0; q < it; q++) {

                int ind = f(A, x);
                int pos = f(A, cur);

                cout << "P " << ind + 1 << "\n";
                x--;

                if (x < 0) return 0;

                if (pos != -1) {
                    cout << "S " << pos + 1 << " " << ind + 1 << "\n";
                    A[ind] = A[pos] + 1;
                }

                cur++;
            }
        }
    }

    int t = (n + 7) / 8;

    vector<int> A(9);

    for (int i = 0; i < 8; i++) {
        A[i + 1] = t * (7 - i);
    }

    for (int i = 0; i < 9; i++) cout << A[i] << " ";
    cout << "\n";

    for (int i = n; i >= 0; i--) {
		int ok = 0;
    	for (int j = 0; j < 9; j++) {
  			if (i == A[j]) {
  				ok = 1;
  				cout << "P " << j + 1 << "\n";
  				break;
  			}
      	}
      	
      	if (ok) continue;
    
        for (int j = 1; j < 9; j++) {
            if (i > A[j]) {
                int x = A[j] + 1;
                cout << "S " << j + 1 << " 1\n";
                A[0] = x;
                while (x < i) {
                    cout << "S 1 1\n";
                    x++;
                }
                A[0] = i;
                cout << "P 1\n";
                break;
            }
        }
    }

    return 0;
}