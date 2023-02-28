// Link: https://oj.vnoi.info/problem/fct044_house
// P/s: Còn có cách tốt hơn cách trong code dưới :v Sao cũng được (vì code dưới cũng đã AC rồi :)))

#include <bits/stdc++.h>

using namespace std;

const int nMax = 5e5 + 50;
const int oo = 2e9 + 7;

class ST{
	public:
		int val[nMax];
		
		void build(int si, int sl, int sr, int x[]){
			if (sl == sr){
				this->val[si] = x[sl];
				return;
			}
			
			int sm = (sl + sr) >> 1;
			this->build(si << 1, sl, sm, x);
			this->build(si << 1 | 1, sm + 1, sr, x);
			this->val[si] = min(this->val[si << 1], this->val[si << 1 | 1]);
		}
		
		int get(int si, int sl, int sr, int l, int r){
			if (sr < l || r < sl) return oo;
			
			if (l <= sl && sr <= r) return this->val[si];
			
			int sm = (sl + sr) >> 1;
			int g1 = this->get(si << 1, sl, sm, l, r);
			int g2 = this->get(si << 1 | 1, sm + 1, sr, l, r);
			return min(g1, g2);
		}
};

int n, c[nMax], ans = -1;
ST tree;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n;
	for (int x = 1; x <= n; ++x) cin >> c[x];
	tree.build(1, 1, n, c);
	for (int x = 1; x < n; ++x){
		int m = tree.get(1, 1, n, x + 1, n);
		if (m <= c[x]) ans = max(ans, c[x] - m);
	}
	if (ans == -1) cout << "Lo nang roi!";
	else cout << ans;
	return 0;
}

// Chuc moi nguoi buoi toi vui ve :3
