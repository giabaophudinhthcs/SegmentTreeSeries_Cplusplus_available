// Segment Tree using Lazy Propagation

#include <bits/stdc++.h>

using namespace std;

const int nMax = 4e6 + 10;
const long long oo = 1e18 + 10;

long long a[nMax], tree[nMax], lazy[nMax];

void fix(int node, int sl, int sr){ // For lazy pending
    tree[node] += lazy[node]; // Add the pending
    if (sl != sr){ // sl != sr <=> this isn't a leaf node
        // Move the pending to its child
        lazy[2 * node] += lazy[node];
        lazy[2 * node + 1] += lazy[node];
    }
    lazy[node] = 0; // Clear the pending
}
long long Max(int node, int sl, int sr, int l, int r){
	fix(node, sl, sr);
    if (r < sl || sr < l) return -1 * oo;
    if (l <= sl && sr <= r) return tree[node];
    int sm = sl + (sr - sl) / 2;
    return max(Max(2 * node, sl, sm, l, r), Max(2 * node + 1, sm + 1, sr, l, r));
}

void update(int node, int sl, int sr, int l, int r, int x){
	fix(node, sl, sr);
    if (r < sl || sr < l) return;
    if (l <= sl && sr <= r){
        lazy[node] += x;
        fix(node, sl, sr);
        return;
    }
    int sm = sl + (sr - sl) / 2;
    update(2 * node, sl, sm, l, r, x);
    update(2 * node + 1, sm + 1, sr, l, r, x);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

void init(int node, int sl, int sr){
	if (sl == sr){
		tree[node] = a[sl];
		return;
	}
	int sm = sl + (sr - sl) / 2;
	init(2 * node, sl, sm);
	init(2 * node + 1, sm + 1, sr);
	tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

int main(){
	int n, q, t, l, r, x;
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	init(1, 1, n);
    cin >> q;
	for (int i = 1; i <= q; ++i){
		cin >> t >> l >> r;
		if (t == 1){
            cin >> x;
            update(1, 1, n, l, r, x);
        }
		else cout << Max(1, 1, n, l, r) << "\n";
	}
}
