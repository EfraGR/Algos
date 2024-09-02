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

const int intM = 1e5 + 2;

vi graf[intM];

int szs[intM];
void dfs(int ini = 0, int p = -1){
    szs[ini] = 1;
    for(int child : graf[ini]){
        if (child != p){
            dfs(child, ini);
            szs[ini] += szs[child];
        }
    }
}

int cnt[intM]; // ED global

void add(int v, int x){
    // Implementar add/del de nodo
    return;
}

vector<int> ansF;
vector<pii> qs[intM];
void ans(int v){
    // Implementar respuesta a querys
    return;
}

vi vs[intM];
void solve(int ini = 0, int p = -1, bool keep = 1){
    int bigC = -1;
    int bigS = 0;

    for(int child : graf[ini]){
        if (child == p || szs[child] < bigS) continue;
        bigS = szs[child];
        bigC = child;
    }

    for(int child : graf[ini]){
        if (child == p || child == bigC) continue;
        solve(child, ini, 0);
        
    }

    if(bigC != -1){
        solve(bigC, ini, 1);
        swap(vs[bigC], vs[ini]);
    }

    vs[ini].pb(ini);
    add(ini, 1);

    for(int child : graf[ini]){
        if (child == p && child == bigC) continue;
        for(int nd : vs[child]){
            vs[ini].pb(nd);
            add(nd, 1);
        }
    }

    ans(ini);

    if (!keep){
        for(int nd : vs[ini]){
            add(nd, -1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << setprecision(20)<< fixed;
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);

    
}