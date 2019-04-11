#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:66777216")
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>
#include <cstring>
#include <sstream>
#include <numeric>
#include <unordered_set>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fornn(i, q, n) for (int i = q; i < (ll)n; i++)
#define mp make_pair
#define pk push_back
#define all(v) v.begin(), v.end()
#define times clock() * 1.0 / CLOCKS_PER_SEC

#define TASK "king"

const double eps = 1e-7;
const double pi = acos(-1.0);

const ll INF = (ll)2e9 + 1;
const ll LINF = (ll)8e18;
const ll inf = (ll)2e9 + 1;
const ll linf = (ll)2e18;
const ll MM = (ll)1e9 + 7;

int solve();
void gen();

int main()
{
#ifdef _DEBUG
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	//freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout), freopen("test.txt", "w", stderr);
#endif
	solve();
	return 0;
}


unsigned long long abs(unsigned long long n)
{
	return n;
}

//! ���������� true, ���� n ������
template <class T>
bool even(const T & n)
{
	// return n % 2 == 0;
	return (n & 1) == 0;
}

//! ����� ����� �� 2
template <class T>
void bisect(T & n)
{
	// n /= 2;
	n >>= 1;
}

//! �������� ����� �� 2
template <class T>
void redouble(T & n)
{
	// n *= 2;
	n <<= 1;
}

//! ���������� true, ���� n - ������ ������� �������� �����
template <class T>
bool perfect_square(const T & n)
{
	T sq = (T)ceil(sqrt((double)n));
	return sq*sq == n;
}

//! ��������� ������ �� �����, �������� ��� ����
template <class T>
T sq_root(const T & n)
{
	return (T)floor(sqrt((double)n));
}

//! ���������� ���������� ��� � ����� (�.�. ����������� ���������� ���, �������� ����� ����������� ������ �����)
template <class T>
unsigned bits_in_number(T n)
{
	if (n == 0)
		return 1;
	unsigned result = 0;
	while (n)
	{
		bisect(n);
		++result;
	}
	return result;
}

//! ���������� �������� k-�� ���� ����� (���� ���������� � ����)
template <class T>
bool test_bit(const T & n, unsigned k)
{
	return (n & (T(1) << k)) != 0;
}

//! �������� a *= b (mod n)
template <class T>
void mulmod(T & a, T b, const T & n)
{
	// ������� ������, ������� ������ ��� ������� ����������
	a *= b;
	a %= n;
}

template <>
void mulmod(int & a, int b, const int & n)
{
	a = int((((long long)a) * b) % n);
}

template <>
void mulmod(unsigned & a, unsigned b, const unsigned & n)
{
	a = unsigned((((unsigned long long)a) * b) % n);
}

template <>
void mulmod(unsigned long long & a, unsigned long long b, const unsigned long long & n)
{
	// ������� ������, ���������� �� �������� ���������� ������������ � �����
	if (a >= n)
		a %= n;
	if (b >= n)
		b %= n;
	unsigned long long res = 0;
	while (b)
		if (!even(b))
		{
			res += a;
			while (res >= n)
				res -= n;
			--b;
		}
		else
		{
			redouble(a);
			while (a >= n)
				a -= n;
			bisect(b);
		}
	a = res;
}

template <>
void mulmod(long long & a, long long b, const long long & n)
{
	bool neg = false;
	if (a < 0)
	{
		neg = !neg;
		a = -a;
	}
	if (b < 0)
	{
		neg = !neg;
		b = -b;
	}
	unsigned long long aa = a;
	mulmod<unsigned long long>(aa, (unsigned long long)b, (unsigned long long)n);
	a = (long long)aa * (neg ? -1 : 1);
}


//! ��������� a^k (mod n). ���������� �������� ���������� � �������
template <class T, class T2>
T powmod(T a, T2 k, const T & n)
{
	T res = 1;
	while (k)
		if (!even(k))
		{
			mulmod(res, a, n);
			--k;
		}
		else
		{
			mulmod(a, a, n);
			bisect(k);
		}
	return res;
}

