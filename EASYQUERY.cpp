// EASYQUERY - Tưởng dễ nhưng ko dễ :))
// EASYQUERY - Thought it was easy but not easy :))
// Link problem: https://oj.vnoi.info/problem/bedao_g11_easyquery

#include <bits/stdc++.h>

using namespace std;

const int Max = 4e5 + 40;

int up[Max], L[Max], R[Max], n, q, a[Max], t, l, r, x, k;

class node{
    public:
        long long lazy;
        long long val;
};

node Nodes[Max];

void propagate(int si, int sl, int sr){
    Nodes[si].val += Nodes[si].lazy * (sr - sl + 1);
    if (sl != sr){
        Nodes[2 * si].lazy += Nodes[si].lazy;
        Nodes[2 * si + 1].lazy += Nodes[si].lazy;
    }
    Nodes[si].lazy = 0;
}

void update(int si, int sl, int sr, int l, int r, int x){
    propagate(si, sl, sr);
    if (r < sl || sr < l) return;
    if (l <= sl && sr <= r){
        Nodes[si].lazy += x;
        propagate(si, sl, sr);
        return;
    }
    int sm = sl + sr >> 1;
    update(2 * si, sl, sm, l, r, x);
    update(2 * si + 1, sm + 1, sr, l, r, x);
    Nodes[si].val = Nodes[2 * si].val + Nodes[2 *si + 1].val;
}

long long get(int si, int sl, int sr, int l, int r){
    propagate(si, sl, sr);
    if (r < sl || sr < l) return 0;
    if (sl >= l && sr <= r) return Nodes[si].val;
    int sm = sl + sr >> 1;
    long long s1 = get(2 * si, sl, sm, l, r);
    long long s2 = get(2 * si + 1, sm + 1, sr, l, r);
    return (s1 + s2);
}

void build(int si, int sl, int sr){
    if (sl == sr){
        Nodes[si].val = a[sl];
        return;
    }
    int sm = sl + sr >> 1;
    build(2 * si, sl, sm);
    build(2 * si + 1, sm + 1, sr);
    Nodes[si].val = Nodes[2 * si].val + Nodes[2 * si + 1].val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);
    for (int i = 1; i <= q; ++i){
        cin >> t;
        if (t == 1){
            cin >> l >> r >> x;
            up[i] = x;
            L[i] = l;
            R[i] = r;
            update(1, 1, n, l, r, up[i]);
        }
        if (t == 2){
            cin >> k;
            up[i] = (-1) * up[k];
            L[i] = L[k];
            R[i] = R[k];
            update(1, 1, n, L[i], R[i], up[i]);
        }
        if (t == 3){
            cin >> l >> r;
            cout << get(1, 1, n, l, r) << "\n";
        }
    }
    return 0;
}
