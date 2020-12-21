#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define list2d(name, N, M, type, init) vector<vector<type>> name(N, vector<type>(M, init))
constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

template<typename T> inline bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> inline bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

ll sum(vector<ll> A) { ll res = 0; for (ll a: A) res += a; return res; }
ll max(vector<ll> A) { ll res = -INF; for (ll a: A) chmax(res, a); return res; }
ll min(vector<ll> A) { ll res = INF; for (ll a: A) chmin(res, a); return res; }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }


// ダイクストラ(テンプレートで小数コストも対応)
template<typename T>
vector<T> dijkstra(vector<vector<pair<ll, T>>> nodes, int src) {

    ll N = nodes.size();
    vector<T> res(N, INF);
    priority_queue<pair<T, ll>, vector<pair<T, ll>>, greater<pair<T, ll>>> que;
    res[src] = 0;
    que.push(mkp(0, src));

    pair<T, ll> p;
    T dist, cost;
    int cur, nxt;
    while(!que.empty()) {
        p = que.top(); que.pop();
        dist = p.first;
        cur = p.second;
        if (res[cur] < dist) {
            continue;
        }
        for (auto p: nodes[cur]) {
            nxt = p.first;
            cost = p.second;
            if (dist + cost < res[nxt]) {
                res[nxt] = dist + cost;
                que.push(mkp(dist+cost, nxt));
            }
        }
    }
    return res;
}