//! ��������� ����� n � ����� q*2^p
template <class T>
void transform_num(T n, T & p, T & q)
{
	T p_res = 0;
	while (even(n))
	{
		++p_res;
		bisect(n);
	}
	p = p_res;
	q = n;
}

//! �������� �������
template <class T, class T2>
T gcd(const T & a, const T2 & b)
{
	return (a == 0) ? b : gcd(b % a, a);
}

//! ��������� jacobi(a,b)
template <class T>
T jacobi(T a, T b)
{

#pragma warning (push)
#pragma warning (disable: 4146)

	if (a == 0)
		return 0;
	if (a == 1)
		return 1;

	if (a < 0)
		if ((b & 2) == 0)
			return jacobi(-a, b);
		else
			return -jacobi(-a, b);

	T e, a1;
	transform_num(a, e, a1);

	T s;
	if (even(e) || (b & 7) == 1 || (b & 7) == 7)
		s = 1;
	else
		s = -1;
	if ((b & 3) == 3 && (a1 & 3) == 3)
		s = -s;
	if (a1 == 1)
		return s;
	return s * jacobi(b % a1, a1);

#pragma warning (pop)

}


//! ��������� pi(b) ������ ������� �����. ���������� ������ �� ������ � �������� (� ������� ����� ��������� ������ �������, ��� ����) � � pi - pi(b)
template <class T, class T2>
vector<T> & get_primes(const T & b, T2 & pi)
{

	static vector<T> primes;
	static T counted_b;

	typedef typename vector<T>::iterator iterator;
	// ���� ��������� ��� ��� �������� �����, ���������� ���, ����� ����������� �������
	if (counted_b >= b)
		pi = T2(upper_bound(primes.begin(), primes.end(), b) - primes.begin());
	else
	{

		// ����� 2 ������������ ��������
		if (counted_b == 0)
		{
			primes.push_back(2);
			counted_b = 2;
		}

		// ������ ������������ ��� ��������, ���� �� ������ ������ ���������� �������
		T first = counted_b == 2 ? 3 : primes.back() + 2;
		for (T cur = first; cur <= b; ++++cur)
		{
			bool cur_is_prime = true;
			for (typename vector<T>::iterator iter = primes.begin(); iter != primes.end(); ++iter)
			{
				const T & div = *iter;
				if (div * div > cur)
					break;
				if (cur % div == 0)
				{
					cur_is_prime = false;
					break;
				}
			}
			if (cur_is_prime)
				primes.push_back(cur);
		}

		counted_b = b;
		pi = (T2)primes.size();

	}

	return primes;

}

//! ����������� �������� n �� ��������, ������������ ��� �������� �� m. ���������: 1 - ���� n ����� �������, p - ��� ��������� ��������, 0 - ���� ����������, �������� �� n ������� ��� ���
template <class T, class T2>
T2 prime_div_trivial(const T & n, T2 m)
{

	typedef typename vector<T2>::iterator iterator;
	// ������� ��������� ����������� ������
	if (n == 2 || n == 3)
		return 1;
	if (n < 2)
		return 0;
	if (even(n))
		return 2;

	// ���������� ������� �� 3 �� m
	T2 pi;
	vector<T2> & primes = get_primes(m, pi);

	// ����� �� ��� �������
	for (typename vector<T2>::iterator iter = primes.begin(); iter != primes.end(); ++iter)
	{
		T2 & div = *iter;
		if (div * div > n)
			break;
		else
			if (n % div == 0)
				return div;
	}

	if (n < m*m)
		return 1;
	return 0;

}

