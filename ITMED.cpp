// Link: https://oj.vnoi.info/problem/segtree_itmed

#include <bits/stdc++.h>

using namespace std;

const int nMax = 5e5 + 40;
const int oo = 2e9 + 10;

class ST{
    public:
        long long val[nMax];
        
        void build(int si, int sl, int sr, long long x[]){
            if (sl == sr){
                this->val[si] = x[sl];
                return;
            }
            int sm = (sl + sr) >> 1;
            this->build(2 * si, sl, sm, x);
            this->build(2 * si + 1, sm + 1, sr, x);
            this->val[si] = max(this->val[2 * si], this->val[2 * si + 1]);
        }
        
        void update(int si, int sl, int sr, int i, long long v){
            if (sr < i || i < sl) return;
            if (i == sl && i == sr){
                this->val[si] = v;
                return;
            }
            int sm = (sl + sr) >> 1;
            this->update(2 * si, sl, sm, i, v);
            this->update(2 * si + 1, sm + 1, sr, i, v);
            this->val[si] = max(this->val[2 * si], this->val[2 * si + 1]);
        }
        
        long long get(int si, int sl, int sr, int L, int R){
            if (sr < L || R < sl) return -oo;
            if (L <= sl && sr <= R) return this->val[si];
            int sm = (sl + sr) >> 1;
            long long g1 = this->get(2 * si, sl, sm, L, R);
            long long g2 = this->get(2 * si + 1, sm + 1, sr, L, R);
            return max(g1, g2);
        }
};

int n, k;
long long a[nMax], dp[nMax];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i){
        cin >> a[i];
        dp[i] = -oo;
    }
    ST tree;
    tree.build(1, 1, n, dp);
    dp[1] = max(a[1], 0LL);
    tree.update(1, 1, n, 1, dp[1]);
    for (int i = 2; i <= n; ++i){
        int l = max(1, i - k);
        int r = i - 1;
        dp[i] = max(tree.get(1, 1, n, l, r), 0LL) + a[i];
        dp[i] = max(dp[i], 0LL);
        tree.update(1, 1, n, i, dp[i]);
    }
    cout << max(tree.val[1], 0LL);
    return 0;
}
