/**
 * ・HL分解の練習兼verify用
 * ・1点更新なので、遅延セグ木じゃなくてもよくね？となって普通のセグ木を乗せてみる。
 * ・ちゃんとACしたけど、注意点として、更新時に区間[a,a)みたいなやつも飛んでくるので、
 * 　この時には更新しないようにちゃんと場合分けする。
 */

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

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

template<typename Monoid>
struct SegTree {
    using F = function<Monoid(Monoid, Monoid)>;
    
    int sz;
    vector<Monoid> seg;
    
    const F f;
    const Monoid M1;
    
    SegTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
    }

    SegTree(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.resize(2 * sz, M1);
    }

    void clear() {
        seg.clear();
    }
    
    void set(int k, const Monoid &x) {
        seg[k+sz] = x;
    }
    
    void build() {
        for(int k = sz - 1; k > 0; k--) {
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }

    void update(int k, const Monoid &x) {
        k += sz;
        seg[k] = x;
        while(k >>= 1) {
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }
 
    Monoid query(int a, int b) {
        Monoid L = M1, R = M1;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) L = f(L, seg[a++]);
            if(b & 1) R = f(seg[--b], R);
        }
        return f(L, R);
    }

    Monoid operator[](const int &k) const {
        return seg[k+sz];
    }

    Monoid all() {
        return seg[1];
    }
};

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

template <class weight_t = int, class flow_t = int> struct HeavyLightDecomposition {
    vvl &g;
    vector<int> sz;   // sz[i]   := ノードiを根とする部分木のサイズ
    vector<int> in;   // in[i]   := ノードiはオイラーツアー何番目か
    vector<int> out;  // out[i]  := オイラーツアー帰りがけでノードi到達時までに計いくつノードを走査したか
    vector<int> head; // head[i] := HLD後のノードiを含む木の根ノード
    vector<int> rev;  // rev[i]  := オイラーツアーでi番目に訪れるノード（inの逆写像）
    vector<int> par;  // par[i]  := ノードiの親（0を根としたとき）

    HeavyLightDecomposition(vvl &g)
        : g(g), sz(g.size()), in(g.size()), out(g.size()), head(g.size()), rev(g.size()), par(g.size()) {}

    // 部分木のサイズを調べながらdfsする
    void dfs_sz(int idx, int p) {
        par[idx] = p;
        sz[idx] = 1;
        // 最初のエッジが親へ向いているものなら、交換可能なら交換する
        if (g[idx].size() >= 2ul && g[idx][0] == p) {
            swap(g[idx][0], g[idx][1]);
            // swap(g[idx][0], g[idx].back());
        }
        for (auto &to : g[idx]) {
            if (to == p) continue;
            dfs_sz(to, idx);
            sz[idx] += sz[to];
            // 部分木のサイズが大きい子ノードへのエッジが先頭になるようにする
            if (sz[g[idx][0]] < sz[to]) {
                // dump(g[idx][0], to, sz[g[idx][0]], sz[to]);
                swap(g[idx][0], to);
            }
        }
    }

    // dfsしながらhldを実行する
    void dfs_hld(int idx, int par, int &times) {
        in[idx] = times++;
        rev[in[idx]] = idx;
        for (auto &to : g[idx]) {
            if (to == par) continue;
            head[to] = (g[idx][0] == to ? head[idx] : to);
            dfs_hld(to, idx, times);
        }
        out[idx] = times;
    }

    // 構築する
    void build() {
        dfs_sz(0, -1);
        int t = 0;
        dfs_hld(0, -1, t);
    }

    // 頂点vから頂点0方向にk個だけ遡った頂点を返す
    int la(int v, int k) {
        while (1) {
            int u = head[v];
            if (in[v] - k >= in[u]) return rev[in[v] - k];
            k -= in[v] - in[u] + 1;
            v = par[u];
        }
    }

    // 頂点uとvの最小共通祖先を返す
    int lca(int u, int v) {
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) return u;
        }
    }

    /**
     * 頂点uとvを通るパスに対する取得クエリを処理する
     * @param ti 単位元
     * @param q 列に対するクエリを返す演算
     * @param f 列と列同士の演算結果をマージする演算
     * @param edge 頂点クエリではなく辺クエリとして処理する
     */
    template <typename T, typename Q, typename F>
    T query(int u, int v, const T &ti, const Q &q, const F &f, bool edge = false) {
        T l = ti, r = ti;
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v), swap(l, r);
            if (head[u] == head[v]) break;
            l = f(q(in[head[v]], in[v] + 1), l);
        }
        return f(f(q(in[u] + edge, in[v] + 1), l), r);
        // return {f(q(in[u] + edge, in[v] + 1), l), r};
    }

    /**
     * 頂点uとvを通るパスに対する更新クエリを処理する O(log n)
     * @param q 更新クエリ：半開区間で呼び出される (left, right) -> void
     * @param edge 頂点クエリではなく辺クエリとして処理する
     */
    template <typename Q> void add(int u, int v, const Q &q, bool edge = false) {
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) break;
            q(in[head[v]], in[v] + 1);
        }
        q(in[u] + edge, in[v] + 1);
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, M;
    cin >> N >> M;
    ll a, b, c;
    vector<tuple<ll, ll, ll>> edges, edges2, edges3;
    rep(_, 0, M) {
        cin >> a >> b >> c;
        a--; b--;
        edges.pb({c, a, b});
        edges2.pb({a, b, c});
    }
    sort(edges.begin(), edges.end());

    UnionFind uf(N);
    vvl nodes(N);
    set<pll> used;
    ll mncost = 0;
    for (auto [c, a, b] : edges) {
        if (!uf.is_same(a, b)) {
            uf.merge(a, b);
            nodes[a].pb(b);
            nodes[b].pb(a);
            edges3.pb({a, b, c});
            used.insert({a, b});
            used.insert({b, a});
            mncost += c;
        }
    }

    SegTree<ll> seg(N, [](ll a, ll b) -> ll { return max(a, b); }, -INF);

    HeavyLightDecomposition<ll, ll> hld(nodes);
    hld.build();

    ll u, v;
    for (auto edge : edges3) {
        tie(u, v, c) = edge;
        // a == b の時は更新処理されないようにする
        hld.add(u, v, [&](ll a, ll b) { if (a != b) seg.update(a, c); }, true);
    }

    for (auto [u, v, c] : edges2) {
        if (used.count({u, v})) {
            print(mncost);
        } else {
            // [u,v]パス上の辺から最大コストを取得
            ll mx = hld.query(u, v, -INF,
                [&](ll a, ll b) { return seg.query(a, b); },
                [](ll a, ll b) { return max(a, b); }, true);
            print(mncost + c - mx);
        }
    }
    return 0;
}
