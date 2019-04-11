#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

#ifndef HOME
	typedef __int128 ll;
#else 
	typedef long long ll;
#endif

bool check(string &s, int st, int len) {
	for (int j = st + len; j < (int)s.size(); j += len) {
	
		for (int i = 0; i < len; i++) {
			int ci = j + i;
			int cj = j + i - len;
			
			if (ci >= (int)s.size()) continue;
			if (ci + 1 == (int)s.size()) {
				int ind = (ci - st) % len;
				int nx = (ind + 1) % len;
				
				
				char cur = s[st + ind];
				if (s[st + nx] >= '5') cur++;
				
				//err("cur = %c\n", cur);
				//err("s[ci] = %c\n", s[ci]);
				
				if (s[ci] != cur) return false;
				
			} else if (s[ci] != s[cj]) return false;
		}
	}
	return true;
}

ll get(string &s) {
	ll x = 0;
	for (char c : s) x = x * 10 + c - '0';
	return x;
}

int main() {
	int t; cin >> t;
	
	while (t--) {
		string s; cin >> s;
		
		int pos = s.find('.') + 1;
		
		int len = -1, st = -1;
		int found = 0;
		
		for (st = pos; st < pos + 10; st++) {
			for (len = 1; len <= 9; len++) {
				if (check(s, st, len)) {
					found = 1;	
					break;
				}
			}
			if (found) break;
		}
		
		assert(len != -1);
		
		//err("pos = %d, st = %d, len = %d\n", pos, st, len);
		
		string a, b;
		for (int i = pos; i < st + len; i++) a += s[i];
		for (int i = pos; i < st; i++) b += s[i];
		
		string den;
		for (int i = 0; i < len; i++) den += '9';
		for (int i = pos; i < st; i++) den += '0';
		
		ll A = get(a) - get(b);
		ll B = get(den);
		
		ll t = __gcd(A, B);
		A /= t, B /= t;
		
		assert(A < B);
		
		int C = 50;
		while (A > (ll)1e9) {
			ll ct = -1;
			ll na = -1; 
			ll nb = -1;
			for (int da = -C; da <= C; da++) {
				for (int db = -C; db <= C; db++) {
					ll t = __gcd(A + da, B + db);
					if (t > ct) {
						ct = t, na = (A + da) / t, nb = (B + db) / t;
					}
				}
			}
			if (ct == 1) break;
			A = na;
			B = nb;
		}
		
		//assert(A <= (ll)1e9);
		//assert(B <= (ll)1e9);
		
		cout << (long long)A << " " << (long long)B << "\n";
	}
	return 0;
}