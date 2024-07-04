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

// O(N log log N)
ll sieve_size;
bitset<10000010> bs; //10^7 lim aprox
vl p;                   
void sieve(ll upper) {        
    sieve_size = upper + 1;    
    bs.set();                     
    bs[0] = bs[1] = 0;             
    for (ll i = 2; i < sieve_size; ++i){
        if (bs[i]){
            for(ll j = i * i; j < sieve_size; j += i) bs[j] = 0;
            p.push_back(i);  
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << setprecision(20)<< fixed;
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);

    ll lim = 1e6 + 1;
    sieve(lim);

}