// Link: https://oj.vnoi.info/problem/nkinv

#include <bits/stdc++.h>

using namespace std;

const int nMax = 3e5;
const int m = 60000;

int n, a[nMax], node[nMax], ans = 0;

void update(int si, int sl, int sr, int val){
    if (sr < val || val < sl) return;
    if (val == sl && val == sr){
        node[si]++;
        return;
    }
    int sm = sl + sr >> 1;
    update(si << 1, sl, sm, val);
    update(si << 1 | 1, sm + 1, sr, val);
    node[si] = node[si << 1] + node[si << 1 | 1];
}

int get(int si, int sl, int sr, int l, int r){
    if (r < sl || sr < l) return 0;
    if (l <= sl && sr <= r) return node[si];
    int sm = sl + sr >> 1;
    int g1 = get(si << 1, sl, sm, l, r);
    int g2 = get(si << 1 | 1, sm + 1, sr, l, r);
    return g1 + g2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; ++i){
        cin >> a[i];
        ans += get(1, 1, m, a[i] + 1, m);
        update(1, 1, m, a[i]);
    }
    cout << ans;
    return 0;
}
