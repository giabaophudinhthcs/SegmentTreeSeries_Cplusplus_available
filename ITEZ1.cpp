// Link: https://oj.vnoi.info/problem/segtree_itez1

#include <bits/stdc++.h>
using namespace std;

const int nMax = 4e6 + 40;

class ST_Max{
	public:
		int tree[nMax];
		void updateUtil(int stStart, int stEnd, int i, int x, int si);
		void update(int arr[], int n, int i, int x);
		int maxUtil(int stStart, int stEnd, int qStart, int qEnd, int si);
		int maxVal(int n, int qStart, int qEnd);
		void initTree(int arr[], int stStart, int stEnd, int si);
    	void print();
};

void ST_Max::print(){
    for (int i = 0; i < 9; ++i){
        cout << this->tree[i] << " ";
    }
    cout << "\n";
}

void ST_Max::updateUtil(int stStart, int stEnd, int i, int x, int si){
	if (i < stStart || i > stEnd) return;
	if (stStart == stEnd ) this->tree[si] = x;
	else{
		int stMid = stStart + (stEnd - stStart) / 2;
		this->updateUtil(stStart, stMid, i, x, 2 * si + 1);
		this->updateUtil(stMid + 1, stEnd, i, x, 2 * si + 2);
		this->tree[si] = max(this->tree[2 * si + 1], this->tree[2 * si + 2]);
	}
}

void ST_Max::update(int arr[], int n, int i, int x){
	if (i < 0 || i > n - 1){
		cout << "Invalid input!\n";
		return;
	}
	arr[i] = x;
	this->updateUtil(0, n - 1, i, x, 0);
}

int ST_Max::maxUtil(int stStart, int stEnd, int qStart, int qEnd, int si){
	if (stEnd < qStart || qEnd < stStart) return INT_MIN;
	if (stEnd <= qEnd && qStart <= stStart) return this->tree[si];
	int stMid = stStart + (stEnd - stStart) / 2;
	return max(this->maxUtil(stStart, stMid, qStart, qEnd, 2 * si + 1), this->maxUtil(stMid + 1, stEnd, qStart, qEnd, 2 * si + 2));
}

int ST_Max::maxVal(int n, int qStart, int qEnd){
	if (qStart < 0 || qEnd < 0 || qStart > n - 1 || qEnd > n - 1 || qStart > qEnd){
		cout << "Invalid input!\n";
		return -1;
	}
	return this->maxUtil(0, n - 1, qStart, qEnd, 0);
}

void ST_Max::initTree(int arr[], int stStart, int stEnd, int si){
	if (stStart == stEnd){
		this->tree[si] = arr[stStart];
		return;
	}
	int stMid = stStart + (stEnd - stStart) / 2;
	this->initTree(arr, stStart, stMid, 2 * si + 1);
	this->initTree(arr, stMid + 1, stEnd, 2 * si + 2);
	this->tree[si] = max(this->tree[2 * si + 1], this->tree[2 * si + 2]);
}

int main(){
	int n, t, q, x, y;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) cin >> a[i];
    cin >> t;
    ST_Max Tree;
    Tree.initTree(a, 0, n - 1, 0);
    for (int i = 0; i < t; ++i){
        cin >> q;
        if (q == 1){
            cin >> x >> y;
            Tree.update(a, n, x - 1, y);
        }else{
            cin >> x >> y;
            cout << Tree.maxVal(n, x - 1, y - 1) << "\n";
        }
    }
}
