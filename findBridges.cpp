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

vvl graf;
vl tin, low, vis0;
ll tim;
set<pll> bridges;

void dfsB(ll u, ll p = -1){
    vis0[u] = 1;
    tin[u] = low[u] = tim++;

    for(int v : graf[u]){
        // no tenemos en cuenta multi-edges
        if (v == p) continue;

        if (vis0[v]) low[u] = min(low[u], tin[v]);
        else{
            dfsB(v, u);
            low[u] = min(low[u], low[v]);
            if (tin[u] < low[v]){
                bridges.insert({u, v});
                bridges.insert({v, u});
            }
        }
    }
}

void findBridges(ll n){
    bridges.clear();
    tin.assign(n, -1);
    low.assign(n, -1);
    vis0.assign(n, 0);
    tim = 0;

    for(int i = 0; i < n; i++){
        if (!vis0[i]) dfsB(i);
    }
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << setprecision(20)<< fixed;
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);

    ll t; cin >> t;
    while(t--){
        ll n, m; cin >> n >> m;
        
        graf.assign(n, vl());
        forx(i, m){
            ll u, v; cin >> u >> v;
            u--; v--;
            graf[u].pb(v);
            graf[v].pb(u);
        }

        findBridges(n);

    }
}