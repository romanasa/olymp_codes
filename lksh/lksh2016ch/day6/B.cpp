#include <bits/stdc++.h>
//#include "grader.h"
 
using namespace std;
 
int n;
double X = (int)1e9;
vector<double> T;
 
void init(int x) {
	T.clear();
    srand(135);
    n = x;
}
 
int answer(double y) {
    //if (y > X / n)
    //  return 1;
         
    //if (rand() % n == 0)
    //  return 1;
     
    int c = 0;
    for (int i = 0; i < (int)T.size(); i++)
        c += (T[i] > y);
         
    if (c == 0 && (double)T.size() * 2.5 >= n)
        return 1;   
 
    T.push_back(y);
         
    if ((int)T.size() == n)
        return 1;
         
    return 0;
}
/*
int main() {
	return 0;
}*/
