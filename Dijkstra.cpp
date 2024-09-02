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

// O ((V+E)*log V)
typedef vector<pii> vii;
vi dijkstra(vector<vii> &graf, int s){
    vi dist(graf.size(), INT_MAX); 
    dist[s] = 0;
    priority_queue<pii, vii, greater<pii>> pq; 
    pq.push({0, s});
    while(!pq.empty()){
        pii front = pq.top(); pq.pop();
        int d = front.ff;
        int u = front.ss;
        if (d > dist[u]) continue;

        for (pii node : graf[u]){
            if (dist[u] + node.ss < dist[node.ff]){
                dist[node.ff] = dist[u] + node.ss;
                pq.push({dist[node.ff], node.ff});
            }
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << setprecision(20)<< fixed;
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);

    
}