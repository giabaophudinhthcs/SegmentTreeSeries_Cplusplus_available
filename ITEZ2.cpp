// Link: https://oj.vnoi.info/problem/segtree_itez2

#include <bits/stdc++.h>

using namespace std;

const int nMax = 4e6 + 10;

long long a[nMax], tree[nMax];

long long sum(int node, int sl, int sr, int l, int r){
	if (l <= sl && sr <= r) return tree[node];
	if (r < sl || sr < l) return 0;
	int sm = sl + (sr - sl) / 2;
	return sum(2 * node, sl, sm, l, r) + sum(2 * node + 1, sm + 1, sr, l, r);
}

void update(int node, int sl, int sr, int i, int x){
	if (i < sl || i > sr || sl > sr) return;
	if (sl != sr){
		int sm = sl + (sr - sl) / 2;
		update(2 * node, sl, sm, i, x);
		update(2 * node + 1, sm + 1, sr, i, x);
		tree[node] = tree[2 * node] + tree[2 * node + 1];
	}else tree[node] += x;
}

void init(int node, int sl, int sr){
	if (sl == sr){
		tree[node] = a[sl];
		return;
	}
	int sm = sl + (sr - sl) / 2;
	init(2 * node, sl, sm);
	init(2 * node + 1, sm + 1, sr);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int main(){
	int n, q, t, x;
	long long y;
	cin >> n >> q;
	for (int i = 1; i <= q; ++i){
		cin >> t >> x >> y;
		if (t == 1){
		    update(1, 1, n, x, y - a[x]);
		    a[x] = y;
		}
		else cout << sum(1, 1, n, x, y) << "\n";
	}
}
