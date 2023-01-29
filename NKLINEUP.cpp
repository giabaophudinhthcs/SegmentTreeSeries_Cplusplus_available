// Link: https://oj.vnoi.info/problem/nklineup

#include <bits/stdc++.h>

using namespace std;

const int nMax = 4e6 + 10;
const int oo = 1e9 + 7;

int a[nMax], treeMax[nMax], treeMin[nMax];

int Max(int node, int sl, int sr, int l, int r) {
    if (l <= sl && sr <= r)
        return treeMax[node];
    if (r < sl || sr < l)
        return 0;
    int sm = sl + (sr - sl) / 2;
    return max(Max(2 * node, sl, sm, l, r), Max(2 * node + 1, sm + 1, sr, l, r));
}

int Min(int node, int sl, int sr, int l, int r) {
    if (l <= sl && sr <= r)
        return treeMin[node];
    if (r < sl || sr < l)
        return oo;
    int sm = sl + (sr - sl) / 2;
    return min(Min(2 * node, sl, sm, l, r), Min(2 * node + 1, sm + 1, sr, l, r));
}

void initMax(int node, int sl, int sr) {
    if (sl == sr) {
        treeMax[node] = a[sl];
        return;
    }
    int sm = sl + (sr - sl) / 2;
    initMax(2 * node, sl, sm);
    initMax(2 * node + 1, sm + 1, sr);
    treeMax[node] = max(treeMax[2 * node], treeMax[2 * node + 1]);
}

void initMin(int node, int sl, int sr) {
    if (sl == sr) {
        treeMin[node] = a[sl];
        return;
    }
    int sm = sl + (sr - sl) / 2;
    initMin(2 * node, sl, sm);
    initMin(2 * node + 1, sm + 1, sr);
    treeMin[node] = min(treeMin[2 * node], treeMin[2 * node + 1]);
}

int main() {
    int n, q, l, r;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    initMax(1, 1, n);
    initMin(1, 1, n);
    for (int i = 1; i <= q; ++i) {
        cin >> l >> r;
        cout << Max(1, 1, n, l, r) - Min(1, 1, n, l, r) << " ";
    }
}