template<typename T>
vector<vector<T>> warshall_floyd(vector<vector<T>> G) {
    ll N = G.size();
    rep(i, 0, N) G[i][i] = 0;
    rep(k, 0, N) {
        rep(i, 0, N) {
            rep(j, 0, N) {
                chmin(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
    rep(i, 0, N) {
        if (G[i][i] < 0) {
            return {};
        }
    }
    return G;
}


struct UnionFind {

    int n, groupcnt;
    vector<int> par, rank, size;

    UnionFind(int n) : n(n) {
        par.resize(n);
        rank.resize(n);
        size.resize(n, 1);
        rep(i, 0, n) par[i] = i;
        groupcnt = n;
    }

    UnionFind() {}

    void resize(int _n) {
        n = _n;
        par.resize(n);
        rank.resize(n);
        size.resize(n, 1);
        rep(i, 0, n) par[i] = i;
        groupcnt = n;
    }

    // 根の検索(グループ番号)
    int find(int x) {
        if (par[x] == x) {
            return x;
        } else {
            par[x] = find(par[x]);
            return par[x];
        }            
    }

    // 併合
    void merge(int a, int b) {
        int x = find(a);
        int y = find(b);
        if (x == y) return;
        groupcnt--;
        if (rank[x] < rank[y]) {
            par[x] = y;
            size[y] += size[x];
        } else {
            par[y] = x;
            size[x] += size[y];
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

    // 集合の数
    int get_size() {
        return groupcnt;
    }
};


struct PartiallyPersistentUnionFind {

    int n;
    vector<int> par, last;

    PartiallyPersistentUnionFind(int n) : n(n) {
        // xが根のときはxを含むグループのサイズ(の-1倍)、そうでないときは親ノード
        par.resize(n+1, -1);
        // 最後に「根」ではなくなった瞬間の時刻
        last.resize(n+1, -1);
    }

    PartiallyPersistentUnionFind() {}

    // 根の検索(グループ番号)
    int find(int t, int x) {
        // 根ならその番号を返す
        if (last[x] == -1 || t < last[x]) {
            return x;
        } else {
            return find(t, par[x]);
        }
    }

    // 併合
    bool merge(int t, int a, int b) {
        // 根を探す
        int x = find(t, a);
        int y = find(t, b);
        if (x == y) {
            return false;
        }
        // 要素数の少ない方を付け替える(マージテク)
        if (par[x] > par[y]) {
            swap(x, y);
        }
        // xにyを付ける
        par[x] += par[y];
        par[y] = x;
        last[y] = t;
        return true;
    }

    // 同じ集合に属するか判定
    bool is_same(int t, int a, int b) {
        return find(t, a) == find(t, b);
    }
};


// 全方位木DP
template<typename sum_t, typename key_t>
struct ReRooting {
    struct Edge {
        int to;
        key_t data;
        sum_t dp, ndp;
    };

    using F1 = function<sum_t(sum_t, sum_t)>;
    using F2 = function<sum_t(sum_t, key_t)>;

    vector<vector<Edge>> g;
    vector<sum_t> subdp, dp;
    const sum_t ident;
    const F1 f1;
    const F2 f2;

    ReRooting(int V, const F1 f1, const F2 f2, const sum_t &ident)
        : g(V), f1(f1), f2(f2), ident(ident), subdp(V, ident), dp(V, ident) {}

    void add_edge(int u, int v, const key_t &d) {
        g[u].emplace_back((Edge) {v, d, ident, ident});
        g[v].emplace_back((Edge) {u, d, ident, ident});
    }

    void add_edge_bi(int u, int v, const key_t &d, const key_t &e) {
        g[u].emplace_back((Edge) {v, d, ident, ident});
        g[v].emplace_back((Edge) {u, e, ident, ident});
    }

    void dfs_sub(int idx, int par) {
        for(auto &e : g[idx]) {
        if(e.to == par) continue;
        dfs_sub(e.to, idx);
        subdp[idx] = f1(subdp[idx], f2(subdp[e.to], e.data));
        }
    }

    void dfs_all(int idx, int par, const sum_t &top) {
        sum_t buff{ident};
        for(int i = 0; i < (int) g[idx].size(); i++) {
        auto &e = g[idx][i];
        e.ndp = buff;
        e.dp = f2(par == e.to ? top : subdp[e.to], e.data);
        buff = f1(buff, e.dp);
        }
        dp[idx] = buff;
        buff = ident;
        for(int i = (int) g[idx].size() - 1; i >= 0; i--) {
        auto &e = g[idx][i];
        if(e.to != par) dfs_all(e.to, idx, f1(e.ndp, buff));
        e.ndp = f1(e.ndp, buff);
        buff = f1(buff, e.dp);
        }
    }

    vector<sum_t> build() {
        dfs_sub(0, -1);
        dfs_all(0, -1, ident);
        return dp;
    }
};


// HD分解
// ・主な使用方法など列挙
// 　・初期化後、忘れずにbuildを呼ぶこと。
// 　・パスクエリはadd,queryで処理
// 　・1点取得/更新はhld.in[x]で可能。add,queryは呼ばなくていい。
// 　・部分木クエリは[hld.in[x],hld.out[x])で処理
// 　・根付き木は頂点0が根である前提。他の頂点を根にしたい場合、
// 　　HLD構築前に根と頂点0の関係を全てスワップしておく。
// 　・パスクエリ[u,v]にて、u->lcaとlca->vでHLD上の列の向きが逆になるので、
// 　　乗せたセグ木の演算にマージ方向がある場合などは注意して処理する。
struct HeavyLightDecomposition {
public:
    vvl &g;
    vector< int > sz, in, out, head, rev, par, dep;

    void build() {
        sz.assign(g.size(), 0);
        in.assign(g.size(), 0);
        out.assign(g.size(), 0);
        head.assign(g.size(), 0);
        rev.assign(g.size(), 0);
        par.assign(g.size(), 0);
        dep.assign(g.size(), 0);
        dfs_sz(0, -1, 0);
        int t = 0;
        dfs_hld(0, -1, t);
    }

    /* k: 0-indexed */
    int la(int v, int k) {
        while(1) {
            int u = head[v];
            if(in[v] - k >= in[u]) return rev[in[v] - k];
            k -= in[v] - in[u] + 1;
            v = par[u];
        }
    }

    int lca(int u, int v) const {
        for(;; v = par[head[v]]) {
            if(in[u] > in[v]) swap(u, v);
            if(head[u] == head[v]) return u;
        }
    }

    int dist(int u, int v) const {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    template< typename E, typename Q, typename F, typename S >
    E query(int u, int v, const E &ti, const Q &q, const F &f, const S &s, bool edge = false) {
        E l = ti, r = ti;
        for(;; v = par[head[v]]) {
            if(in[u] > in[v]) swap(u, v), swap(l, r);
            if(head[u] == head[v]) break;
            l = f(q(in[head[v]], in[v] + 1), l);
        }
        return s(f(q(in[u] + edge, in[v] + 1), l), r);
    }

    template< typename E, typename Q, typename F >
    E query(int u, int v, const E &ti, const Q &q, const F &f, bool edge = false) {
        return query(u, v, ti, q, f, f, edge);
    }

    template< typename Q >
    void add(int u, int v, const Q &q, bool edge = false) {
        for(;; v = par[head[v]]) {
            if(in[u] > in[v]) swap(u, v);
            if(head[u] == head[v]) break;
            q(in[head[v]], in[v] + 1);
        }
        q(in[u] + edge, in[v] + 1);
    }

    /* {parent, child} */
    vector< pair< int, int > > compress(vector< int > &remark) {
        auto cmp = [&](int a, int b) { return in[a] < in[b]; };
        sort(begin(remark), end(remark), cmp);
        remark.erase(unique(begin(remark), end(remark)), end(remark));
        int K = (int) remark.size();
        for(int k = 1; k < K; k++) remark.emplace_back(lca(remark[k - 1], remark[k]));
        sort(begin(remark), end(remark), cmp);
        remark.erase(unique(begin(remark), end(remark)), end(remark));
        vector< pair< int, int > > es;
        stack< int > st;
        for(auto &k : remark) {
            while(!st.empty() && out[st.top()] <= in[k]) st.pop();
            if(!st.empty()) es.emplace_back(st.top(), k);
            st.emplace(k);
        }
        return es;
    }

    explicit HeavyLightDecomposition(vvl &g) : g(g) {}

    private:
    void dfs_sz(int idx, int p, int d) {
        dep[idx] = d;
        par[idx] = p;
        sz[idx] = 1;
        if(g[idx].size() && g[idx][0] == p) swap(g[idx][0], g[idx].back());
        for(auto &to : g[idx]) {
            if(to == p) continue;
            dfs_sz(to, idx, d + 1);
            sz[idx] += sz[to];
            if(sz[g[idx][0]] < sz[to]) swap(g[idx][0], to);
        }
    }

    void dfs_hld(int idx, int p, int &times) {
        in[idx] = times++;
        rev[in[idx]] = idx;
        for(auto &to : g[idx]) {
            if(to == p) continue;
            head[to] = (g[idx][0] == to ? head[idx] : to);
            dfs_hld(to, idx, times);
        }
        out[idx] = times;
    }
};
