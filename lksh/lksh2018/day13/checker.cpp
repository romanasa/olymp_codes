#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef long long ll;

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	
	int n = inf.readInt();
	
	vector<pair<ll, ll> > A(n);
	for (int i = 0; i < n; i++)
		A[i].first = inf.readInt(), A[i].second = inf.readInt();
		
	pair<ll, ll> pJ;
	pJ.first = ans.readInt(), pJ.second = ans.readInt();
	
	ll jans = 0;
	for (auto c : A) jans = max(jans, abs(pJ.first - c.first) + abs(pJ.second - c.second));
	
	pair<ll, ll> pP;
	pP.first = ouf.readInt(), pP.second = ouf.readInt();
	
	ll pans = 0;
	for (auto c : A) pans = max(pans, abs(pP.first - c.first) + abs(pP.second - c.second));
	
	if (jans < pans)
        quitf(_wa, "jury has the better answer: jans = %lld, pans = %lld\n", jans, pans);
    else if (jans == pans)
        quitf(_ok, "answer = %lld\n", pans);
    else 
    	quitf(_fail, ":( participant has the better answer: jans = %lld, pans = %lld\n", jans, pans);
	
	return 0;
}
