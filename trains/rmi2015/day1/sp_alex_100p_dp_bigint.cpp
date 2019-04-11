#include <bits/stdc++.h>

using namespace std;

class BigInteger
{
private:

  static const int base = 1000000000;
  static const int base_digits = 9;

  vector<int> a;

public:

  BigInteger();
  BigInteger(long long);
  BigInteger(const BigInteger &);

  BigInteger& operator =  (const BigInteger &);
  BigInteger& operator =  (long long);

  BigInteger  operator +  (const BigInteger &) const;
  BigInteger& operator += (const BigInteger &);

  BigInteger  operator *  (int) const;
  BigInteger& operator *= (int);

  BigInteger  operator /  (int) const;
  BigInteger& operator /= (int);

  void trim();

  bool isEven() const;

  ///Input/Output operators ---------------------------------------------------------
  friend ostream& operator << (ostream &stream, const BigInteger &B)
  {
    stream << (B.a.empty() ? 0 : B.a.back());

    for (int i = (int)B.a.size() - 2; i >= 0; i--)
      stream << setw(base_digits) << setfill('0') << B.a[i];

    return stream;
  }
  ///----------------------------------------------------------------------------------
};

///Constructors --------------------------------------------------------------------------------

BigInteger::BigInteger() : a()
{
  this->a.clear();
}

BigInteger::BigInteger(long long value) : a()
{
  *this = value;
}

BigInteger::BigInteger(const BigInteger &BI): a()
{
  this->a = BI.a;

  this->trim();
}

///Constructors --------------------------------------------------------------------------------

BigInteger& BigInteger::operator = (const BigInteger &BI)
{
  this->a = BI.a;

  this->trim();

  return *this;
}

BigInteger& BigInteger::operator = (long long value)
{
  this->a.clear();

  do
    {
      this->a.push_back(value % base);
      value /= base;

    } while (value > 0);

  return *this;
}

BigInteger BigInteger::operator + (const BigInteger &B) const
{
  BigInteger solution = B;

  int maximLg = (int)max(this->a.size(), B.a.size());

  for (int i = 0, carry = 0; i < maximLg || carry; ++i)
    {
      if (i == (int)solution.a.size())
        solution.a.push_back(0);

      long long current = solution.a[i];

      current += carry;

      if (i < (int)this->a.size())
        current += this->a[i];

      carry = (current >= base);

      if (carry)
        current -= base;

      solution.a[i] = current;
    }

  return solution;
}

BigInteger& BigInteger::operator += (const BigInteger &B)
{
  *this = *this + B;

  return *this;
}

BigInteger BigInteger::operator * (int value) const
{
  BigInteger solution = *this;

  for (int i = 0, carry = 0; i < (int)solution.a.size() || carry; ++i)
    {
      if (i == (int)solution.a.size())
        solution.a.push_back(0);

      long long current = (1LL * solution.a[i] * value) + 1LL * carry;
      carry = current / base;
      solution.a[i] = current % base;
    }

  solution.trim();

  return solution;
}

BigInteger& BigInteger::operator *= (int value)
{
  *this = *this * value;

  return *this;
}

BigInteger BigInteger::operator / (int value) const
{
  BigInteger solution = *this;

  for (int i = (int)solution.a.size() - 1, rem = 0; i >= 0; i--)
    {
      long long current = 1LL * rem * base + 1LL * solution.a[i];
      solution.a[i] = (current / value);
      rem = (current % value);
    }

  solution.trim();

  return solution;
}

BigInteger& BigInteger::operator /= (int value)
{
  *this = *this / value;

  return *this;
}

void BigInteger::trim()
{
  while (this->a.size() && this->a.back() == 0)
    this->a.pop_back();
}

bool BigInteger::isEven() const
{
  return (this->a.empty() || ((this->a[0] & 1) == 0));
}

// Main

const int MAX_N = 2000;

BigInteger denominator[1 + MAX_N / 2];

int main()
{
  ifstream in("spoiler.in");
  ofstream out("spoiler.out");

  int N, K, A, B;

  in >> N >> K;

  A = (N + 1) / 2;
  B = K - A;

  BigInteger numerator = 1;

  for (int score = K - 1; score >= 0; --score)
    {
      numerator *= 2;

      for (int i = min(score, A - 1); i >= score - i; --i)
        {
          int j = score - i;

          if (i == A - 1 && j < B)
            {
              ///S(i,j) = S(i,j+1)
              denominator[j] = denominator[j + 1];
              denominator[j] *= 2;
            }
          else if (i > B && j == B)
            {
              ///S(i,j) = S(i+1,j)
              denominator[j] *= 2;
            }
          else if (i == j) ///diagonal
            {
              ///S(i,j) = 1 + S(i+1,j)
              denominator[j] *= 2;
              denominator[j] += numerator;
            }
          else
            {
              ///S(i,j) = 1 + (S(i+1,j) + S(i,j+1)) / 2
              denominator[j] += numerator;
              denominator[j] += denominator[j + 1];
            }
        }
    }

  while (denominator[0].isEven() && numerator.isEven()) {
    denominator[0] /= 2;
    numerator /= 2;
  }

  out << denominator[0] << "\n";
  out << numerator << "\n";

  return 0;
}
