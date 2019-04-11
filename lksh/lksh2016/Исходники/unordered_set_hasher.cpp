#include <unordered_set>

using namespace std;

struct Hasher {
  static const long long P = 1e9 + 7, Q = 1e9 + 9;
  size_t operator() ( pair<int, int> x ) const { return (x.first * P + x.second) % Q; }
};

const int SIZE = 1e7;
unordered_set <pair<int, int>, Hasher> h(SIZE); 

int main() {
	
}