using namespace std;
#include <bits/stdc++.h>

typedef long double lf;
const lf EPS = 1e-8L;
const lf E0 = 0.0L; //Keep = 0 for integer coordinates, otherwise = EPS
const lf INF = 5e9;

enum {OUT,IN,ON};

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
lf orient(pt a, pt b, pt c) {return cross(b - a, c - a);}
lf norm2 (pt p){return p.x * p.x + p.y * p.y;}
bool half(pt p){return p.y > 0 || (p.y == 0 && p.x < 0);}
lf dot(pt p, pt q) {return p.x * q.x + p.y * q.y;}

// polar sort
bool polar_cmp(const pt &a, const pt &b) {
  return make_tuple(half(a), 0) < make_tuple(half(b), cross(a,b));
}

 
void polar_sort(vector<pt> &v, pt o) { // sort points in counterclockwise with respect to point o
    sort(v.begin(), v.end(), [&](pt a,pt b) {
        return make_tuple(half(a - o), 0.0, norm2((a - o))) < make_tuple(half(b - o), cross(a - o, b - o), norm2((b - o)));
    });
}

// Poligonos
int point_in_convex_polygon(const vector<pt> &pol, const pt &p) {
	// El poligono debe estar en anti - horario
	// Eliminar puntos colineales
	int low = 1, high = pol.size() - 1;
	while(high - low > 1){
		int mid = (low + high) / 2;
		if(orient(pol[0], pol[mid], p) >= -E0) low = mid;
		else high = mid;
	}
	if(orient(pol[0], pol[low], p) < -E0) return OUT;
	if(orient(pol[low], pol[high], p) < -E0) return OUT;
	if(orient(pol[high], pol[0], p) < -E0) return OUT;

	if(low == 1 && orient(pol[0], pol[low], p) <= E0) return ON;
	if(orient(pol[low], pol[high], p) <= E0) return ON;
	if(high == (int) pol.size() -1 && orient(pol[high], pol[0], p) <= E0) return ON;
	return IN;	
}

vector<pt> minkowski(vector<pt> P, vector<pt> Q) {
	rotate(P.begin(), min_element(P.begin(), P.end()), P.end());
	rotate(Q.begin(), min_element(Q.begin(), Q.end()), Q.end());

	P.push_back(P[0]), P.push_back(P[1]);
	Q.push_back(Q[0]), Q.push_back(Q[1]);

	vector<pt> ans; 
	size_t i = 0, j = 0;
	while(i < P.size() - 2 || j < Q.size() - 2) {
		ans.push_back(P[i] + Q[j]);
		lf dt = cross( P[i + 1] - P[i], Q[j + 1] - Q[j]);
		if(dt >= E0 && i < P.size() - 2) ++i;
		if(dt <= E0 && j < Q.size() - 2) ++j;
	}
	return ans;
}

void convex_hull(vector<pt>& p) {
	sort(p.begin(), p.end());
	vector<pt> ch;
	ch.reserve(p.size()+1);
	for (int it = 0; it < 2; it++) {
		int start = ch.size();
		for (auto &a : p) {
			// if colineal are needed, use < and remove repeated points
			while (ch.size() >= start+2 && orient(ch[ch.size()-2], ch.back(), a) <= 0) 
				ch.pop_back();
			ch.push_back(a);
		}
		ch.pop_back();
		reverse(p.begin(), p.end());
	}
	if (ch.size() == 2 && ch[0] == ch[1]) ch.pop_back();
	// be careful with CH of size < 3
	p.swap(ch);
}

int point_in_polygon(const vector<pt> &pol, const pt &p) {
  int wn = 0;
  for(int i = 0, n = pol.size(); i < n; ++i) {
    lf c = orient(p, pol[i], pol[(i + 1)%n]);
    if(fabsl(c) <= E0 && dot(pol[i] - p, pol[(i + 1)%n] - p) <= E0) return ON;
    if(c > 0 && pol[i].y <= p.y + E0 && pol[(i + 1)%n].y - p.y > E0) ++wn;
    if(c < 0 && pol[(i + 1)%n].y <= p.y + E0 && pol[i].y - p.y > E0) --wn;
  }
  return wn ? IN : OUT;
}
