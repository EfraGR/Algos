using namespace std;
#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define ff first
#define ss second
#define pb push_back
#define forx(i,n) for(int i=0; i<(int)n; ++i)
#define printF(x) for(auto &w : x) {cout << w << " ";} cout << endl;
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<vl> vvl;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef priority_queue<ll> pqll;
const char ln = '\n';
const int MOD = 1e9+7;
const ll inf  = LONG_LONG_MAX;
const string abc = "abcdefghijklmnopqrstuvwxyz";
int dirx[4] = {0,-1,1,0};
int diry[4] = {-1,0,0,1};

// LCA Binary Lifting
vvl tree;
vl deep;

vvl up; // up[i][j] = 2^j -th ancestor of the node i
ll LOG = 20; // log of tree depth
void binLif(ll ini){
	for(int hijo : tree[ini]){
		deep[hijo] = deep[ini] + 1;

		up[hijo][0] = ini;
		for(int i = 1; i < LOG; i++){
			up[hijo][i] = up[up[hijo][i - 1]][i - 1];
		} 

		binLif(hijo);
	}
}

ll LCA(ll u, ll v){
	if (deep[u] < deep[v]) swap(u, v);

	ll dif = deep[u] - deep[v];
	for(int b = LOG - 1; b >= 0; b--){
		if (dif & (1 << b)){
			u = up[u][b];
		}
	}

	for(int b = LOG - 1; b >= 0; b--){
		if (up[u][b] != up[v][b]){
			u = up[u][b];
			v = up[v][b];
		}
	}

	return (u == v ? u : up[u][0]);
}


int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cout << setprecision(20)<< fixed;
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);

	ll n, q; cin >> n >> q;
	
	tree.assign(n, vl());

	forx(i, n - 1){
		ll val; cin >> val;
		tree[val - 1].pb(i + 1);
	}

	up.assign(n, vl(LOG, 0));
	deep.assign(n, 0);

	binLif(0);

	while(q--){
		ll u, v; cin >> u >> v;
		cout << LCA(u - 1, v - 1) + 1 << ln;
	}
}

// LCA Euler Tour ST
// vvl tree;
// vl tur;
// vl fir;
// vl h;
// void eulerT(ll ini = 0, ll alt = 0, ll p = -1){
//     tur.pb(ini);
//     h.pb(alt);
//     fir[ini] = tur.size() - 1;
 
//     for(ll hijo : tree[ini]){
//         if (hijo != p){
//             eulerT(hijo, alt + 1, ini);
//             tur.pb(ini);
//             h.pb(alt);
//         }
//     }
 
// }

// struct nodeSt {
//     nodeSt *left, *right;
//     ll l, r;
//     pll val;
 
//     nodeSt(vl &v, ll lef, ll rig) : l(lef), r(rig) {
//         ll m = (l + r) / 2;
 
//         if (l != r) {
//             left = new nodeSt(v, lef, m);
//             right = new nodeSt(v, m + 1, rig);
//             val = oper(left->val, right->val);
//         } else {
//             val = {v[l], l};
//         }
//     }
 
//     pll get(ll i, ll j) {
//         if (i > j) swap(i, j);

//         if (l >= i && r <= j) {
//             return val;
//         }
//         if (l > j || r < i) {
//             return {inf, -1};
//         }
 
//         return oper(left->get(i, j), right->get(i, j));
//     }
 
//     pll oper(pll n1, pll n2) {
//         return min(n1, n2);
//     }
// };
 