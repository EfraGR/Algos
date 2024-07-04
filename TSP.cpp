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

ll n, ini;
vvl adj, dp;

ll tsp(){
    dp.assign(n, vl((1 << n), inf));

    for(int i = 0; i < n; i++){
        if (i == n) continue;
        dp[i][(1 << i) | (1 << ini)] = adj[ini][i];
    }

    for(int x = 0; x < (1 << n); x++){
        for(int next = 0; next < n; next++){
            
            if (!(x & (1 << next))) continue;

            for(int last = 0; last < n; last++){
                if (last == next || last == ini || !(x & (1 << last))) continue;

                ll op = dp[last][x ^ (1 << next)] + adj[last][next];
                dp[next][x] = min(dp[next][x], op);
            }
        }
    }

    ll ans = inf;
    for(int i = 0; i < n; i++){
        ans = min(ans, dp[i][(1 << n) - 1] + adj[i][0]);
    }
    
    return ans;
}

void build(vl& tour){
    tour.assign(n + 1, 0);

    ll lastInd = ini;
    ll mask = (1 << n) - 1;

    for(int i = n - 1; i >= 1; i--){
        ll ind = 0;

        for(int j = 0; j < n; j++){
            if (j == ini || !(mask & (1 << j))) continue;
            
            ll ant = dp[ind][mask] + adj[ind][lastInd];
            ll act = dp[j][mask] + adj[j][lastInd];

            if (act < ant) ind = j;
        }

        tour[i] = ind;
        mask ^= (1 << ind);
        lastInd = ind;
    }

    tour[0] = tour[n] = ini;
}



int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << setprecision(20)<< fixed;
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);

    ll t; cin >> t;
    while(t--){
        cin >> n;
        n++;
        vvl graf(n, vl(n, 0));

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if (i == j) continue;
                cin >> graf[i][j];
            }
        }

        ini = 0;
        adj = graf;
        cout << tsp() << ln;

        vl tour;
        build(tour);
        printF(tour);

        // !!! PROBAR, no lo he mandado a ninguno problema
    }
}