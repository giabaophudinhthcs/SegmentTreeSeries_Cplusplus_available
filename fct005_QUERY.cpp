// QUERY - Free Contest Testing Round 5
// Link: https://oj.vnoi.info/problem/fct005_query

#include <bits/stdc++.h>

#define st first
#define nd second

using namespace std;

typedef long long ll;

const int nMax = 1e6 + 10;

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
        	this->lazy[si] = {0, 0};
    	}
    	
    	void fix(int si, int sl, int sr){
    		pair<ll, ll> p = this->lazy[si];
    		this->sum[si] += (p.st * (sr + sl) * (sr - sl + 1) / 2) + (p.nd * (sr - sl + 1));
    		if (sl != sr){
    			this->lazy[si << 1].st += p.st;
    			this->lazy[si << 1].nd += p.nd;
    			this->lazy[si << 1 | 1].st += p.st;
    			this->lazy[si << 1 | 1].nd += p.nd;
			}
			this->lazy[si] = {0, 0};
		}
		
		void update(int si, int sl, int sr, int l, int r){
			fix(si, sl, sr);
			if (sr < l || r < sl) return;
			if (l <= sl && sr <= r){
				this->lazy[si].st++;
				this->lazy[si].nd += (1 - l);
				fix(si, sl, sr);
				return;
			}
			int sm = (sl + sr) >> 1;
			this->update(si << 1, sl, sm, l, r);
			this->update(si << 1 | 1, sm + 1, sr, l, r);
			this->sum[si] = this->sum[si << 1] + this->sum[si << 1 | 1];
		}
		
		long long get(int si, int sl, int sr, int l, int r){
			fix(si, sl, sr);
			if (sr < l || r < sl) return 0;
			if (l <= sl && sr <= r) return this->sum[si];
			int sm = (sl + sr) >> 1;
			long long g1 = get(si << 1, sl, sm, l, r);
			long long g2 = get(si << 1 | 1, sm + 1, sr, l, r);
			return (g1 + g2);
		}
};

int n, q, l, r, t;
long long a[nMax];
ST tree;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int x = 1; x <= n; ++x) cin >> a[x];
    tree.build(1, 1, n, a);
    cin >> q;
    for (int x = 1; x <= q; ++x){
    	cin >> t >> l >> r;
    	if (t == 1) tree.update(1, 1, n, l, r);
    	if (t == 2) cout << tree.get(1, 1, n, l, r) << "\n";
	}
    return 0;
}
