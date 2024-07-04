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

typedef int type;

// O(n + m) n: # variables m: # de clausuras
struct SAT2 {
    type n;
    vector<vector<vector<type>>> g;
    vector<type> tag;
    vector<bool> seen, value;
    stack<type> st;

    SAT2(type n): n(n), g(2, vector<vector<type>>(2 * n)), tag(2 * n), seen(2 * n), value(2 * n){}
   
    type neg(type x){return 2 * n - x - 1;}
    void add_or(type u, type v) {implication(neg(u), v);}
    void make_true(type u){add_edge(neg(u), u);}
    void make_false(type u){make_true(neg(u));}
    void diff(type u, type v){eq(u, neg(v));}
    void eq(type u, type v){
        implication(u, v);
        implication(v, u);
    }
    
    void implication(type u, type v){
        add_edge(u, v);
        add_edge(neg(v), neg(u));
    }

    void add_edge(type u, type v){
        g[0][u].push_back(v);
        g[1][v].push_back(u);
    }

    void dfs(type id, type u, type t = 0){
        seen[u] = true;
        for (auto& v : g[id][u])
            if (!seen[v]) dfs(id, v, t);
        if (id == 0)
            st.push(u);
        else
            tag[u] = t;
    }

    void kosaraju() {
        for (int u = 0; u < n; u++) {
            if (!seen[u]) dfs(0, u);
            if (!seen[neg(u)]) dfs(0, neg(u));
        }
        fill(seen.begin(), seen.end(), false);

        type t = 0;
        while (!st.empty()) {
            type u = st.top();
            st.pop();
            if (!seen[u]) dfs(1, u, t++);
        }
    }

    bool satisfiable() {
        kosaraju();
        for (int i = 0; i < n; i++) {
            if (tag[i] == tag[neg(i)]) return false;
            value[i] = tag[i] > tag[neg(i)];
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << setprecision(20) << fixed;
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);

    int n, m; cin >> n >> m;
    SAT2 sat2(m);

    forx(i, n){
        char ty1, ty2;
        int vl1, vl2;
        cin >> ty1 >> vl1 >> ty2 >> vl2;
        vl1--; vl2--;

        if (ty1 == '-') vl1 = sat2.neg(vl1);
        if (ty2 == '-') vl2 = sat2.neg(vl2);

        sat2.add_or(vl1, vl2);
    }

    bool pos = sat2.satisfiable();

    if (pos){
        forx(i, m) cout << (sat2.value[i] ? "+" : "-") << " ";
        cout << ln;
    }else{
        cout << "IMPOSSIBLE" << ln;
    }

}