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

// O(|N+Q|*sqrt(|N|)*|ADD/DEL|)

struct query {
  int l, r, idx;
  query (int l, int r, int idx) : l(l), r(r), idx(idx) {}
};

vector<query> qs; // queries
vl vals; // values 
vl ans; // ans of queries
ll S; // size of blocks 

bool cmp (const query &a, const query &b) {
	int A = a.l/S, B = b.l/S;
	if (A != B) return A < B;
	return A & 1 ? a.r > b.r : a.r < b.r;
}

void del(ll idx){
	// implement del 
}

void add(ll idx){
	// implement add
}

int get_ans(){
	// implement get_ans
}

void MOs(){
	ll n = vals.size();
	S = sqrt(n);
	ans.assign(qs.size(), 0);
	sort(all(qs), cmp);

	int l = 0, r = -1;
	for (int i = 0; i < qs.size(); ++i) {
		while (r < qs[i].r) add(++r);
		while (l > qs[i].l) add(--l);
		while (r > qs[i].r) del(r--);
		while (l < qs[i].l) del(l++);
		ans[qs[i].idx] = get_ans();
	}
}


int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cout << setprecision(20)<< fixed;
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);

	
}