// Link: https://codeforces.com/contest/52/problem/C

#include <bits/stdc++.h>

#define FOR(i, a, b) for(int i = a; i <= b ; ++i)
#define FORD(i, a, b) for(int i = a; i >= b ; --i)
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define pb push_back
#define len length

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<string> vs;

const int nMax = 1e6 + 10;
const int mMax = 3e3 + 30;
const ll MOD = 1e9 + 7;
const ll MODLL = 1e18 + 7;
const int oo = 2e9 + 10;
const ll ooll = 2e18 + 10;
const auto seed = chrono::steady_clock::now().time_since_epoch().count();

int n, q, l, r, cntSpace, Len, Ll, Lr, Rl, Rr, Vl, Vr, s[3];
string Response, Sl, Sr, Sv;
ll v, a[nMax];

class ST{
	public:
		ll val[nMax];
		ll lazy[nMax];
		
		void build(int si, int sl, int sr){
			if (sl == sr){
				this->val[si] = a[sl];
				this->lazy[si] = 0;
				return;
			}
			
			int sm = (sl + sr) >> 1;
			this->build(si << 1, sl, sm);
			this->build(si << 1 | 1, sm + 1, sr);
			this->val[si] = min(this->val[si << 1], this->val[si << 1 | 1]);
			this->lazy[si] = 0;
		}
		
		void fix(int si, int sl, int sr){
			this->val[si] += this->lazy[si];
			
			if (sl != sr){
				this->lazy[si << 1] += this->lazy[si];
				this->lazy[si << 1 | 1] += this->lazy[si];
			}
			
			this->lazy[si] = 0;
		}
		
		void update(int si, int sl, int sr, int l, int r, int v){
			this->fix(si, sl, sr);
			
			if (r < sl || sr < l) return;
			
			if (l <= sl && sr <= r){
				this->lazy[si] += v;
				this->fix(si, sl, sr);
				return;
			}
			
			int sm = (sl + sr) >> 1;
			this->update(si << 1, sl, sm, l, r, v);
			this->update(si << 1 | 1, sm + 1, sr, l, r, v);
			this->val[si] = min(this->val[si << 1], this->val[si << 1 | 1]);
		}
		
		ll get(int si, int sl, int sr, int l, int r){
			this->fix(si, sl, sr);
			
			if (r < sl || sr < l) return ooll;
			
			if (l <= sl && sr <= r) return this->val[si];
			
			int sm = (sl + sr) >> 1;
			ll g1 = this->get(si << 1, sl, sm, l, r);
			ll g2 = this->get(si << 1 | 1, sm + 1, sr, l, r);
			return min(g1, g2);
		}
};

ST tree;

void Update(int L, int R, int V){
	if (L <= R) tree.update(1, 0, n - 1, L, R, V);
	else{
		tree.update(1, 0, n - 1, L, n - 1, V);
		tree.update(1, 0, n - 1, 0, R, V);
	}
}

ll Min(int L, int R){
	if (L <= R) return tree.get(1, 0, n - 1, L, R);
	else{
		ll Left = tree.get(1, 0, n - 1, L, n - 1);
		ll Right = tree.get(1, 0, n - 1, 0, R);
		return min(Left, Right);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	FOR(x, 0, n - 1) cin >> a[x];
	tree.build(1, 0, n - 1);
	cin >> q;
	cin.ignore();
	FOR(x, 1, q){
		getline(cin, Response);
		l = r = v = 0;
		// cntSpace, Len, Ll, Lr, Rl, Rr, Vl, Vr, s[3]
		cntSpace = s[1] = s[2] = 0;
		Len = int(Response.len());
		while (Response[Len - 1] == ' ') Response.erase(Len - 1, 1);
		FOR(y, 0, Len - 1){
			if (Response[y] == ' '){
				cntSpace++;
				s[cntSpace] = y;
			}
		}
		if (cntSpace == 2){
			Ll = 0;
			Lr = s[1] - 1;
			Rl = s[1] + 1;
			Rr = s[2] - 1;
			Vl = s[2] + 1;
			Vr = Len - 1;
			
			Sl = Response.substr(Ll, Lr - Ll + 1);
			Sr = Response.substr(Rl, Rr - Rl + 1);
			Sv = Response.substr(Vl, Vr - Vl + 1);
			
			FOR(y, 0, int(Sl.len()) - 1){
				int digit = int(Sl[y] - '0');
				l = 10 * l + digit;
			}
			
			FOR(y, 0, int(Sr.len()) - 1){
				int digit = int(Sr[y] - '0');
				r = 10 * r + digit;
			}
			
			int sign = 1;
			if (Sv[0] == '-'){
				sign = -1;
				Sv.erase(0, 1);
			}
			FOR(y, 0, int(Sv.len()) - 1){
				int digit = int(Sv[y] - '0');
				v = 10LL * v + digit;
			}
			v *= sign;
			
			Update(l, r, v);
		}else{
			Ll = 0;
			Lr = s[1] - 1;
			Rl = s[1] + 1;
			Rr = Len - 1;
			
			Sl = Response.substr(Ll, Lr - Ll + 1);
			Sr = Response.substr(Rl, Rr - Rl + 1);
			
			FOR(y, 0, int(Sl.len()) - 1){
				int digit = int(Sl[y] - '0');
				l = 10 * l + digit;
			}
			
			FOR(y, 0, int(Sr.len()) - 1){
				int digit = int(Sr[y] - '0');
				r = 10 * r + digit;
			}
			
			cout << Min(l, r) << "\n";
		}
	}
	return 0;
}