//! ��������� �������� �������-������ �������� n �� �������� �� ������ b
template <class T, class T2>
bool miller_rabin(T n, T2 b)
{

	// ������� ��������� ����������� ������
	if (n == 2)
		return true;
	if (n < 2 || even(n))
		return false;

	// ���������, ��� n � b ������� ������ (����� ��� �������� � ������)
	// ���� ��� �� ������� ������, �� ���� n �� ������, ���� ����� ��������� b
	if (b < 2)
		b = 2;
	for (T g; (g = gcd(n, b)) != 1; ++b)
		if (n > g)
			return false;

	// ��������� n-1 = q*2^p
	T n_1 = n;
	--n_1;
	T p, q;
	transform_num(n_1, p, q);

	// ��������� b^q mod n, ���� ��� ����� 1 ��� n-1, �� n, ��������, �������
	T rem = powmod(T(b), q, n);
	if (rem == 1 || rem == n_1)
		return true;

	// ������ ��������� b^2q, b^4q, ... , b^((n-1)/2)
	// ���� �����-���� �� ��� ����� n-1, �� n, ��������, �������
	for (T i = 1; i<p; i++)
	{
		mulmod(rem, rem, n);
		if (rem == n_1)
			return true;
	}

	return false;

}

//! ��������� �������� ������-��������� �������� n �� ��������. ������������ ��������� �������� ������ � ����������� ���������. �������� ������ � ��������� ������!!! ������ �������� unused �� ������������, �� ������ ���� ���
template <class T, class T2>
bool lucas_selfridge(const T & n, T2 unused)
{

	// ������� ��������� ����������� ������
	if (n == 2)
		return true;
	if (n < 2 || even(n))
		return false;

	// ���������, ��� n �� �������� ������ ���������, ����� �������� ���� ������
	if (perfect_square(n))
		return false;

	// �������� ���������: ������� ������ ����� d �����, ���:
	// jacobi(d,n)=-1 � ��� ����������� ���� { 5,-7,9,-11,13,... }
	T2 dd;
	for (T2 d_abs = 5, d_sign = 1;; d_sign = -d_sign, ++++d_abs)
	{
		dd = d_abs * d_sign;
		T g = gcd(n, d_abs);
		if (1 < g && g < n)
			// ����� �������� - d_abs
			return false;
		if (jacobi(T(dd), n) == -1)
			break;
	}

	// ��������� ���������
	T2
		p = 1,
		q = (p*p - dd) / 4;

	// ��������� n+1 = d*2^s
	T n_1 = n;
	++n_1;
	T s, d;
	transform_num(n_1, s, d);

	// �������� ������
	T
		u = 1,
		v = p,
		u2m = 1,
		v2m = p,
		qm = q,
		qm2 = q * 2,
		qkd = q;
	for (unsigned bit = 1, bits = bits_in_number(d); bit < bits; bit++)
	{
		mulmod(u2m, v2m, n);
		mulmod(v2m, v2m, n);
		while (v2m < qm2)
			v2m += n;
		v2m -= qm2;
		mulmod(qm, qm, n);
		qm2 = qm;
		redouble(qm2);
		if (test_bit(d, bit))
		{
			T t1, t2;
			t1 = u2m;
			mulmod(t1, v, n);
			t2 = v2m;
			mulmod(t2, u, n);

			T t3, t4;
			t3 = v2m;
			mulmod(t3, v, n);
			t4 = u2m;
			mulmod(t4, u, n);
			mulmod(t4, (T)dd, n);

			u = t1 + t2;
			if (!even(u))
				u += n;
			bisect(u);
			u %= n;

			v = t3 + t4;
			if (!even(v))
				v += n;
			bisect(v);
			v %= n;
			mulmod(qkd, qm, n);
		}
	}

	// ����� ������� (��� ������-�������)
	if (u == 0 || v == 0)
		return true;

	// �������������� ��������, ����� ��������� ��������� ����� "�����������" � �������
	T qkd2 = qkd;
	redouble(qkd2);
	for (T2 r = 1; r < s; ++r)
	{
		mulmod(v, v, n);
		v -= qkd2;
		if (v < 0) v += n;
		if (v < 0) v += n;
		if (v >= n) v -= n;
		if (v >= n) v -= n;
		if (v == 0)
			return true;
		if (r < s - 1)
		{
			mulmod(qkd, qkd, n);
			qkd2 = qkd;
			redouble(qkd2);
		}
	}

	return false;

}

