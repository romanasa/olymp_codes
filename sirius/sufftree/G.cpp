#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

/** Interface */

inline int readChar();
template <class T = int> inline T readInt(); 
template <class T> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x ); 
inline void writeWord( const char *s );

/** Read */

static const int buf_size = 4096;

inline int getChar() {
	static char buf[buf_size];
	static int len = 0, pos = 0;
	if (pos == len)
		pos = 0, len = fread(buf, 1, buf_size, stdin);
	if (pos == len)
		return -1;
	return buf[pos++];
}

inline int readChar() {
	int c = getChar();
	while (c <= 32)
		c = getChar();
	return c;
}

template <class T>
inline T readInt() {
	int s = 1, c = readChar();
	T x = 0;
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
	if (write_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
	write_buf[write_pos++] = x;
}

template <class T> 
inline void writeInt( T x, char end ) {
	if (x < 0)
		writeChar('-'), x = -x;

	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n--)
		writeChar(s[n]);
	if (end)
		writeChar(end);
}

inline void writeWord( const char *s ) {
	while (*s)
		writeChar(*s++);
}

struct Flusher {
	~Flusher() {
		if (write_pos)
			fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
	}
} flusher;


const int dd = 2e5 + 7;

string s;
map<char, int> go[dd];
int l[dd], r[dd], p[dd], suf[dd];
int nv = 2;
vector<string> e[dd];

void ask(string t, int N) {
	int v = 1, ind = 0, pos = 0;

	while (ind < t.size()) {
		if (!go[v].count(t[ind])) {
			writeWord("NO\n");
			return;
		}
		v = go[v][t[ind]];
		pos = l[v];
		while (ind < t.size() && pos < min(r[v], N)) {
			if (s[pos] != t[ind]) {
				writeWord("NO\n");
				return;
			}
			pos++, ind++;
		}
	}
	writeWord("YES\n");
}

void dfs(int v, int ind, int pos) {
	reverse(e[ind].begin(), e[ind].end());
	while (e[ind].size()) {
		ask(e[ind].back(), ind);
		e[ind].pop_back();
	}

	if (ind >= s.size())
		return;
	char c = s[ind];

	if (pos >= r[v]) {
		if (!go[v].count(c)) {

			int x = nv++;
			p[x] = v;
			l[x] = ind, r[x] = dd, go[v][c] = x;

			dfs(suf[v], ind, r[v]);
			return;
		}
		dfs(go[v][c], ind + 1, l[go[v][c]] + 1);
	} else if (c == s[pos]) {
		dfs(v, ind + 1, pos + 1);
	} else {
		int x = nv++;

		l[x] = l[v], r[x] = pos, p[x] = p[v];
		l[v] = pos, p[v] = x;

		go[p[x]][s[l[x]]] = x;
		go[x][s[pos]] = v;

		int y = nv++;

		p[y] = x, l[y] = ind, r[y] = dd;
		go[x][c] = y;

		v = suf[p[x]];
		pos = l[x];

		while (pos < r[x]) {
			v = go[v][s[pos]];
			pos += r[v] - l[v];
		}

		suf[x] = (pos == r[x] ? v : nv);

		dfs(v, ind, r[v] - (pos - r[x]));
	}
}

bool ok(char c) {
	return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

int main() {
	l[1] = -1;
	for( int i = 0; i < 127; i++)
		go[0][i] = 1;

	char t = getChar();

	while (t == 'A' || t == '?') {
		char c = getChar();

		if (t == 'A') {
			char c = getChar();
			while (ok(c))
				s += tolower(c), c = getChar();
		} else {
			char c = getChar();

			string a;

			while (ok(c))
				a += tolower(c), c = getChar();

			e[s.size()].push_back(a);
		}
		t = getChar();
	}

	dfs(1, 0, 0);

	return 0;
}