/**
 * ・ライブラリ整備
 * ・HL分解
 * ・この前は辺クエリしかやらなかったので頂点クエリもやってみた。
 * ・WAで全然通らない。何かと思ったらオーバーフロー。。
 * 　単位元の0がintだったから。。This is C++の洗礼。。。
 * ・1点更新の場合、add呼ばなくてもin配列の直接更新でも大丈夫だった。
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

template<typename T>
struct BIT {

    int sz;
    vector<T> tree;

    BIT(int n) {
        // 0-indexed
        n++;
        sz = 1;
        while (sz < n) {
            sz *= 2;
        }
        tree.resize(sz);
    }

    // [0, i]を合計する
    T sum(int i) {
        T s = 0;
        i++;
        while (i > 0) {
            s += tree[i-1];
            i -= i & -i;
        }
        return s;
    }

    void add(int i, T x) {
        i++;
        while (i <= sz) {
            tree[i-1] += x;
            i += i & -i;
        }
    }

    // 区間和の取得 [l, r)
    T query(int l, int r) {
        return sum(r-1) - sum(l-1);
    }

    T get(int i) {
        return query(i, i+1);
    }

    void update(int i, T x) {
        add(i, x - get(i));
    }
};

struct HeavyLightDecomposition {
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

    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    vvl nodes(N);
    ll u, v;
    rep(i, 0, N-1) {
        cin >> u >> v;
        nodes[u].pb(v);
        nodes[v].pb(u);
    }
    HeavyLightDecomposition hld(nodes);
    hld.build();

    BIT<ll> bit(N);
    rep(u, 0, N) {
        // 1点更新なら追加のやり方はこうでもいい
        bit.add(hld.in[u], A[u]);
    }

    ll op, x, y;
    rep(i, 0, Q) {
        cin >> op >> x >> y;
        if (op == 0) {
            bit.add(hld.in[x], y);
        } else {
            // 単位元をLLにする
            ll ans = hld.query(x, y, 0LL, 
                [&](ll a, ll b) { return bit.query(a, b); },
                [](ll a, ll b) { return a + b; });
            print(ans);
        }
    }
    return 0;
}
