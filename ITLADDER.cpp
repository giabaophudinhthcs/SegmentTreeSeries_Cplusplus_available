// Link: https://oj.vnoi.info/problem/segtree_itladder

#include <bits/stdc++.h>

#define st first
#define nd second

using namespace std;

typedef long long ll;

const int nMax = 1e6 + 10;
const ll MOD = 1000000007LL;

class ST{
	public:
    	ll sum[nMax];
    	pair<ll, ll> lazy[nMax];
    	
    	void build(int si, int sl, int sr, long long x[]){
        	if (sl == sr){
            	this->sum[si] = x[sl];
            	this->lazy[si] = {0, 0};
            	return;
        	}
        	int sm = (sl + sr) >> 1;
        	this->build(si << 1, sl, sm, x);
        	this->build(si << 1 | 1, sm + 1, sr, x);
        	this->sum[si] = this->sum[si << 1] + this->sum[si << 1 | 1];
        	this->sum[si] %= MOD;
        	this->lazy[si] = {0, 0};
    	}
    	
    	void fix(int si, int sl, int sr){
    		pair<ll, ll> p = this->lazy[si];
    		this->sum[si] += (p.st * (sr + sl) * (sr - sl + 1) / 2) % MOD;
    		this->sum[si] %= MOD;
    		this->sum[si] += (p.nd * (sr - sl + 1)) % MOD;
    		this->sum[si] %= MOD;
    		if (sl != sr){
    			this->lazy[si << 1].st += p.st;
    			this->lazy[si << 1].st %= MOD;
    			this->lazy[si << 1].nd += p.nd;
    			this->lazy[si << 1].nd %= MOD;
    			this->lazy[si << 1 | 1].st += p.st;
    			this->lazy[si << 1 | 1].st %= MOD;
    			this->lazy[si << 1 | 1].nd += p.nd;
    			this->lazy[si << 1 | 1].nd %= MOD;
			}
			this->lazy[si] = {0LL, 0LL};
		}
		
		void update(int si, int sl, int sr, int l, int r, ll x, ll y){
			fix(si, sl, sr);
			if (sr < l || r < sl) return;
			if (l <= sl && sr <= r){
				this->lazy[si].st += x;
				this->lazy[si].st %= MOD;
				this->lazy[si].nd += (y - l * x);
				this->lazy[si].nd %= MOD;
				this->lazy[si].nd += MOD;
				this->lazy[si].nd %= MOD;
				fix(si, sl, sr);
				return;
			}
			int sm = (sl + sr) >> 1;
			this->update(si << 1, sl, sm, l, r, x, y);
			this->update(si << 1 | 1, sm + 1, sr, l, r, x, y);
			this->sum[si] = this->sum[si << 1] + this->sum[si << 1 | 1];
			this->sum[si] %= MOD;
		}
		
		long long get(int si, int sl, int sr, int l, int r){
			fix(si, sl, sr);
			if (sr < l || r < sl) return 0;
			if (l <= sl && sr <= r) return this->sum[si];
			int sm = (sl + sr) >> 1;
			long long g1 = get(si << 1, sl, sm, l, r);
			long long g2 = get(si << 1 | 1, sm + 1, sr, l, r);
			return (g1 + g2) % MOD;
		}
};

int n, q, l, r, t;
long long a[nMax], A, B;
ST tree;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    for (int x = 1; x <= n; ++x) a[x] = 0;
    tree.build(1, 1, n, a);
    for (int x = 1; x <= q; ++x){
    	cin >> t >> l >> r;
    	if (t == 1){
    	    cin >> A >> B;
    	    tree.update(1, 1, n, l, r, A, B);
    	}
    	if (t == 2) cout << tree.get(1, 1, n, l, r) << "\n";
	}
    return 0;
}
