#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int dd = (int)1e5 + 7;
int L[dd], R[dd];
int sum[dd], bad[dd];

struct SegmentTreeMin {
    int T[4 * dd];
    void build(int v, int tl, int tr, int *A) {
        if (tl == tr) T[v] = A[tl];
        else {
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm, A);
            build(v * 2 + 1, tm + 1, tr, A);
            T[v] = min(T[v * 2], T[v * 2 + 1]);
        }
    }
    int get(int v, int tl, int tr, int l, int r) {
        if (tl == l && tr == r) return T[v];
        int tm = (tl + tr) / 2;
        if (r <= tm) return get(v * 2, tl, tm, l, r);
        if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r);
        return min(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
    }
} MIN;

struct SegmentTreeMax {
    int T[4 * dd];
    void build(int v, int tl, int tr, int *A) {
        if (tl == tr) T[v] = A[tl];
        else {
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm, A);
            build(v * 2 + 1, tm + 1, tr, A);
            T[v] = max(T[v * 2], T[v * 2 + 1]);
        }
    }
    int get(int v, int tl, int tr, int l, int r) {
        if (tl == l && tr == r) return T[v];
        int tm = (tl + tr) / 2;
        if (r <= tm) return get(v * 2, tl, tm, l, r);
        if (l > tm) return get(v * 2 + 1, tm + 1, tr, l, r);
        return max(get(v * 2, tl, tm, l, tm), get(v * 2 + 1, tm + 1, tr, tm + 1, r));
    }
} MAX;


bool check(string s) {
    vector<char> st;
    for (char c : s) {
        if (islower(c)) {
            if (st.empty()) return false;
            if (st.back() != toupper(c)) return false;
            st.pop_back();
        } else st.push_back(c);
    }
    if (st.size()) return false;
    return true;
}

int main() {
#ifdef WIN
    freopen("01", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // WIN

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //for (int it = 0; it < 500; it++) {

    string s;
    cin >> s;

    int n = (int)s.size();
    //n = 20;

    /*for (int i = 0; i < n; i++) {
        int tp = rand() % 4;
        if (tp == 0) s += 'a';
        if (tp == 1) s += 'A';
        if (tp == 2) s += 'b';
        if (tp == 3) s += 'B';
    }*/

    for (int i = 0; i < n; i++) L[i] = n, R[i] = -1;

    vector<int> st;
    for (int i = 0; i < n; i++) {
        if (islower(s[i])) {
            if (st.empty()) bad[i] = 1;
            else {
                if (s[st.back()] != toupper(s[i])) bad[st.back()] = bad[i] = 1;
                else R[st.back()] = i, L[i] = st.back();
                st.pop_back();
            }
        } else st.push_back(i);
    }
    while (st.size()) bad[st.back()] = 1, st.pop_back();


    //for (int i = 0; i < n; i++) cout << bad[i] << " "; cout << "\n";

    MAX.build(1, 0, n - 1, R);
    MIN.build(1, 0, n - 1, L);
    for (int i = 0; i < n; i++) sum[i + 1] = sum[i] + bad[i];

    //cout << s << "\n";
    //for (int i = 0; i < n; i++) cout << bad[i] << " "; cout << "\n";
    //for (int i = 0; i < n; i++) cout << L[i] << " "; cout << "\n";
    //for (int i = 0; i < n; i++) cout << R[i] << " "; cout << "\n";

    int q;
    cin >> q;
    //q = 50;

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        //l = rand() % n, r = rand() % n;
        //if (l > r) swap(l, r);

        //string t = string(s.begin() + l, s.begin() + r + 1);

        int ok = 1;

        if (sum[r + 1] - sum[l] > 0) {
            ok = 0;
        }
        if (MAX.get(1, 0, n - 1, l, r) > r) {
            ok = 0;
        }
        if (MIN.get(1, 0, n - 1, l, r) < l) {
            ok = 0;
        }
        cout << (ok ? '1' : '0');
        //if (check(t) != ok) {
            //cout << l << " " << r << "\n";
            //cout << t << " " << ok << endl;
            //assert(check(t) == ok);
            //cout << (ok ? '1' : '0');
        //    return 0;
        //}
    //    }
    //    cout << it << '\n';
    }
    return 0;
}


