// Link: https://oj.vnoi.info/problem/fct018_sub
// P/s: sus

#include <bits/stdc++.h>

using namespace std;

const int N = 4e5 + 40;
const int oo = 2e9 + 10;

class ST{
    public:
        int val[N];
        
        void build(int si, int sl, int sr){
            if (sl == sr){
                this->val[si] = oo;
                return;
            }
            
            int sm = (sl + sr) >> 1;
            this->build(si << 1, sl, sm);
            this->build(si << 1 | 1, sm + 1, sr);
            this->val[si] = min(this->val[si << 1], this->val[si << 1 | 1]);
        }
        
        void update(int si, int sl, int sr, int i, int v){
            if (i < sl || i > sr) return;
        
            if (i == sl && i == sr){
                this->val[si] = v;
                return;
            }
            
            int sm = (sl + sr) >> 1;
            this->update(si << 1, sl, sm, i, v);
            this->update(si << 1 | 1, sm + 1, sr, i, v);
            this->val[si] = min(this->val[si << 1], this->val[si << 1 | 1]);
        }
        
        int get(int si, int sl, int sr, int l, int r){
            if (r < sl || l > sr) return oo;
        
            if (l <= sl && sr <= r) return this->val[si];
            
            int sm = (sl + sr) >> 1;
            int g1 = this->get(si << 1, sl, sm, l, r);
            int g2 = this->get(si << 1 | 1, sm + 1, sr, l, r);
            return min(g1, g2);
        }
};

int t, n, a[N], M, S, s[N], m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t;
    while (t--){
        ST tree;
        M = -2e4;
        m = -oo;
        S = 0;
        cin >> n;
        tree.build(1, 0, n);
        s[0] = 0;
        tree.update(1, 0, n, 0, s[0]);
        for (int x = 1; x <= n; ++x){
            cin >> a[x];
            
            // For sub
            M = max(M, a[x]);
            if (a[x] > 0) S += a[x];
            
            // For range
            s[x] = s[x - 1] + a[x];
            m = max(m, s[x] - tree.get(1, 0, n - 1, 0, x - 1));
            tree.update(1, 0, n, x, s[x]);
        }
        if (M < 0) cout << M << " ";
        else cout << S << " ";
        cout << m << "\n";
    }
    return 0;
}
