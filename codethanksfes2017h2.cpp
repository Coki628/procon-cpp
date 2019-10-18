/**
 * ・蟻本演習2-4-3
 * ・LCA、ダブリング
 * ・AC0.1秒。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> tlii;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define all(obj) (obj).begin(), (obj).end()
#define pb push_back
#define str to_string
#define mkp make_pair
#define mkt make_tuple
// #define print(out) cout << (out) << endl
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
void chmax(ll &a, ll b) { a = max(a, b); }
void chmin(ll &a, ll b) { a = min(a, b); }
void chmax(int &a, int b) { a = max(a, b); }
void chmin(int &a, int b) { a = min(a, b); }

template<typename Any>
void print(Any out) {
    cout << out << '\n';
}

void print(vector<ll> A) {
    rep(i, 0, A.size()) {
        cout << A[i];
        cout << (i == A.size()-1 ? '\n' : ' ');
    }
}

ll max(vector<ll> A) {
    ll res = -INF;
    for (ll a: A) chmax(res, a);
    return res;
}

ll min(vector<ll> A) {
    ll res = INF;
    for (ll a: A) chmin(res, a);
    return res;
}

struct UnionFind {

    int n;
    vector<int> par, rank, size;

    UnionFind(int n) : n(n) {
        par.resize(n+1);
        rank.resize(n+1);
        size.resize(n+1, 1);
        rep(i, 0, n+1) par[i] = i;
    }

    UnionFind() {}

    // 根の検索(グループ番号)
    int find(int x) {
        // 根ならその番号を返す
        if (par[x] == x) {
            return x;
        } else {
            // 走査していく過程で親を書き換える
            par[x] = find(par[x]);
            return par[x];
        }            
    }

    // 併合
    void merge(int a, int b) {
        // 根を探す
        int x = find(a);
        int y = find(b);
        // 木の高さを比較し、低いほうから高いほうに辺を張る
        if (rank[x] < rank[y]) {
            par[x] = y;
            size[y] += size[x];
        } else {
            par[y] = x;
            size[x] += size[y];
            // 木の高さが同じなら片方を1増やす
            if (rank[x] == rank[y]) {
                rank[x] += 1;
            }
        }
    }

    // 同じ集合に属するか判定
    bool is_same(int a, int b) {
        return find(a) == find(b);
    }

    // あるノードの属する集合のノード数
    int get_size(int x) {
        return size[find(x)];
    }
};

int N, M, Q, a, b, gap, mx, x, y;
UnionFind uf;
vector<vector<pii>> nodes;
vector<int> depths;
vector<bool> visited;
// nxt[k][v] := 頂点vから2^k遡った祖先の頂点
int nxt[17][100007];
// cost[k][v] := 頂点vから2^k遡った祖先に至るまでの辺の最大コスト
int cost[17][100007];

void dfs(int u, int prev, int depth, int prevc) {
    visited[u] = true;
    depths[u] = depth;
    nxt[0][u] = prev;
    // 自分の親への辺のコスト
    cost[0][u] = prevc;
    for (pii node : nodes[u]) {
        int v = node.first, c = node.second;
        if (prev != v) {
            dfs(v, u, depth+1, c);
        }
    }
}

// ここではLCAの頂点ではなく、そこまでの最大コストを返す
int get_lca(int a, int b) {
    // 深い方をbにする
    if (depths[a] > depths[b]) {
        swap(a, b);
    }
    // bをaと同じ高さまで持ってくる
    gap = depths[b] - depths[a];
    mx = 0;
    rep(k, 0, 17) {
        // ビットの立っている所を辿れば、好きな高さに移動できる
        if (gap>>k & 1) {
            // 最大コストの取得
            chmax(mx, cost[k][b]);
            b = nxt[k][b];
        }
    }
    // この時点で一致すればそこがLCA
    if (a == b) {
        return mx;
    }
    // aとbが一致する直前の高さまで持ってくる
    rrep(k, 16, -1) {
        if (nxt[k][a] != nxt[k][b]) {
            // 最大コストの取得
            chmax(mx, cost[k][a]);
            chmax(mx, cost[k][b]);
            a = nxt[k][a];
            b = nxt[k][b];
        }
    }
    // 元々直前の高さだった場合、1度もmaxを取らないのでここで取る
    if (a != b) {
        chmax(mx, cost[0][a]);
        chmax(mx, cost[0][b]);
    }
    return mx;
}   

int main() {

    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> M;
    nodes.resize(N);
    uf = UnionFind(N);
    depths.resize(N, -1);
    visited.resize(N, false);
    memset(nxt, -1, sizeof(nxt));
    memset(cost, -1, sizeof(cost));
    // 辺が追加された時系列iを辺のコストとする
    rep(i, 0, M) {
        cin >> a >> b;
        a--;
        b--;
        if (!uf.is_same(a, b)) {
            uf.merge(a, b);
            // (次の頂点, 辺のコスト)
            nodes[a].pb(mkp(b, i+1));
            nodes[b].pb(mkp(a, i+1));
        }
    }

    // 木ではなく森なので、全頂点からやって各木を探索しておく
    rep(i, 0, N) {
        if (!visited[i]) {
            dfs(i, -1, 0, -1);
        }
    }

    // ダブリングのテーブル構築
    rep(k, 1, 17) {
        rep(v, 0, N) {
            // 遡った頂点が根なら、それ以上先はないので-1のまま
            if (nxt[k-1][v] != -1) {
                nxt[k][v] = nxt[k-1][nxt[k-1][v]];
                // ひとつ前と遡った頂点から最大を取る
                cost[k][v] = max(cost[k-1][v], cost[k-1][nxt[k-1][v]]);
            }
        }
    }

    cin >> Q;
    rep(i, 0, Q) {
        cin >> x >> y;
        x--;
        y--;
        if (uf.is_same(x, y)) {
            print(get_lca(x, y));
        } else {
            print(-1);
        }
    }
}
