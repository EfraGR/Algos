using namespace std;
#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define ff first
#define ss second
#define pb push_back
#define forx(i,n) for(int i=0; i<(int)n; ++i)
#define printF(x) for(auto &w : x) {cout << w << " ";} cout << endl;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<vl> vvl;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef priority_queue<ll> pqll;
const char ln = '\n';
const int MOD = 1e9+7;
const ll inf  = 1e18;
const string abc = "abcdefghijklmnopqrstuvwxyz";
int dirx[4] = {0,-1,1,0};
int diry[4] = {-1,0,0,1};

// ST Recursivo
typedef long long ty;
struct segTree{
	vector<ty> v, laz;
	ty null = 0;
	int tam;

	segTree(vector<ty>& vals){
		tam = vals.size();
		v.assign(2 * tam, -1);
		laz.assign(2 * tam, 0);
		build(vals, 0, 0, tam - 1);
	}

	void build(vector<ty>& vals, int ind, int l, int r){
		ty mid = (l + r) >> 1;

		if (l == r){
			v[ind] = vals[l];
		}else{
			build(vals, ind + 1, l, mid);
			build(vals, ind + 2 * (mid - l + 1) , mid + 1, r);
			v[ind] = oper(v[ind + 1], v[ind + 2 * (mid - l + 1)]);
		}
	}

	// get range query
	ty get(int ql, int qr, int ind, int l, int r){
		prop(ind, l, r);
		if (l > qr || r < ql) return null;
		if (l >= ql && r <= qr) return v[ind];

		int mid = (l + r) >> 1;
		ty v1 = get(ql, qr, ind + 1, l, mid);
		ty v2 = get(ql, qr, ind + 2 * (mid - l + 1), mid + 1, r);

		return (oper(v1, v2));
	}

	ty get(int l, int r){
		return get(l, r, 0, 0, tam - 1);
	}

	 // update point query
	void upd(ty uval, int qind, int ind, int l, int r){
		if (l > qind || r < qind) return;
		if (l == qind && r == qind){
            v[ind] = uval;
			return;
		}
 
		int mid = (l + r) >> 1;
		upd(uval, qind, ind + 1, l, mid);
		upd(uval, qind, ind + 2 * (mid - l + 1), mid + 1, r);	
 
		v[ind] = oper(v[ind + 1], v[ind + 2 * (mid - l + 1)]);
	}
    
    void upd(int x, ty uval){
		upd(uval, x, 0, 0, tam - 1);
	}

	// update range query
	void upd(ty uval, int ul, int ur, int ind, int l, int r){
		prop(ind, l, r);
		if (l > ur || r < ul) return;
		if (l >= ul && r <= ur){
			laz[ind] += uval;
			prop(ind, l, r);
			return;
		}

		int mid = (l + r) >> 1;
		upd(uval, ul, ur, ind + 1, l, mid);
		upd(uval, ul, ur, ind + 2 * (mid - l + 1), mid + 1, r);	

		v[ind] = oper(v[ind + 1], v[ind + 2 * (mid - l + 1)]);
	}

	void upd(int ul, int ur, ty uval){
		upd(uval, ul, ur, 0, 0, tam - 1);
	}

	void prop(int ind, int l, int r){
		ll mid = (l + r) >> 1;
		if (laz[ind]){
			if (l != r){
				laz[ind + 1] += laz[ind];
				laz[ind + 2 * (mid - l + 1)] += laz[ind];
			}

			v[ind] += (r - l + 1) * laz[ind];
			laz[ind] = 0;
		}
	}

	// global oper
	ty oper(ty v1, ty v2){
		return (v1 + v2);
	}
};



// ST Recursivo Pointers
struct nodeSt {
    nodeSt *left, *right;
    ll l, r, val;

    nodeSt(vl &v, ll lef, ll rig) : l(lef), r(rig) {
        ll m = (l + r) / 2;

        if (l != r) {
            left = new nodeSt(v, lef, m);
            right = new nodeSt(v, m + 1, rig);
            val = oper(left->val, right->val);
        } else {
            val = v[l];
        }
    }

    ll get(ll i, ll j) {
        if (l >= i && r <= j) {
            return val;
        }
        if (l > j || r < i) {
            return 0; // nullval
        }

        return oper(left->get(i, j), right->get(i, j));
    }

    void actl(ll k, ll u) {
        if (l > k || r < k) return;
        if (l == k && r == k) {
            val = u;
            return;
        }

        left->actl(k, u);
        right->actl(k, u);

        val = oper(left->val, right->val);
    }

    ll oper(ll n1, ll n2) {
        return n1 + n2;
    }
};


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << setprecision(20)<< fixed;
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);

    
}