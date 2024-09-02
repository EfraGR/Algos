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

typedef long double lf;
const lf EPS = 1e-6;
const lf E0 = EPS; //Keep = 0 for integer coordinates, otherwise = EPS
const lf INF = 5e9;

// Puntos
struct pt {
	lf x,y;
	pt(){}
	pt(lf a , lf b): x(a), y(b){}

	pt operator - (const pt &q ) const {return {x - q.x , y - q.y };}
	pt operator + (const pt &q ) const {return {x + q.x , y + q.y };}
	pt operator * (const lf &t ) const {return {x * t , y * t };}
	pt operator / (const lf &t ) const {return {x / t , y / t };}
	bool operator == (pt b) { return x == b.x && y == b.y; }

	bool operator < (const pt & q) const {
		if(fabsl( x - q.x ) > E0) return x < q.x;
		return y < q.y;
	}
};

lf cross(pt p, pt q) {return p.x * q.y - q.x * p.y;}
lf dot(pt p, pt q) {return p.x * q.x + p.y * q.y;}
lf orient(pt a, pt b, pt c) {return cross(b - a, c - a);}

struct Halfplane{
  pt p, pq;
  lf angle;

  Halfplane() {}
  Halfplane(const pt& a, const pt& b) : p(a), pq(b - a) {
    angle = atan2l(pq.y, pq.x);
  }

  bool out(const pt& r) {
    return cross(pq, r - p) < -EPS;
  }

  bool operator < (const Halfplane& e) const {
    return angle < e.angle;
  }

  friend pt inter(const Halfplane& s, const Halfplane& t) {
      lf alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
      return s.p + (s.pq * alpha);
  }
};

vector<pt> hp_intersect(vector<Halfplane>& H) {
    pt box[4] = {pt(INF, INF), pt(-INF, INF), pt(-INF, -INF), pt(INF, -INF)};

    for(int i = 0; i < 4; ++i ) {
        Halfplane aux(box[i], box[(i+1) % 4]);
        H.push_back(aux);
    }

    sort(H.begin(), H.end());
    deque<Halfplane> dq;
    int len = 0;
    for(int i = 0; i < int(H.size()); ++i){
        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
            dq.pop_back();
            --len;
        }

        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front();
            --len;
        }

        if (len > 0 && fabsl(cross(H[i].pq, dq[len-1].pq)) < EPS ) {
            if (dot(H[i].pq, dq[len-1].pq) < 0.0) return vector<pt>();

            if (H[i].out(dq[len-1].p)){
                dq.pop_back();
                --len;
            }
            else continue;
        }

        dq.push_back(H[i]);
        ++len;
    }

    while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))){
        dq.pop_back();
        --len;
    }

    while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))){
        dq.pop_front();
        --len;
    }

    if (len < 3) return vector<pt>();

    vector<pt> ret(len);
    for(int i = 0; i+1 < len; ++i ){
        ret[i] = inter(dq[i], dq[i+1]);
    }
    ret.back() = inter(dq[len-1], dq[0]);
    //remove repeated points if needed
    return ret;
}
