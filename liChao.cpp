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

// inf max abs value that the function may take
typedef long long ty;

struct Line {
  ty m, b;

  Line(ll m, ll b): m(m), b(b){}
  Line(){}
  
  ty eval(ty x){return m * x + b;}

};

struct nLiChao{
	// see coments for min

	nLiChao *left = nullptr, *right = nullptr;
	ty l, r;
	Line line;

	nLiChao(ty l, ty r): l(l), r(r){
		line = {0, -inf}; // change to {0, inf};
	}

	// T(Log(Rango)) M(Log(rango))
	void addLine(Line nline){
		ty m = (l + r) >> 1;
		bool lef = nline.eval(l) > line.eval(l); // change > to <
    	bool mid = nline.eval(m) > line.eval(m); // change > to <

		if (mid) swap(nline, line);

		if (r == l) return;

    	if (lef != mid){
			if (!left){
				left = new nLiChao(l, m);
				left -> line = nline;
			}

			else left -> addLine(nline);
		}
    	else{
			if (!right){
				right = new nLiChao(m + 1, r);
				right -> line = nline;
			}

			else right -> addLine(nline);
		}
	}

	// T(Log(Rango))
	ty get(ty x) {
		ty m = (l + r) >> 1;
		ty op1 = -inf, op2 = -inf; // change to inf		

		if(l == r) return line.eval(x);
		else if(x < m){
			if (left) op1 = left -> get(x);
			return max(line.eval(x), op1); // change max to min
		} 
		else{
			if (right) op2 = right -> get(x);
			return max(line.eval(x), op2); // change max to min
		}
  	}
};


int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cout << setprecision(20)<< fixed;
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);

	// (rango superior) * (pendiente maxima) puede desbordarse
	// usar double o long double en el eval para estos casos 
	// (puede dar problemas de precision)
	nLiChao liChao(0, 1e18);

	liChao.addLine({1, -3});
	liChao.addLine({-3, 5});
	liChao.addLine({-1, 5});
	liChao.addLine({0, 3});

	cout << liChao.get(-2) << ln;
	cout << liChao.get(-1) << ln;
	cout << liChao.get(0) << ln;
	cout << liChao.get(1) << ln;
	cout << liChao.get(4) << ln;
	cout << liChao.get(9) << ln;

}