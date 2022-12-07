#include <bits/stdc++.h>

using namespace std;

const int Max = 2e5 + 40;
const long oo = 1e10;

int n, m, p, l, r, k;
long d[Max], a[Max], node[Max];

long get(int si, int sl, int sr, int l, int r){
    if (r < sl || sr < l) return (-1) * oo;
    if (l <= sl && sr <= r) return node[si];
    int sm = sl + sr >> 1;
    long res1 = get(2 * si, sl, sm, l, r);
    long res2 = get(2 * si + 1, sm + 1, sr, l, r);
    return max(res1, res2);
}

void build(int si, int sl, int sr){
    if (sl == sr){
        node[si] = a[sl];
        return;
    }
    int sm = sl + sr >> 1;
    build(2 * si, sl, sm);
    build(2 * si + 1, sm + 1, sr);
    node[si] = max(node[2 * si], node[2 * si + 1]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) a[i] = 0;
    for (int i = 1; i < n; ++i) d[i] = 0;
    for (int i = 1; i <= m; ++i){
        cin >> l >> r >> k;
        d[l - 1] += k;
        d[r] -= k;
        if (l == 1) a[1] += k;
    }
    for (int i = 2; i <= n; ++i) a[i] = a[i - 1] + d[i - 1];
    build(1, 1, n);
    cin >> p;
    for (int i = 1; i <= p; ++i){
        cin >> l >> r;
        cout << get(1, 1, n, l, r) << "\n";
    }
    return 0;
}
