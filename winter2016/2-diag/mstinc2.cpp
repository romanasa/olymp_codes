#include "retrodeque.h"
#include <bits/stdc++.h>
#define err(...) fprintf(stderr, __VA_ARGS__)
 
using namespace std;
 
typedef long long ll;
 
struct st {
    int tp, val;
};
 
vector<st> T;
 
void init(int n, int* type, int* value)
{
    for (int i = 0; i < n; i++)
        T.push_back({ type[i], value[i] });
}
 
void insert_command(int pos, int type, int value)
{
    T.insert(T.begin() + pos, { type, value });
}
 
void erase_command(int pos)
{
    T.erase(T.begin() + pos);
}
 
int get_front(int pos)
{
    deque<int> cur;
 
    for (int i = 0; i < pos; i++) {
        if (T[i].tp == 0) {
            cur.push_front(T[i].val);
        }
        if (T[i].tp == 1) {
            cur.push_back(T[i].val);
        }
        if (T[i].tp == 2) {
            if (cur.empty()) return -(i + 1);
            cur.pop_front();
        }
        if (T[i].tp == 3) {
            if (cur.empty()) return -(i + 1);
            cur.pop_back();
        }
    }
    if (cur.empty()) return 0;
    return cur.front();
}
 
int get_back(int pos)
{
 
    deque<int> cur;
 
    for (int i = 0; i < pos; i++) {
        if (T[i].tp == 0) {
            cur.push_front(T[i].val);
        }
        if (T[i].tp == 1) {
            cur.push_back(T[i].val);
        }
        if (T[i].tp == 2) {
            if (cur.empty()) return -(i + 1);
            cur.pop_front();
        }
        if (T[i].tp == 3) {
            if (cur.empty()) return -(i + 1);
            cur.pop_back();
        }
    }
    if (cur.empty()) return 0;
    return cur.back();
}