#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;

struct Fen {
	int T[dd];
	
	void upd(int pos, int val) {
		for (int i = pos + 1; i < dd; i += (i&-i)) T[i] += val;
	}
	
	int get(int pos) {
		int res = 0;
		for (int i = pos + 1; i; i -= (i&-i)) res += T[i];
		return res;
	}
	int get(int l, int r) {
		return get(r) - get(l - 1);
	}
} F;

struct ev {
	int x, l, r, tp, id;
};

int ans[dd];
int a[dd];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m; 
	cin >> n >> m;
	
	for (int i = 0; i < n; i++) cin >> a[i];
	
	vector<ev> E;
	for (int i = 0; i < m; i++) {
		int l, r, x, y;
		cin >> l >> r >> x >> y;
		l--, r--;
		E.push_back({ l, x, y, 0, i });
		E.push_back({ r, x, y, 1, i });
	}
	
	sort(E.begin(), E.end(), [](const ev &a, const ev &b){
		return a.x == b.x ? a.tp < b.tp : a.x < b.x;
	});
	
	int j = 0;
	for (int i = 0; i < n; i++) {
		while (j < (int)E.size() && E[j].x == i && E[j].tp == 0)
			ans[E[j].id] -= F.get(E[j].l, E[j].r), j++;
		F.upd(a[i], 1);
		while (j < (int)E.size() && E[j].x == i && E[j].tp == 1)
			ans[E[j].id] += F.get(E[j].l, E[j].r), j++;
	}
	for (int i = 0; i < m; i++) cout << ans[i] << "\n";
	
	return 0;
}