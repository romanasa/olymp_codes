#include <cstdio>

using namespace std; 

int main() { 
	double x = 1;
	double y = 1;
	
	for (int i = 0; i < 100; i++) {
		x = x * (float)1.1;
		y = (double)1.1 * y;
	}
	
	printf("%.40f\n%.40f\n", x, y);
	return 0; 
}