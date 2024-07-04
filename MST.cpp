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

struct DSU{
    vl parents,sizes;
    ll cantSets;
    ll maxSz;
 
    DSU(ll sz){
        parents.assign(sz, 0);
        sizes.assign(sz, 1);
        cantSets=sz;
        maxSz=1;
        for (int i = 0; i < sz; i++) parents[i] = i;}
 
    ll findSet(ll v){
        if (v == parents[v]) return v;
        return parents[v] = findSet(parents[v]);
    }
 
    bool isSameSet(ll i, ll j){
        return findSet(i) == findSet(j);
    }
 
    void unionSets(ll a, ll b){
        a = findSet(a);
        b = findSet(b);
        if (a != b) {
            if (sizes[a] < sizes[b]) swap(a, b);
            parents[b] = a;
            sizes[a] += sizes[b];
            maxSz = max(maxSz, sizes[a]);
            cantSets--;
        }
    }
};

ll kruskal(vector<pair<int, pll>>& edges, ll n){
    // edge = {peso, {u, v}}
    // n = vertices

    sort(all(edges));

    ll mstW = 0;
    ll mstS = 0;
    DSU dsu(n); 
    for(int i = 0; i < edges.size() && mstS < n - 1; i++){
        pair<int, pll> act = edges[i];
        if (!dsu.isSameSet(act.ss.ff, act.ss.ss)){
            dsu.unionSets(act.ss.ff, act.ss.ss);
            mstW += act.ff;
            mstS++;
        }
    }

    // -1 si es imposible conectar todos los componentes
    return (dsu.cantSets == 1 ? mstW : -1);
    
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << setprecision(20)<< fixed;
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);

    vector<pair<int, pll>> edges;

    ll n, m; cin >> n >> m;

    forx(i, m){
        ll u, v, c; cin >> u >> v >> c;
        u--; v--;
        edges.pb({c, {u, v}});
    }

    ll ans = kruskal(edges, n);
    if (ans == -1) cout << "IMPOSSIBLE" << ln;
    else cout << ans << ln;

    
}