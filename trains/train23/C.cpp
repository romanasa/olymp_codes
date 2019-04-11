#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

char A[543][543];

int main() {
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
    //freopen("01", "r", stdin);

    int n;
    cin >> n;

    int black = 0;

    for (char a = 'a'; a <= 'h'; a++) {
        for (char b = '1'; b <= '8'; b++) {
            A[a][b] = '.';
        }
    }


    A['a']['1'] = 'R';
    A['b']['1'] = 'N';
    A['c']['1'] = 'B';
    A['d']['1'] = 'Q';
    A['e']['1'] = 'K';
    A['f']['1'] = 'B';
    A['g']['1'] = 'N';
    A['h']['1'] = 'R';
    for (char a = 'a'; a <= 'h'; a++) A[a]['2'] = 'P';

    A['a']['8'] = 'r';
    A['b']['8'] = 'n';
    A['c']['8'] = 'b';
    A['d']['8'] = 'q';
    A['e']['8'] = 'k';
    A['f']['8'] = 'b';
    A['g']['8'] = 'n';
    A['h']['8'] = 'r';
    for (char a = 'a'; a <= 'h'; a++) A[a]['7'] = 'p';


    for (int i = 0; i < n; i++) {

        string s;
        cin >> s;

        if (s == "0-0-0") {
            char c = black ? '8' : '1';
            A['a'][c] = A['e'][c] = '.';
            A['c'][c] = black ? 'k' : 'K';
            A['d'][c] = black ? 'r' : 'R';
        } else if (s == "0-0") {
            char c = black ? '8' : '1';
            A['h'][c] = A['e'][c] = '.';
            A['f'][c] = black ? 'r' : 'R';
            A['g'][c] = black ? 'k' : 'K';
        } else {
            char f = s[0];
            if ((int)s.size() > 6) f = black ? tolower(s.back()) : toupper(s.back());
            A[s[1]][s[2]] = '.';
            A[s[4]][s[5]] = f;
        }
        black ^= 1;
    }



    for (char i = '8'; i >= '1'; i--) {
        for (char j = 'a'; j <= 'h'; j++) {
            cout << A[j][i];
        }
        cout << "\n";
    }

    return 0;
}

