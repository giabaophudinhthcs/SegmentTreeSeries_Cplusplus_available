#include <bits/stdc++.h>

#define FOI(i, a, b) for (int i = a; i <= b; ++i)

using namespace std;

const int nMax = 1e5 + 10;
const int oo = 2e9 + 10;

int n, m, a[nMax], t, i, v, l, r;
multiset<int> tree[4 * nMax];

int get(int sl, int sr, int si, int l, int r, int k) {
    if (sl > r || sr < l) return oo; 
    if (sl >= l && sr <= r) {
        auto it = tree[si].lower_bound(k);
        if (*it < k) return oo;
        return *it;
    }

    int sm = sl + sr >> 1;
    int get1 = get(sl, sm, 2 * si, l, r, k);
    int get2 = get(sm + 1, sr, 2 * si + 1, l, r, k);
    return min(get1, get2);
}

void update(int sl, int sr, int si, int i, int old, int val){
	if (sr < i || i < sl) return;
	if (sl == sr){
		tree[si].clear();
		tree[si].insert(val);
		return;
	}
	int sm = sl + (sr - sl) / 2;
	update(sl, sm, 2 * si, i, old, val);
	update(sm + 1, sr, 2 * si + 1, i, old, val);
	tree[si].erase(tree[si].find(old));
	tree[si].insert(val);
}

void init(int sl, int sr, int si){
	if (sl == sr){
		tree[si].insert(a[sl]);
		return;
	}
	int sm = sl + (sr - sl) / 2;
	init(sl, sm, 2 * si);
	init(sm + 1, sr, 2 * si + 1);
	tree[si] = tree[2 * si + 1];
	for (auto x: tree[2 * si]) tree[si].insert(x);
}

int main(){
	cin >> n >> m;
	FOI(x, 1, n) cin >> a[i];
	init(1, n, 1);
	FOI(x, 1, m){
		cin >> t;
		if (t == 1){
			cin >> i >> v;
			int old = a[i];
			update(1, n, 1, i, old, v);
			a[i] = v;
		}else{
			cin >> l >> r >> v;
			int a = get(1, n, 1, l, r, v);
			cout << (a == oo ? -1 : a) << "\n";
		}
	}
}
