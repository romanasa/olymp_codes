//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("sse,sse2,sse3,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, n1;

inline int check(int x) {
	return x >= n1 ? x - n1 : x;
}
        
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (true)
    {
        cin >> n;
        if (n == 0)
            return 0;
        vector<int> s(n);
        for (int i = 0; i < n; i++)
            cin >> s[i];
        for (int i = n; i < n * 2; i++)
        {
            s.push_back(s[i - n]);
        }
        s.push_back(-1);
        vector<int> s1 = s;
        sort(s1.begin(), s1.end());

        map<ll, ll> to;
        ll kk = -1;
        for (int i = 0; i < s1.size(); i++)
        {
            if (i == 0 || s1[i] != s1[i - 1])
                kk++;
            to[s1[i]] = kk;
        }

        vector<int> cnt(s.size(), 0);
        vector<int> head(s.size(), 0);
        vector<int> per(s.size());
        vector<int> cl(s.size());

        for (int i = 0; i < s.size(); i++)
        {
            cl[i] = to[s[i]];
            cnt[cl[i]]++;
        }

        for (int i = 1; i < head.size(); i++)
        {
            head[i] = head[i - 1] + cnt[i - 1];
        }

        for (int i = 0; i < s.size(); i++)
        {
            per[head[cl[i]]++] = i;
        }

        int L = 1;
        n1 = s.size();
        while (L < s.size())
        {
            fill(cnt.begin(), cnt.end(), 0);

            for (int i = 0; i < s.size(); i++)
            {
                cnt[cl[i]]++;
            }
            head[0] = 0;
            for (int i = 1; i < s.size(); i++)
            {
                head[i] = head[i - 1] + cnt[i - 1];
            }

            vector<int> per1(s.size());

            for (int i = 0; i < per1.size(); i++)
            {
                per1[head[cl[check(i + L)]]++] = i;
            }

            //vector<ll> per2(s.size());

            head[0] = 0;
            for (int i = 1; i < s.size(); i++)
            {
                head[i] = head[i - 1] + cnt[i - 1];
            }

            for (int i = 0; i < per.size(); i++)
            {
                per[head[cl[per1[i]]]++] = per1[i];
            }
            int cls = -1;
            vector<int> cl1(s.size());
            for (int i = 0; i < s.size(); i++)
            {
                if (i == 0)
                {
                    cls++;
                    cl1[per[i]] = cls;
                    continue;
                }
                if (cl[per[i - 1]] != cl[per[i]] || cl[per[i - 1] + L] != cl[per[i] + L])
                    cls++;
                cl1[per[i]] = cls;
            }
            cl = cl1;
            L *= 2;
        }

        vector<int> oper(per.size());
        for (int i = 0; i < oper.size(); i++)
        {
            oper[per[i]] = i;
        }

        vector<int> lcp(per.size(), 0);

        int lc = 0;
        for (int i = 0; i < per.size(); i++)
        {
            int j = oper[i];
            if (--lc < 0)
                lc = 0;
            if (j != per.size() - 1)
                while(lc < per.size() && s[check(per[j] + lc)] == s[check(per[j + 1] + lc)])
                    lc++;
            lcp[j] = lc;
        }

        ll sum = 0;
        ll i1 = 0;
        while (true)
        {
            int minn = 0;
            while (i1 < per.size() && per[i1] >= n)
                i1++;
            if (i1 == per.size())
                break;
            minn = lcp[i1];
            ll i2 = i1 + 1;
            while (i2 < per.size() && per[i2] >= n)
            {
                minn = min(minn, lcp[i2 - 1]);
                i2++;
            }
            sum += min(minn, n);
            if (i2 >= n1)
                break;
            i1 = i2;
        }
        cout << sum << " ";
    }
}