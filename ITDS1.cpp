// Link: https://oj.vnoi.info/problem/segtree_itds1

#include <bits/stdc++.h>

using namespace std;

const int nMax = 5e5 + 50;
const int oo = 2e9 + 10;

class ST{
    public:
    
    multiset<int> val[nMax];
    
    void build(int si, int sl, int sr, int x[]){
        if (sl == sr){
            this->val[si].insert(x[sl]);
            return;
        }
        
        int sm = (sl + sr) >> 1;
        
        this->build(si << 1, sl, sm, x);
        this->build(si << 1 | 1, sm + 1, sr, x);
        this->val[si] = this->val[si << 1 | 1];
        for (auto t: this->val[si << 1]) this->val[si].insert(t);
    }
    
    void update(int si, int sl, int sr, int i, int Old, int New){
        if (i < sl || sr < i) return;
        
        if (sl == i && sr == i){
            this->val[si].clear();
            this->val[si].insert(New);
            return;
        }
        
        int sm = (sl + sr) >> 1;
        this->update(si << 1, sl, sm, i, Old, New);
        this->update(si << 1 | 1, sm + 1, sr, i, Old, New);
        this->val[si].erase(this->val[si].find(Old));
        this->val[si].insert(New);
    }
    
    int get(int si, int sl, int sr, int l, int r, int k){
        if (r < sl || sr < l) return oo;
        
        if (l <= sl && sr <= r){
            auto it = this->val[si].lower_bound(k);
            if (it == this->val[si].end()) return oo;
            else return *it;
        }
        
        int sm = (sl + sr) >> 1;
        
        int g1 = this->get(si << 1, sl, sm, l, r, k);
        int g2 = this->get(si << 1 | 1, sm + 1, sr, l, r, k);
        
        return min(g1, g2);
    }
};

int n, m, a[nMax], t, l, r, k, x;
ST tree;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    tree.build(1, 1, n, a);
    
    for (int i = 1; i <= m; ++i){
        cin >> t;
        if (t == 1){
            cin >> x >> k;
            tree.update(1, 1, n, x, a[x], k);
            a[x] = k;
        }else{
            cin >> l >> r >> k;
            int ans = tree.get(1, 1, n, l, r, k);
            if (ans == oo) ans = -1;
            cout << ans << "\n";
        }
    }
    return 0;
}
