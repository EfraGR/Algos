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

const int MAXN = 1e5;
const int K = 22; // log2(MAXN)
int spt[K + 1][MAXN];

int oper(int v1, int v2){
	return min(v1, v2);
}

// O(nlogn)
void buildSpt(vector<int>& arr){
	copy(arr.begin(), arr.end(), spt[0]);
	
	for(int i = 1; i <= K; i++){
		for(int j = 0; j + (1 << i) <= arr.size(); j++){
			spt[i][j] = oper(spt[i - 1][j], spt[i - 1][j + (1 << (i - 1))]);
		}
	}
}

// O(K)
ll getAns(int l, int r){
	ll ans = -1;
	for (int i = K; i >= 0; i--) {
		if ((1 << i) <= r - l + 1) {
            if (ans == -1) ans = spt[i][l];
            else ans = oper(ans, spt[i][l]);
			l += 1 << i;
		}
	}

	return ans;
}

// O(1) idempotent functions
ll getMin(int l, int r){
    int log = __builtin_clzll(1) - __builtin_clzll(r - l + 1);
	return oper(spt[log][l], spt[log][r - (1 << log) + 1]);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cout << setprecision(20)<< fixed;
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);

	vi nums = {4, 2, 3, 7, 1, 5, 3, 3, 9, 6, 7, -1, 4};

	buildSpt(nums);

	cout << getAns(0, 11) << ln; 
	cout << getMin(0, 10) << ln;

	for(int i = 0; i <= 3; i++){
		for(int j = 0; j < nums.size(); j++){
			cout << spt[i][j] << " ";
		}
		cout << ln;
	}
}