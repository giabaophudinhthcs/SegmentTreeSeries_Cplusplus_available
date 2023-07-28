// Link: https://codeforces.com/contest/339/problem/D

#include <bits/stdc++.h>

using namespace std;

const int nMax = 5e5 + 50;

class node{
    public:
    	int val;
    	int level;
};

int n, sz, m, a[nMax], p, x, pow2[20];
node nodes[nMax];

void update(int si, int sl, int sr){
    if (p < sl || sr < p) return;
    if (p == sl && p == sr){
        nodes[si].val = x;
        return;
    }
    int sm = sl + sr >> 1;
    update(2 * si, sl, sm);
    update(2 * si + 1, sm + 1, sr);
    if (nodes[2 * si].level % 2 != 0) nodes[si].val = nodes[2 * si].val | nodes[2 * si + 1].val;
    else nodes[si].val = nodes[2 * si].val ^ nodes[2 * si + 1].val;
    nodes[si].level = nodes[2 * si].level + 1;
}

void build(int si, int sl, int sr){
    if (sl == sr){
        nodes[si].val = a[sl];
        nodes[si].level = 1;
        return;
    }
    int sm = sl + sr >> 1;
    build(2 * si, sl, sm);
    build(2 * si + 1, sm + 1, sr);
    if (nodes[2 * si].level % 2 != 0) nodes[si].val = nodes[2 * si].val | nodes[2 * si + 1].val;
    else nodes[si].val = nodes[2 * si].val ^ nodes[2 * si + 1].val;
    nodes[si].level = nodes[2 * si].level + 1;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    pow2[1] = 2;
    for (int i = 2; i < 20; ++i) pow2[i] = pow2[i - 1] * 2;
    sz = pow2[n];
    for (int i = 1; i <= sz; ++i) cin >> a[i];
    build(1, 1, sz);
    for (int i = 1; i <= m; ++i){
        cin >> p >> x;
        update(1, 1, sz);
        cout << nodes[1].val << "\n";
    }
}
