// Link: https://codeforces.com/contest/242/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int nMax = 5e5 + 50;

class ST{
    public:
    	int bit_sum[nMax], lazy[nMax];
    	
    	void build(int si, int sl, int sr, int a[], int bit){
            if (sl == sr){
                this->bit_sum[si] = (a[sl] >> bit & 1);
                this->lazy[si] = 0;
                return;
            }
            int sm = (sl + sr) >> 1;
            this->build(si << 1, sl, sm, a, bit);
            this->build(si << 1 | 1, sm + 1, sr, a, bit);
            this->bit_sum[si] = this->bit_sum[si << 1] + this->bit_sum[si << 1 | 1];
            this->lazy[si] = 0;
        }
    	
    	void fix(int si, int sl, int sr){
            if (this->lazy[si]){
                this->bit_sum[si] = (sr - sl + 1) - this->bit_sum[si];
                if (sl != sr){
                    this->lazy[si << 1] ^= 1;
                    this->lazy[si << 1 | 1] ^= 1;
                }
            }
            this->lazy[si] = 0;
        }
    	
    	void update(int si, int sl, int sr, int l, int r){
            fix(si, sl, sr);
            if (sr < l || r < sl) return;
			if (l <= sl && sr <= r){
				this->lazy[si] ^= 1;
				fix(si, sl, sr);
				return;
			}
			int sm = (sl + sr) >> 1;
			this->update(si << 1, sl, sm, l, r);
			this->update(si << 1 | 1, sm + 1, sr, l, r);
			this->bit_sum[si] = this->bit_sum[si << 1] + this->bit_sum[si << 1 | 1];
        }
    	
    	int get(int si, int sl, int sr, int l, int r){
            fix(si, sl, sr);
			if (sr < l || r < sl) return 0;
			if (l <= sl && sr <= r) return this->bit_sum[si];
			int sm = (sl + sr) >> 1;
			int g1 = get(si << 1, sl, sm, l, r);
			int g2 = get(si << 1 | 1, sm + 1, sr, l, r);
			return (g1 + g2);
        }
};

int n, m, a[nMax], l, r, x, t;
ST tree[25];

int main(){
    cin >> n;
    for (int k = 1; k <= n; ++k) cin >> a[k];
    for (int k = 0; k < 20; ++k) tree[k].build(1, 1, n, a, k);
    cin >> m;
    for (int k = 1; k <= m; ++k){
        cin >> t >> l >> r;
        if (t == 1){
            ll ans = 0;
            for (int i = 0; i <= 19; ++i) ans += tree[i].get(1, 1, n, l, r) * (1LL << i);
            cout << ans << "\n";
        }else{
            cin >> x;
            for (int i = 0; i <= 19; ++i){
                if (x >> i & 1) tree[i].update(1, 1, n, l, r);
            }
        }
    }
}
