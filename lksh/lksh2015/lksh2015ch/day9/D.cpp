#include <iostream>
#include <bitset>

using namespace std;

bitset<50000007> a;

int main() {
	int a, b;
	cin >> a >> b;
	for (int i = 2; i <= b; i++)
		a[i] = 1;
		
	for (int i = 2; i * i <= b; i++) {
		for (int j = i; j <= b; j += i)
			a[j] = 0;
	}
	int ans = 0;
	for (int i = a; i <= b; i++)
		ans += a[i];
	cout << ans;
}
