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

// Trie recursivo
struct TrieNode {
	map<char, TrieNode*> children;
	bool endofword;
    
	TrieNode(){
		endofword = false;
	}

    void insert(string word){
        TrieNode *current = this;
        for(int i = 0; i < word.size(); i++){
            char ch = word[i];
            TrieNode *node = current -> children[ch];

            if(!node){
                node = new TrieNode();
                current -> children[ch] = node;
            }

            current = node;
        }

        current -> endofword = true;
    }

    bool search(string word){
        TrieNode *current = this;
        for(int i=0; i < word.size(); i++){
            char ch = word[i];
            
            TrieNode *node = current -> children[ch];
            
            if(!node) return false;
            
            current = node;
        }

        return current -> endofword;
    }

    bool remove(string word, int depth = 0) {
        if (depth == word.size()) {
            if (!endofword) return false;
            endofword = false;
            return children.empty();
        }

        char ch = word[depth];
        TrieNode *node = children[ch];
        if (!node) return false;

        bool shouldDeleteChild = node -> remove(word, depth + 1);

        if (shouldDeleteChild) {
            delete node;
            children.erase(ch);
            return children.empty() && !endofword;
        }

        return false;
    }
};

// Trie tabular
struct node{
    int childs[27];
    node(){
        memset(childs, -1, sizeof childs);
    }
};

struct TrieNode {
	vector<node> nds;
	vi endofword;
    
	TrieNode(){
		nds.pb(node());	
        endofword.pb(0);
    }

    void insert(string word){
        int cur = 0;
        for(int i = 0; i < word.size(); i++){
            int ch = word[i] - 'a';
            if(nds[cur].childs[ch] == -1){
                nds[cur].childs[ch] = nds.size();
                nds.pb(node());
                endofword.pb(0);
            }
            cur = nds[cur].childs[ch];
        }
        endofword[cur]++;
    }

    int search(string word){
        int cur = 0;
        for(int i = 0; i < word.size(); i++){
            int ch = word[i] - 'a';
            if(nds[cur].childs[ch] == -1) return 0;
            cur = nds[cur].childs[ch];
        }
        return endofword[cur];
    }

    void remove(string word) {
        int cur = 0;
        for(int i = 0; i < word.size(); i++){
            int ch = word[i] - 'a';
            if(nds[cur].childs[ch] == -1) return;
            cur = nds[cur].childs[ch];
        }
        endofword[cur]--; 
    }
};

// TrieBit recursivo
struct TrieBit{
    TrieBit* children[2];
	int passNums;
    
	TrieBit(){
        children[0] = children[1] = NULL;
		passNums = 0;
	}

    void insert(int num){
        TrieBit *current = this;
        for(int i = 30; i >= 0; i--){
            bool bit = (num >> i) & 1;
            TrieBit *node = current -> children[bit];

            if(!node){
                node = new TrieBit();
                current -> children[bit] = node;
            }

            current -> passNums++;
            current = node;
        }

        current -> passNums++;
    }

    void remove(int num){   
        TrieBit *current = this;
        for(int i = 30; i >= 0; i--){
            bool bit = (num >> i) & 1;
            TrieBit *node = current -> children[bit];
            current -> passNums--;
            current = node;
        }

        current -> passNums--;
    }

    int maxXor(int num, int alt = 30){

        TrieBit *current = this;
        bool bit = (num >> alt) & 1;

        TrieBit *node1 = current -> children[!bit];
        TrieBit *node2 = current -> children[bit];

        if (node1 && (node1 -> passNums)){
            return (1 << alt) + node1 -> maxXor(num, alt - 1);
        }

        if (node2 && (node2 -> passNums)){
            return node2 -> maxXor(num, alt - 1);
        }

        return 0;
        
    }

    void mergeTries(TrieBit *oTrie){
		for(int i = 0; i <= 1; i++){
			if (oTrie -> children[i]){
				if (children[i]){
					children[i] -> mergeTries(oTrie -> children[i]);
				}else{
					children[i] = oTrie -> children[i];
				}
			}
		}
	}
};


// TrieBit tabular
struct node{
  int childs[2]{-1, -1};
};

struct TrieBit{
    vector<node> nds;
	vi passNums;
    
	TrieBit(){
        nds.pb(node());
        passNums.pb(0);
	}

    void insert(int num){
        int cur = 0;
        for(int i = 30; i >= 0; i--){
            bool bit = (num >> i) & 1;

            if(nds[cur].childs[bit] == -1){
                nds[cur].childs[bit] = nds.size();
                nds.pb(node());
                passNums.pb(0);
            }

            passNums[cur]++;
            cur = nds[cur].childs[bit];
        }

        passNums[cur]++;
    }

    void remove(int num){   
        int cur = 0;
        for(int i = 30; i >= 0; i--){
            bool bit = (num >> i) & 1;
            passNums[cur]--;
            cur = nds[cur].childs[bit];
        }

        passNums[cur]--;
    }

    int maxXor(int num){
        int ans = 0;
        int cur = 0;
        for(int i = 30; i >= 0; i--){
            bool bit = (num >> i) & 1;

            int n1 = nds[cur].childs[!bit]; 
            if (n1 != -1 && passNums[n1]){
                ans += (1 << i);
                bit = !bit;
            }

            cur = nds[cur].childs[bit];
        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << setprecision(20)<< fixed;
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);

    TrieNode trie;
    trie.insert("hola");
    trie.insert("hola123");
    trie.insert("hola12345");
    trie.insert("hola");
    trie.insert("accepted");

    cout << trie.search("hola12345") << ln;

    trie.remove("hola12345");

    cout << trie.search("hola12345") << ln;

    trie.insert("hola12345");

    cout << trie.search("hola") << ln;
    cout << trie.search("hola123") << ln;
    cout << trie.search("hola12345") << ln;

    
}