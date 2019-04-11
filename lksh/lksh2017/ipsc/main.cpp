#include <bits/stdc++.h>

using namespace std;

map<int, string> ma;

const int INF = 1e9;
const int MAXOPERATIONS = 70;

int get_num(int i, const string &s) {
	int num = 0;
	for (int j = i; j < (int)s.length(); j++)
		num = num * 10 + s[j] - '0';
	return num;
}

int go(int i, const string &s) {
	if (s[0] == 'j' && s[1] == 'u' && s[2] == 'm' && s[3] == 'p')
		return get_num(5, s) - 1;
	return i + 1;
}

int solve(const vector <string> &v, int x) {
	vector <string> pr;
	for (int i = 0; i < (int)v.size(); i++) {
		bool two = false;
		for (int j = 0; j < (int)v[i].length(); j++)
			if (v[i][j] == ';')
				two = true;
		if (!two)
			pr.push_back(v[i]);
		else {
			string s1 = "";
			for (int j = 0; j < (int)v[i].length(); j++) {
				if (v[i][j] == ';') {
					pr.push_back(s1);
					s1 = "";
				} else
					s1 += v[i][j];
			}
			pr.push_back(s1);
		}
	}

	vector <int> stack;
	int ans = -INF;

	bool has_red = false;
	for (int i = 0, counter = 0; i < (int)pr.size(); i = go(i, pr[i]), counter++) {
		string cur = pr[i];
		if (cur == "input") {
			if (has_red)
				return -INF;
			stack.push_back(x);
			has_red = true;
		} else if (cur == "pop") {
			if (stack.empty())
				return -INF;
			stack.pop_back();
		} else if (cur == "print") {
			if (ans != -INF)
				return -INF;
			if (stack.empty())
				return -INF;
			ans = stack.back();
		} else if (cur[0] == 'p' && cur[1] == 'u') {
			int num = get_num(5, cur);
			stack.push_back(num);
		} else if (cur == "dup") {
			if (stack.empty())
				return -INF;
			stack.push_back(stack.back());
		} else {
			if (stack.size() < 2)
				return -INF;
			int a = stack.back();
			stack.pop_back();
			int b = stack.back();
			stack.pop_back();
			if (cur == "+")
				stack.push_back(a + b);
			if (cur == "-")
				stack.push_back(a - b);
			if (cur == "/") {
				if (b == 0)
					return -INF;
				stack.push_back(a / b);
			}
			if (cur == "*")
				stack.push_back(a * b);
		}

		if (counter > MAXOPERATIONS)
			return -INF;
	}

	if (!has_red)
		return -INF;
	return ans;
}

vector <int> tests = {-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100};

bool check(vector <string> a) {
	for (int i = 0; i < (int)tests.size(); i++) {
		int x = tests[i];
		if (solve(a, x) != x)
			return false;
		reverse(a.begin(), a.end());
		if (solve(a, x) != -x)
			return false;
		sort(a.begin(), a.end());
		if (solve(a, x) != x * x)
			return false;
	}
	return true;
}


/*void rec(int nows, bool re = 0, bool wr = 0, bool ju = 0){
    if (nows == 8){

    }

    s.push_back("");
    for (int i = 0; i < 9; i++){
        s.back() = "";
        if (i != 1 && i != 4){
            if ((re && i == 0))
                continue;
            if (wr && i == 3)
                continue;
            s.back() += ma[i];
            rec(nows + 1, re || i == 0, wr || i == 3, ju);
        }
        else if (i == 1){
            if (ju)
                continue;
            for (int j = 1; j <= 8; j++){
                s.back() = "";
                s.back() += ma[1];
                s.back().push_back(j + '0');
                rec(nows + 1, re, wr, 1);
            }
        }
        else{
            s.back() = ma[4];
            s.back().push_back('1');
            rec(nows + 1, re, wr, ju);
            s.back() = ma[4];
            s.back().push_back('-');
            s.back().push_back('1');
            rec(nows + 1, re, wr, ju);
        }
    }

    for (int i = 0; i < 9; i++){
    for (int it = 0; it < 9; it++){
        if (i == 0 && j == 0 || i == 1 && j == 1 || i == 3 && j == 3)
            continue;
        s.back() = "";
        if (i != 1 && i != 4){
            if ((re && i == 0))
                continue;
            if (wr && i == 3)
                continue;
            s.back() += ma[i];
            rec(nows + 1, re || i == 0, wr || i == 3, ju);
        }
        else if (i == 1){
            if (ju)
                continue;
            for (int j = 1; j <= 8; j++){
                s.back() = "";
                s.back() += ma[1];
                s.back().push_back(j + '0');
                rec(nows + 1, re, wr, 1);
            }
        }
        else{
            s.back() = ma[4];
            s.back().push_back('1');
            rec(nows + 1, re, wr, ju);
            s.back() = ma[4];
            s.back().push_back('-');
            s.back().push_back('1');
            rec(nows + 1, re, wr, ju);
        }
    }
    s.pop_back();
}*/

vector<string> s;
ofstream out("output.txt");

void rec(int nows, int re = 0, int wr = 0, int ju = 0){
    if (nows == 8){
        if (!re || ! wr || !ju)
            return;
        if (check(s)){
            for (int it = 0; it < 8; it++){
                out << s[it] << '\n';
            }
            exit(0);
        }
        return;
    }

    s.push_back("");
    while (1){
        if (rand() % 2){
            int it = rand() % 18;
            int jt = rand() % 18;
            int nre = re + (it == 0) + (jt == 0);
            int nwr = wr + (it == 9) + (jt == 9);
            int nju = ju + (it >= 1 && it <= 8) + (jt >= 1 && jt <= 8);
            if (nre > 1 || nwr > 1 || nju > 1)
                continue;

            s.back() = ma[it] + ";" + ma[jt];

            rec(nows + 1, nre, nwr, nju);
            break;
        }
        else{
            int it = rand() % 18;
            int nre = re + (it == 0);
            int nwr = wr + (it == 9);
            int nju = ju + (it >= 1 && it <= 8);
            if (nre > 1 || nwr > 1 || nju > 1)
                continue;

            s.back() = ma[it];
            rec(nows + 1, nre, nwr, nju);
            break;
        }
    }

    s.pop_back();
}

int main()
{
    srand(1488);
    ma[0] = "input";
    ma[1] = "jump 1";
    ma[2] = "jump 2";
    ma[3] = "jump 3";
    ma[4] = "jump 4";
    ma[5] = "jump 5";
    ma[6] = "jump 6";
    ma[7] = "jump 7";
    ma[8] = "jump 8";
    ma[1 +8] = "pop";
    ma[1 +9] = "print";
    ma[1 +10] = "push 1";
    ma[1 +11] = "push -1";
    ma[1 +12] = "dup";
    ma[1 +13] = "+";
    ma[1 +14] = "-";
    ma[1 +15] = "*";
    ma[1 +16] = "/";

    while (1)
        rec(0);
    return 0;
}
