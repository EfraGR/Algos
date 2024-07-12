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

// Se divide en tres casos:

// Caso 1:

// - Me dan las pendientes ordenadas
// - Me hacen las querys ordenadas

// O(N + Q)

// Caso 2:

// - Me dan las pendientes ordenadas
// - Me hacen querys arbitrarias

// O(N + QlogN)

struct CHT {
    // funciona tanto para min como para max, depende del orden en que pasamos las lineas
    
    struct Line {
        int slope, yIntercept;

        Line(int slope, int yIntercept) : slope(slope), yIntercept(yIntercept) {}

        int val(int x) {
            return slope * x + yIntercept;
        }

        int intersect(Line y) {
            return (y.yIntercept - yIntercept + slope - y.slope - 1) / (slope - y.slope);
        }
    };

    deque<pair<Line, int>> dq;

    void insert(int slope, int yIntercept) { 
		// lower hull si m1 < m2 < m3
		// upper hull si si m1 > m2 > m3
        Line newLine(slope, yIntercept);

        while (!dq.empty() && dq.back().second >= dq.back().first.intersect(newLine))
            dq.pop_back();

        if (dq.empty()) {
            dq.emplace_back(newLine, 0);
            return;
        }

        dq.emplace_back(newLine, dq.back().first.intersect(newLine));
    }

    int query(int x) { // cuando las consultas son crecientes (modi para decrecientes)

        while (dq.size() > 1) {
            if (dq[1].second <= x) dq.pop_front();
            else break;
        }

        return dq[0].first.val(x);
    }

    int query2(int x) { // cuando son arbitrarias
        auto qry = *lower_bound(dq.rbegin(), dq.rend(),
                                make_pair(Line(0, 0), x),
                                [&](const pair<Line, int> &a, const pair<Line, int> &b) {
                                    return a.second > b.second;
                                });

        return qry.first.val(x);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << setprecision(20)<< fixed;
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);

    
}