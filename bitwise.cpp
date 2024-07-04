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

// retorna el siguiente bit con la misma cantidad encendida
ll nextMask(ll x){
    ll c = x & -x;
    ll r = x + c;
    return (((r ^ x) >> 2) / c) | r;
}

// F[mask] = sumatoria de todas las A[sub-mask]
void SOS(ll N, vl& A){
    vl F((1 << N), 0);

    for(int i = 0; i < (1 << N); ++i)
	F[i] = A[i];

    for(int i = 0; i < N; ++i){
        for(int mask = 0; mask < (1<<N); ++mask){
            if(mask & (1<<i)){
                F[mask] += F[mask^(1<<i)];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << setprecision(20)<< fixed;
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);

    ll lim = (1 << 5) - 1;

    ll x = (1 << 3) - 1;
    while(x < lim){
        bitset<10> bit3(x);

        cout << bit3 << ln;

        x = nextMask(x);
    }
}