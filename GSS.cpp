// Link: https://oj.vnoi.info/problem/gss

#include <bits/stdc++.h>

using namespace std;

const int nMax = 4e5 + 40;
const int oo = 1e9 + 7;

int Max(int x, int y, int z){
    return max(max(x, y), z);
}

class node{
    public:
        int seg;
        int pref;
        int suf;
        int sum;
        
        node(){
            this->seg = -oo;
            this->pref = -oo;
            this->suf = -oo;
            this->sum = 0;
        }
        
        node(int w, int x, int y, int z){
            this->seg = w;
            this->pref = x;
            this->suf = y;
            this->sum = z;
        }
        
        node operator +(node x){
            node ans;
            ans.seg = Max(this->seg, x.seg, this->suf + x.pref);
            ans.pref = max(this->pref, this->sum + x.pref);
            ans.suf = max(this->suf + x.sum, x.suf);
            ans.sum = this->sum + x.sum;
            return ans;
        }
};

class ST{
    public:
        node tree[nMax];
        
        void build(int x[], int si, int sl, int sr){
            if (sl == sr){
                this->tree[si] = node(x[sl], x[sl], x[sl], x[sl]);
                return;
            }
            
            int sm = sl + sr >> 1;
            this->build(x, si << 1, sl, sm);
            this->build(x, si << 1 | 1, sm + 1, sr);
            this->tree[si] = this->tree[si << 1] + this->tree[si << 1 | 1];
        }
        
        node query(int si, int sl, int sr, int L, int R){
            if (R < sl || sr < L){
                node ans = node();
                return ans;
            }
            
            if (L <= sl && sr <= R) return this->tree[si];
            
            int sm = sl + sr >> 1;
            node q1 = this->query(si << 1, sl, sm, L, R);
            node q2 = this->query(si << 1 | 1, sm + 1, sr, L, R);
            return q1 + q2;
        }
        
        int get(int sz, int L, int R){
            node ans = this->query(1, 1, sz, L, R);
            return ans.seg;
        }
};

int n, t, l, r, a[nMax];
ST Tree;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    Tree.build(a, 1, 1, n);
    cin >> t;
    for (int i = 1; i <= t; ++i){
        cin >> l >> r;
        cout << Tree.get(n, l, r) << "\n";
    }
    return 0;
}
