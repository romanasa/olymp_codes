#include <bits/stdc++.h>

using namespace std;

int main(int argc, char * argv[]) {
    mt19937 rnd(atoi(argv[1]));

    int n = rnd() % 10 + 1;
    int a = rnd() % n + 1;
    int b = rnd() % n + 1;

    cout << n << " " << a << " " << b << "\n";
    return 0;
}
