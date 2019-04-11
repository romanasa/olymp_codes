#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

string s, t;
	
vector<int> G;
int len;
	
void out() {
	cout << "+";
	for (int j = 0; j < len; j++) {
		for (int i = 0; i < G[j] + 2; i++) cout << "-";
		cout << "+";
	}
	cout << "\n";	
}

void out2(vector<string> Q) {
	cout << "|";
	int ind = 0;
	
	for (auto c : Q) {	
		int l1 = 0, r1 = 0;
		
		if (s[ind] == 'l') {
			l1 = 1;
			r1 = G[ind] + 2 - (int)c.size() - l1;
		} else if (s[ind] == 'r') {
			r1 = 1;
			l1 = G[ind] + 2 - (int)c.size() - r1;
		} else {
			l1 = (G[ind] + 2 - (int)c.size()) / 2;
			r1 = (G[ind] + 2 - (int)c.size() - l1);
		}
		
		for (int i = 0; i < l1; i++) cout << " ";
		cout << c;
		for (int i = 0; i < r1; i++) cout << " ";
		cout << "|";
	}
	cout << "\n";
}

int main() {
	cin >> s;
	len = (int)s.size();
	getline(cin, t);
	
	vector<vector<string> > T;
	
	while (getline(cin, t)) {
		//cout << t << "\n";
		
		T.push_back(vector<string>(0));
		
		string cur;
		for (char c : t) {
			if (c == '&') {
				T.back().push_back(cur);
				cur = "";
			} else {
				cur += c;
			}
		}
		T.back().push_back(cur);
	}
	
	G.resize(len);
	for (auto c : T) {
		for (int i = 0; i < len; i++) {
			G[i] = max(G[i], (int)c[i].size());
		}
	} 
	
	out();
	out2(T[0]);
	out();
	for (int i = 1; i < (int)T.size(); i++) out2(T[i]);
	out();
	return 0;
}