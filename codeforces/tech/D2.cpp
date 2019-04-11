
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <numeric>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <cmath>
#include <bitset>
#include <cassert>
#include <queue>
#include <deque>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define read(FILENAME) freopen((FILENAME + ".in").c_str(), "r", stdin)
#define write(FILENAME) freopen((FILENAME + ".out").c_str(), "w", stdout)
#define files(FILENAME) read(FILENAME), write(FILENAME)
using namespace std;
     
template <typename T1, typename T2> inline void chkmin(T1 &x, T2 y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, T2 y) {if (x < y) x = y;}
     
const string FILENAME = "input";
     
typedef pair<double, double> point;
     
const int MAXN = 1000;
     
int n;
string s[MAXN];
char let[26];
bool used[26];
bool bad[26], chk[26];
     
int main() {
    srand(time(0));
	//read(FILENAME);
    ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < 26; ++i) {
    	let[i] = ' ';
    } 
    for (int i = 0; i < n; ++i) {
    	string s;
    	cin >> s;
    	for (int j = 0; j < s.size(); ++j) {
    		if (used[s[j] - 'a']) {
    			if (j + 1 < s.size() && let[s[j] - 'a'] ==  ' ') {
    				bad[s[j + 1] - 'a'] = true;
    				let[s[j] - 'a'] = s[j + 1];
    			}
    			if (j + 1 < s.size() && let[s[j] - 'a'] != s[j + 1]) {
    				cout << "NO" << endl;
    				exit(0);
    			}
    		} else {
    			used[s[j] - 'a'] = true;
    			if (j + 1 < s.size()) {
    				bad[s[j + 1] - 'a'] = true;
    				let[s[j] - 'a'] = s[j + 1];
    			}
    		}
    	}
    }
    // for (int i = 0; i < 26; ++i) {
    // 	if (!used[i] || chk[i]) continue;
    // 	cout << char(i + 'a') << ' ' << "(" << let[i] << ")" << endl;
    // }
    for (int i = 0; i < 26; ++i) {
    	for (int j = 0; j < 26; ++j)
    		chk[j] = 0;
    	if (!used[i] || chk[i]) continue;
    	int j = i;
    	while (true) {
    		if (chk[j]) {
    			cout << "NO" << endl;
    			exit(0);
    		}
    		chk[j] = true;
    		if (let[j] == ' ') break;
    		j = let[j] - 'a';
    	}
    }
    string ans = "";
    for (int i = 0; i < 26; ++i) {
    	if (used[i] && !bad[i]) {
    		int j = i;
    		while (true) {
    			ans += 'a' + j;
    			if (let[j] ==  ' ') break;
    			j = let[j] - 'a';
    		}
    	}
    }
    cout << ans << endl;
}