#include <bits/stdc++.h>
#define ll long long
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
using namespace std;

int main() {
	int n, t;
	cin >> n >> t;
	
	string S;
	cin >> S;
	
	int ind = 0;
	for (int i = 0; i < n; i++)
		if (S[i] == '.')
			ind = i;

	vector<int> T(1, 0);	
	
	for (int i = ind + 1; i < n; i++) {
		T.push_back(S[i] - '0');
		
		if (T.back() >= 5) {
			while ((int)T.size() > i + 1)
				T.pop_back();
			T.pop_back();
			
			T.back()++;
			
			if (T.size() > 1) {
				int j = (int)T.size();
				T[j - 2] += T[j - 1] / 10;
				T[j - 1] %= 10;
			}
			
			t--;
			break;
		}
	}
	
	//err("T: "); for (int i : T) err("%d, ", i); err("\n");
	
	while (t > 0 && T.size() > 1 && T.back() >= 5) {
		t--;
		T.pop_back();
		T.back()++;
		
		if (T.size() > 1) {
			int j = (int)T.size();
			T[j - 2] += T[j - 1] / 10;
			T[j - 1] %= 10;
		}
		
		if (T.size() > 1 && T.back() == 0)
			T.pop_back();
	}
	
	vector<int> ans;
	for (int i = 0; i < ind; i++)
		ans.push_back(S[i] - '0');

	ans.back() += T[0];	
	
	
	//err("ans: "); for (int i : ans) err("%d, ", i); err("\n");
	
	for (int i = (int)ans.size() - 1; i >= 0; i--) {
		if (ans[i] > 9) {
			if (i > 0) {
				ans[i - 1] += ans[i] / 10;
				ans[i] %= 10;
			} else {
				int t = ans[i] / 10;
				ans[i] %= 10;
				ans.insert(ans.begin(), t);
			}
		}
	}
	
	
	//err("ans: "); for (int i : ans) err("%d, ", i); err("\n");
	
	for (int i : ans)
		cout << i;
	
	if (T.size() > 1) {
		cout << ".";
		for (int i = 1; i < (int)T.size(); i++)
			cout << T[i];
	}
	
	return 0;
}