#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

string out(int x) {
	if (x == 0) return "{}";
	else {	
		
		string cur;
	
		vector<int> p;
		for (int i = 0; i < x; i++) p.push_back(i);
		random_shuffle(p.begin(), p.end());
		
		//cout << "{";
		cur += "{";
		for (int i = 0; i < x; i++) {
			cur += out(p[i]);
			if (i + 1 < x) cur += ",";
			else cur += "}";
		}
		return cur;
	}
}

int main(int argc, char* argv[]) {
	srand(atoi(argv[1]));
	
	string s = out(4);
	cout << "dfasfas\n";
	cout << s << "\n";
	
	return 0;
}