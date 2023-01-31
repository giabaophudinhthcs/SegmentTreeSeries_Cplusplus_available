// SEQ51 - Free Contest Testing Round 20
// Link (2 links):
// Free Contest Testing Round 20: https://oj.vnoi.info/problem/fct020_seq51
// Free Contest 81: https://oj.vnoi.info/problem/fc081_seq51

#include <bits/stdc++.h>

using namespace std;

const int nMax = 5e5 + 50;
const int oo = 1e9 + 10;

int n, a[nMax], ans = 0, rmq[nMax];

void build(int si, int sl, int sr){
    if (sl == sr){
        rmq[si] = a[sl] - sl;
        return;
    }
    
    int sm = (sl + sr) >> 1;
    build(si << 1, sl, sm);
    build(si << 1 | 1, sm + 1, sr);
    rmq[si] = min(rmq[si << 1], rmq[si << 1 | 1]);
}

int get(int si, int sl, int sr, int l, int r){
    if (sr < l || r < sl) return oo;
    
    if (l <= sl && sr <= r) return rmq[si];
    
    int sm = (sl + sr) >> 1;
    int g1 = get(si << 1, sl, sm, l, r);
    int g2 = get(si << 1 | 1, sm + 1, sr, l, r);
    return min(g1, g2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);
    for (int L = 1; L <= n; ++L){
        int l = L, r = n, R = L - 1;
        while (l <= r){
            int m = (l + r) >> 1;
            if (get(1, 1, n, L, m) >= 1 - L){
                R = m;
                l = m + 1;
            }else r = m - 1;
        }
        ans = max(ans, R - L + 1);
    }
    cout << ans;
    return 0;
}
