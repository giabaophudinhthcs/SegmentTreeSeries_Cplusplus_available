// Link: https://oj.vnoi.info/problem/mink

#include <bits/stdc++.h>

using namespace std;

const int nMax = 1e5 + 10;
const int oo = 2e9 + 10;

class ST{
    public:
    	int val[nMax];
    	
    	void build(int si, int sl, int sr, int x[]){
        	if (sl == sr){
            	this->val[si] = x[sl];
            	return;
        	}
        	int sm = sl + sr >> 1;
        	this->build(2 * si, sl, sm, x);
        	this->build(2 * si + 1, sm + 1, sr, x);
        	this->val[si] = min(this->val[2 * si], this->val[2 * si + 1]);
    	}
    	
    	int get(int si, int sl, int sr, int l, int r){
        	if (r < sl || sr < l) return oo;
        	if (l <= sl && sr <= r) return this->val[si];
        	int sm = sl + sr >> 1;
        	int g1 = this->get(2 * si, sl, sm, l, r);
        	int g2 = this->get(2 * si + 1, sm + 1, sr, l, r);
        	return min(g1, g2);
    	}
};

int t, n, k, a[nMax];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t;
    for (int i = 1; i <= t; ++i){
        cin >> n >> k;
        for (int j = 1; j <= n; ++j) cin >> a[j];
        ST tree;
        tree.build(1, 1, n, a);
        for (int j = 1; j <= n - k + 1; ++j) cout << tree.get(1, 1, n, j, j + k - 1) << " ";
        cout << "\n";
    }
    return 0;
}