//! �������� �����-��������-��������-�������� (BPSW) �������� n �� ��������
template <class T>
bool baillie_pomerance_selfridge_wagstaff(T n)
{

	// ������� ��������� �� ����������� �������� - �� 29
	int div = prime_div_trivial(n, 29);
	if (div == 1)
		return true;
	if (div > 1)
		return false;
	// ���� div == 0, �� �� ����������� �������� n �� �������

	// ���� �������-������ �� ������ 2
	if (!miller_rabin(n, 2))
		return false;

	// ��������� ���� ������-���������
	return lucas_selfridge((ll)n, 0ll);

}

//! �������� �����-��������-��������-�������� (BPSW) �������� n �� ��������
template <class T>
bool isprime(T n)
{
	return baillie_pomerance_selfridge_wagstaff(n);
}

//! ����� �������� p-1 ������������ �����. ������� ���������� ��������� �������� ����� ��� 1, ���� ������ �� �������
template <class T>
T pollard_p_1(T n)
{
	// ��������� ���������, ����������� ������ �� ������������������ � �������� ������
	const T b = 13;
	const T q[] = { 2, 3, 5, 7, 11, 13 };

	// ��������� ������� ���������
	T a = 5 % n;
	for (int j = 0; j<10; j++)
	{

		// ���� ����� a, ������� ������� ������ � n
		while (gcd(a, n) != 1)
		{
			mulmod(a, a, n);
			a += 3;
			a %= n;
		}

		// ��������� a^M
		for (size_t i = 0; i < sizeof q / sizeof q[0]; i++)
		{
			T qq = q[i];
			T e = (T)floor(log((double)b) / log((double)qq));
			T aa = powmod(a, powmod(qq, e, n), n);
			if (aa == 0)
				continue;

			// ���������, �� ������ �� �����
			T g = gcd(aa - 1, n);
			if (1 < g && g < n)
				return g;
		}

	}

	// ���� ������ �� �����
	return 1;

}

//! ����� �������� RHO ������������ �����. ���������� ��� ��������� �������� ��� 1, ���� ������ �� ���� �������
template <class T>
T pollard_rho(T n, unsigned iterations_count = 100000)
{
	T
		b0 = rand() % n,
		b1 = b0,
		g;
	mulmod(b1, b1, n);
	if (++b1 == n)
		b1 = 0;
	g = gcd(abs(b1 - b0), n);
	for (unsigned count = 0; count<iterations_count && (g == 1 || g == n); count++)
	{
		mulmod(b0, b0, n);
		if (++b0 == n)
			b0 = 0;
		mulmod(b1, b1, n);
		++b1;
		mulmod(b1, b1, n);
		if (++b1 == n)
			b1 = 0;
		g = gcd(abs(b1 - b0), n);
	}
	return g;
}

//! ����� ��������-����� ������������ �����. ���������� ��� ��������� �������� ��� 1, ���� ������ �� ���� �������
template <class T>
T pollard_bent(T n, unsigned iterations_count = 19)
{
	T
		b0 = rand() % n,
		b1 = (b0*b0 + 2) % n,
		a = b1;
	for (unsigned iteration = 0, series_len = 1; iteration<iterations_count; iteration++, series_len *= 2)
	{
		T g = gcd(b1 - b0, n);
		for (unsigned len = 0; len<series_len && (g == 1 && g == n); len++)
		{
			b1 = (b1*b1 + 2) % n;
			g = gcd(abs(b1 - b0), n);
		}
		b0 = a;
		a = b1;
		if (g != 1 && g != n)
			return g;
	}
	return 1;
}

