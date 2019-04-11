#include <bits/stdc++.h>

using namespace std;

int main() {
	long long x;
	cin >> x;
	vector<int> a;
	for (int i = 31; i >= 0; i--) {
		a.push_back((x & (1ll << i)) > 0);
	}                           

	for (int i = 0; i < a.size(); i++) {
		cout << a[i];                   
		if (i % 8 == 7)
			cout << " ";
	}
	cout << "\n";

	for (int i = 0; i < 4; i++) {       
		int s = 0;
		int c = 8;
		for (int j = 8 * i; j < 8 * i + 4; j++)
			s += a[j] * c, c /= 2;

		if (s < 10)
			cout << s;
		else
			cout << (char)(10 - s + 'A');
		
		s = 0, c = 8;
		for (int j = 8 * i + 4; j < 8 * i + 8; j++)
			s += a[j] * c, c /= 2;

		if (s < 10)
			cout << s;
		else
			cout << (char)(10 - s + 'A');
		cout << " ";
	}

	return 0;
}