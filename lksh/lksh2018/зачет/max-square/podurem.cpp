#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:256000000")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <numeric>
#include <queue>
#include <cassert>

using namespace std;

typedef long long ll;

int solve();

int main() {
#ifdef PoDuReM
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	return solve();
}

inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt(T x, char end = 0);
inline void writeChar(int x);
inline void writeWord(const char *s);

/** Read */

static const int buf_size = 8192;

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

inline void writeChar(int x) {
	if (write_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
	write_buf[write_pos++] = x;
}

template <class T>
inline void writeInt(T x, char end) {
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

inline void writeWord(const char *s) {
	while (*s)
		writeChar(*s++);
}

struct Flusher {
	~Flusher() {
		if (write_pos)
			fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
	}
} flusher;

const int dd = (int)1e5 + 7;
const int C = 157;

int A[dd], L[dd];
ll ans[dd];

inline void uax(ll &a, ll b) { if (a < b) a = b; }

struct Line {
	int K;
	ll B;

	Line() {}

	Line(int _K, ll _B) { K = _K, B = _B; }

	ll operator ^ (Line I) {
		return (B - I.B) / (I.K - K) - 1;
	}
};

struct CHT {
	Line T[dd];
	ll G[dd];
	int sz, j;

	void clear() { sz = j = 0; }

	bool good(Line Q) {
		if (Q.K != T[sz - 1].K)
			return G[sz - 1] > (Q ^ T[sz - 1]);
		return Q.B > T[sz - 1].B;
	}

	void add(Line Q) {
		while (sz && good(Q))
			sz--;
		if (T[sz - 1].K != Q.K) {
			G[sz] = (sz ? (Q ^ T[sz - 1]) : -(ll)1e18);
			T[sz++] = Q;
		}
	}

	ll get(int x) {
	    if (j > sz - 1) j = sz - 1;
		while (j < sz - 1 && G[j + 1] < x) ++j;
		return 1ll * T[j].K * x + T[j].B;
	}
} J;

int SzL[dd], SzR[dd];
pair<int, int> Ql[dd], Qr[dd], Kl[dd], Kr[dd];
ll gA[dd];

int solve() {
	//(i - j) * A[i] + j * (A[j] - A[i]) = i * A[i] - 2j * A[i] + j * A[j]
	int n;
	n = readInt();
	for (int i = 0; i < n; ++i)
        A[i] = readInt();
    for (int i = 0; i < n; ++i)
        gA[i] = 1ll * (i + 1) * A[i];
	for (int i = 0; i < n; ++i)
		L[i] = i / C * C;
	int q;
	q = readInt();
	for (int i = 0; i < q; ++i) {
		int l, r;
		l = readInt() - 1, r = readInt() - 1;
		if (L[l] == L[r]) {
			J.clear();
			for (int j = l; j <= r; ++j) {
				if (J.sz) uax(ans[i], J.get(-A[j]) + gA[j]);
				J.add(Line((j + 1) << 1, gA[j]));
			}
			Kl[i] = { -1, -1 };
		} else {
			J.clear();

			int Rl = L[l] + C;
			for (int j = l; j < Rl; ++j) {
				if (J.sz) uax(ans[i], J.get(-A[j]) + gA[j]);
				J.add(Line((j + 1) << 1, gA[j]));
			}

			int Lr = L[r];
			for (int j = Lr; j <= r; ++j) {
				if (J.sz) uax(ans[i], J.get(-A[j]) + gA[j]);
				J.add(Line((j + 1) << 1, gA[j]));
			}

            SzL[Rl + 1]++;
            SzR[Lr]++;
            Kl[i] = { Rl, r };
            Kr[i] = { Lr - 1, l };
		}
	} 

	for (int i = 1; i < n; ++i)
        SzL[i] += SzL[i - 1], SzR[i] += SzR[i - 1];

    for (int i = 0; i < q; ++i) if (Kl[i].first != -1) {
        Ql[SzL[Kl[i].first]++] = { Kl[i].second, i };
        Qr[SzR[Kr[i].first]++] = { Kr[i].second, i };
    }
    for (int i = n; i > 0; --i)
        SzL[i] = SzL[i - 1], SzR[i] = SzR[i - 1];
    SzL[0] = SzR[0] = 0;

    for (int i = 0; i < n; ++i) if (SzL[i + 1] - SzL[i])
        stable_sort(Ql + SzL[i], Ql + SzL[i + 1]);
    for (int i = 0; i < n; ++i) if (SzR[i + 1] - SzR[i])
        stable_sort(Qr + SzR[i], Qr + SzR[i + 1]);

	for (int i = 0; i < n; i += C) {
		if (SzL[i + 1] - SzL[i] == 0) continue;

		J.clear();
		ll cur = 0;
		int j = SzL[i];
		for (int r = i; r < n; ++r) {
			if (J.sz) uax(cur, J.get(-A[r]) + gA[r]);
			J.add(Line((r + 1) << 1, gA[r]));
			while (j < SzL[i + 1] && Ql[j].first == r)
				uax(ans[Ql[j++].second], cur);
            if (j == SzL[i + 1]) break;
		}
	}

	//A[i] * (i + 1) + A[j] * (j + 1) - 2 * i * A[j]

	for (int i = C - 1; i < n; i += C) {
		if (SzR[i + 1] - SzR[i] == 0) continue;

		J.clear();
		ll cur = 0;
		int j = SzR[i + 1] - 1;
		for (int r = i; r >= 0; --r) {
			if (J.sz) uax(cur, J.get(-r - 1) + gA[r]);
			J.add(Line(A[r] << 1, gA[r]));
			while (j >= SzR[i] && Qr[j].first == r)
				uax(ans[Qr[j--].second], cur);
            if (j < SzR[i]) break;
		}
	}

	for (int i = 0; i < q; ++i)
        writeInt(ans[i], ' ');
	return 0;
}