//! ����� �������� Monte-Carlo ������������ �����. ���������� ��� ��������� �������� ��� 1, ���� ������ �� ���� �������
template <class T>
T pollard_monte_carlo(T n, unsigned m = 100)
{
	T b = rand() % (m - 2) + 2;

	static vector<T> primes;
	static T m_max;
	if (primes.empty())
		primes.push_back(3);
	if (m_max < m)
	{
		m_max = m;
		for (T prime = 5; prime <= m; ++++prime)
		{
			bool is_prime = true;
			for (typename vector<T>::iterator iter = primes.begin(); iter != primes.end(); ++iter)
			{
				T div = *iter;
				if (div*div > prime)
					break;
				if (prime % div == 0)
				{
					is_prime = false;
					break;
				}
			}
			if (is_prime)
				primes.push_back(prime);
		}
	}

	T g = 1;
	for (size_t i = 0; i<primes.size() && g == 1; i++)
	{
		T cur = primes[i];
		while (cur <= n)
			cur *= primes[i];
		cur /= primes[i];
		b = powmod(b, cur, n);
		g = gcd(abs(b - 1), n);
		if (g == n)
			g = 1;
	}

	return g;
}

//! ����� ����� ������������ �����. �������� � ������ ������ �� O(sqrt(n)). ���������� ��������� ��������. ������ �������� ������ ���� ���� �� ����, ��� � ������, ������ signed
template <class T, class T2>
T ferma(const T & n, T2 unused)
{
	T2
		x = sq_root(n),
		y = 0,
		r = x*x - y*y - n;
	for (;;) {
		if (r == 0)
			return x != y ? x - y : x + y;
		else
			if (r > 0)
			{
				r -= y + y + 1;
				++y;
			}
			else
			{
				r += x + x + 1;
				++x;
			}
		if (x % 50 == 0 && times > 1.9)
			return 1;
	}
}


bitset<1000007> F;

vector<ull> P;
//! ����������� ������������ �����. ��������� �������� ������ ���� ���� �� ����, ��� � ������, ������ signed. ���������� ���� BPSW, ����� �����, ����� �������� RHO, ����� ��������-�����, ����� �������� Monte-Carlo
template <class T, class T2>
void factorize(const T & n, map<T, unsigned> & result, T2 unused)
{
	if (n == 1)
		;
	else
		// ���������, �� ������� �� �����
		if (isprime(n))
			++result[n];
		else
			// ���� ����� ���������� ���������, �� ��� ��������� ������� ���������
			if (n < 1000 * 1000)
			{
				T div = prime_div_trivial(n, 1000);
				++result[div];
				factorize(n / div, result, unused);
			}
			else
			{
				// ����� �������, ��������� �� ��� ��������� ������������
				T div;
				// ������� ���� ������� ��������� ��������
				div = pollard_monte_carlo(n);
				if (div == 1)
					div = pollard_rho(n);
				if (div == 1)
					div = pollard_p_1(n);
				if (div == 1)
					div = pollard_bent(n);
				// ���� ��������� �������� ������ �� ����, �� ��������� �������� �����, ������� �������������� ������� ��������
				if (div == 1) 
					div = ferma(n, unused);

				if (div == 1) {
					++result[n];
					return;
				}
				// ���������� ������������ ��������� ���������
				factorize(div, result, unused);
				factorize(n / div, result, unused);
			}
}


int solve()
{
	fornn(i, 2, 1000007)
		F[i] = 1;
	for (int i = 2; i * i < 1000007; i++)
		if (F[i])
			for (int j = i * i; j < 1000007; j += i)
				F[j] = 0;
	forn(i, 1000007)
		if (F[i])
			P.push_back(i);

	typedef unsigned long long base;

	base n;
	cin >> n;
	n--;
	map <base, unsigned> m;
	factorize(n, m, (long long)0);

	int f = 0;

	for (map <base, unsigned>::iterator i = m.begin(); i != m.end(); ++i)
		forn(j, i->second)
			f++;

	cout << f << "\n";
	for (map <base, unsigned>::iterator i = m.begin(); i != m.end(); ++i)
		forn(j, i->second)
			cout << i->first - 1 << " ";
	return 0;
}
