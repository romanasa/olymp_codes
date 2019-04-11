#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

const int dd = (int)1e5 + 777;

/*
int T[8 * dd];
int P[8 * dd];
int Q[8 * dd];
int W[8 * dd];
*/
struct st {
	int T, P, Q, W;
} F[8 * dd];

struct SegmentTree {

    void clear(int n) {
        //fill(T, T + 4 * n, 0);
        //fill(W, W + 4 * n, (int)1e9);
        //fill(P, P + 4 * n, 0);
        //fill(Q, Q + 4 * n, -1e9);
        for (int i = 0; i < 4 * n; i++) F[i].T = F[i].P = 0, F[i].W = (int)1e9, F[i].Q = -(int)1e9;
    }

    void push(int v) {

        if (F[v].Q >= 0) {
            F[v].T = F[v].W = F[v].Q;
            F[v].P = 0;

            F[(v << 1)].Q = F[(v << 1) + 1].Q = F[v].Q;
            F[v].Q = (int)-1e9;
        }

        if (F[v].P != 0) {
            F[v].T += F[v].P;
            F[v].W += F[v].P;

            //if (F[(v << 1)].Q == -1)
            F[(v << 1)].P += F[v].P;
            F[(v << 1)].Q += F[v].P;
            //else F[(v << 1)].Q += F[v].P;

            F[(v << 1) + 1].P += F[v].P;
            F[(v << 1) + 1].Q += F[v].P;

            F[v].P = 0;
        }
    }

    void pushL(int v) {

        if (F[v].Q >= 0) {
            F[v].T = F[v].W = F[v].Q;
            F[v].P = 0;
            F[v].Q = (int)-1e9;
        }

        if (F[v].P != 0) {
            F[v].T += F[v].P;
            F[v].W += F[v].P;
            F[v].P = 0;
        }
    }

    void build(int v, int tl, int tr, vector<int> &A) {
        if (tl == tr) {
            F[v].T = F[v].W = A[tl];
        } else {
            int tm = (tl + tr) >> 1;
            build((v << 1), tl, tm, A);
            build((v << 1) + 1, tm + 1, tr, A);
            F[v].T = max(F[(v << 1)].T, F[(v << 1) + 1].T);
            F[v].W = min(F[(v << 1)].W, F[(v << 1) + 1].W);
        }
    }

    void add(int v, int tl, int tr, int l, int r, int val) {
        if (tl == tr) pushL(v); else push(v);
        if (tl == l && tr == r) {
            F[v].P += val;
            if (tl == tr) pushL(v); else push(v);
        } else {
            int tm = (tl + tr) >> 1;
            if (r <= tm) {
                add((v << 1), tl, tm, l, r, val);
                if (tm + 1 == tr) pushL((v << 1) + 1); else push((v << 1) + 1);
            }
            else if (l > tm) {
                add((v << 1) + 1, tm + 1, tr, l, r, val);
                if (tl == tm) pushL((v << 1)); else push((v << 1));
            }
            else add((v << 1), tl, tm, l, tm, val), add((v << 1) + 1, tm + 1 , tr, tm + 1, r, val);


            //push((v << 1));
            //push((v << 1) + 1);
            F[v].T = max(F[(v << 1)].T, F[(v << 1) + 1].T);
            F[v].W = min(F[(v << 1)].W, F[(v << 1) + 1].W);
        }
    }

    void div(int v, int tl, int tr, int l, int r, int x) {

        if (tl == l && tr == r && F[v].Q >= 0) {
            F[v].Q /= x;
            F[v].T = F[v].Q;
            F[v].W = F[v].Q;
            return;
        }

        if (tl == tr) pushL(v); else push(v);

        if (tl == l && tr == r && F[v].T / x == F[v].W / x) {
            F[v].Q = F[v].T / x;
            F[v].T = F[v].Q;
            F[v].W = F[v].Q;
            return;
        }

        if (tl == tr) {
            F[v].T /= x;
            F[v].W /= x;
        } else {
            int tm = (tl + tr) >> 1;
            if (r <= tm) {
                div((v << 1), tl, tm, l, r, x);
                if (tm + 1 == tr) pushL((v << 1) + 1); else push((v << 1) + 1);
            }
            else if (l > tm) {
                div((v << 1) + 1, tm + 1, tr, l, r, x);
                if (tl == tm) pushL((v << 1)); else push((v << 1));
            }
            else div((v << 1), tl, tm, l, tm, x), div((v << 1) + 1, tm + 1 , tr, tm + 1, r, x);

            //push((v << 1));
            //push((v << 1) + 1);

            F[v].T = max(F[(v << 1)].T, F[(v << 1) + 1].T);
            F[v].W = min(F[(v << 1)].W, F[(v << 1) + 1].W);
        }
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (tl == tr) pushL(v); else push(v);;
        if (tl == l && tr == r) return F[v].T;
        int tm = (tl + tr) >> 1;
        if (r <= tm) return get((v << 1), tl, tm, l, r);
        if (l > tm) return get((v << 1) + 1, tm + 1, tr, l, r);
        return max(get((v << 1), tl, tm, l, tm), get((v << 1) + 1, tm + 1, tr, tm + 1, r));
    }

} TT;

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


int R() { return (rand() << 16) ^ rand(); }

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    for (int test = 0; test < 1; test++) {
        srand(test);
        double start = clock();
        int n, q;
        n = readInt(), q = readInt();
        //n = (int)2e3, q = (int)2e3;
        //cerr << n << " " << q << endl;

        vector<int> A(n), B(n);
        for (int i = 0; i < n; i++) {
            B[i] = A[i] = readInt();
            //A[i] = B[i] = R() % (int)150;
            //cerr << A[i] << " ";
        }
        //cerr << endl;

        TT.clear(n + 7);
        TT.build(1, 0, n - 1, A);

        while (q--) {
            int t, l, r, x;
            t = readInt(), l = readInt(), r = readInt(), x = readInt();


            //t = rand() % 3, l = rand() % n, r = rand() % n, x = 2;
            if (l > r) swap(l, r);



            //cerr << t << " " << l << " " << r << " " << x << endl;

            //err("t = %d, l = %d, r = %d\n", t, l, r);

            if (t == 0) {
                TT.add(1, 0, n - 1, l, r, x);
                //for (int i = l; i <= r; i++) B[i] += x;
            } else if (t == 1) {
                if (x != 1) TT.div(1, 0, n - 1, l, r, x);
                //for (int i = l; i <= r; i++) B[i] /= x;
            } else {
                int res1 = TT.get(1, 0, n - 1, l, r);
                /*int res2 = *max_element(B.begin() + l, B.begin() + r + 1);



                if (res1 != res2) {
                    cerr << res1 << ", expected" << res2 << endl;
                    return 0;
                }*/
                writeInt(res1, '\n');
                //cout << TT.get(1, 0, n - 1, l, r) << "\n";
            }
        }
        //cerr << (clock() - start) * 1.0 / CLOCKS_PER_SEC << "\n";
    }
    return 0;
}