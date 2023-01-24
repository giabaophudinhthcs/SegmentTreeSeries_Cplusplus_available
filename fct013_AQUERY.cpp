// AQUERY - Free Contest Testing Round 13
// Link: https://oj.vnoi.info/problem/fct013_aquery

#include <bits/stdc++.h>

using namespace std;

const int nMax = 4e5 + 40;

class ST{
	public:
		long long val[nMax], lazy[nMax];
		
		void build(int si, int sl, int sr){
			if (sl == sr){
				this->val[si] = 0;
				this->lazy[si] = -1;
				return;
			}
			int sm = (sl + sr) >> 1;
			this->build(si << 1, sl, sm);
			this->build(si << 1 | 1, sm + 1, sr);
			this->val[si] = this->val[si << 1] + this->val[si << 1 | 1];
			this->lazy[si] = -1;
		}
		
		void fix(int si, int sl, int sr){
			long long &x = this->lazy[si];
			if (x != -1){
				int sm = (sl + sr) >> 1;
				this->lazy[si << 1] = this->lazy[si << 1 | 1] = x;
				this->val[si << 1] = (sm - sl + 1) * x;
				this->val[si << 1 | 1] = (sr - sm) * x;
				x = -1;
			}
		}
		
		void update(int si, int sl, int sr, int l, int r, long long x){
			if (sr < l || r < sl) return;
			if (l <= sl && sr <= r){
				this->lazy[si] = x;
				this->val[si] = (sr - sl + 1) * x;
				return;
			}
			fix(si, sl, sr);
			int sm = (sl + sr) >> 1;
			this->update(si << 1, sl, sm, l, r, x);
			this->update(si << 1 | 1, sm + 1, sr, l, r, x);
			this->val[si] = this->val[si << 1] + this->val[si << 1 | 1];
		}
		
		long long get(int si, int sl, int sr, int l, int r){
			if (r < sl || sr < l) return 0;
			if (l <= sl && sr <= r) return this->val[si];
			fix(si, sl, sr);
			int sm = (sl + sr) >> 1;
			return (this->get(si << 1, sl, sm, l, r) + this->get(si << 1 | 1, sm + 1, sr, l, r));
		}
};

int n, q, r;
long long p;
ST tree;

int main(){
	cin >> n >> q;
	tree.build(1, 1, n);
	for (int x = 1; x <= q; ++x){
		cin >> r >> p;
		int lo = 1, hi = r - 1, l = r;
		while (lo <= hi){
			int mid = (lo + hi) >> 1;
			long long a_mid = tree.get(1, 1, n, mid, mid);
			long long x = (r - mid + 1) * a_mid - tree.get(1, 1, n, mid, r);
			if (x <= p){
				l = mid;
				hi = mid - 1;
			}else lo = mid + 1;
		}
		long long a_l = tree.get(1, 1, n, l, l);
		p -= (r - l + 1) * a_l - tree.get(1, 1, n, l, r);
		long long a_new = a_l + p / (r - l + 1);
		int m = l + (p % (r - l + 1)) - 1;
		tree.update(1, 1, n, l, m, a_new + 1);
		tree.update(1, 1, n, m + 1, r, a_new);
	}
	for (int x = 1; x <= n; ++x) cout << tree.get(1, 1, n, x, x) << " ";
}
