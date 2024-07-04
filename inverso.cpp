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


ll mod(ll a, ll m){
    return ((a % m) + m) % m;
}

ll binpow(ll b, ll n, ll m) {
    b %= m;
    ll res = 1;
    while (n > 0) {
        if (n & 1)
            res = res * b % m;
        b = b * b % m;
        n >>= 1;
    }
    return res % m;
}


ll inv (ll a){
    return binpow(a, MOD-2, MOD);
}