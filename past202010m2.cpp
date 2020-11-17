/**
 * 参考：https://atcoder.jp/contests/past202010-open/submissions/17946839
 * 　　　https://ei1333.github.io/library/graph/tree/heavy-light-decomposition.cpp
 * 　　　https://qiita.com/Pro_ktmr/items/4e1e051ea0561772afa3
 * 　　　https://beet-aizu.hatenablog.com/entry/2017/12/12/235950
 * ・やってみたかったけど難解で、長らく保留にしていたHL分解をついに履修！
 * ・今回も険しい道だったけど、自分的にabbさんの実装が一番やりやすかった。
 * 　コメントいっぱい付けてくれてたのもでかい。本当にありがとうございます。
 * ・適切にやれば、手持ちのセグ木をそのまま使えることが分かった。
 * 　これなら結構色々他にも応用できそう。
 * ・実装上気をつけたこととして、グラフ上の頂点と、セグ木上の要素が紛らわしくならないように、
 * 　グラフの頂点はu,vにして、セグ木の頂点はa,bにする、みたいに変数名をきっちり分けた。
 * ・区間最大値取得は、今回は常に1点取得なので区間和でも問題ないはず、と思って試した。問題なくAC。
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

template<typename T, typename E>
struct LazySegTree {
    using F = function<T(T, T)>;
    using G = function<T(T, E)>;
    using H = function<E(E, E)>;
    int n, height;
    F f;
    G g;
    H h;
    T ti;
    E ei;
    vector<T> dat;
    vector<E> laz;
    LazySegTree(F f, G g, H h, T ti, E ei):
        f(f), g(g), h(h), ti(ti), ei(ei) {}

    void init(int n_){
        n = 1; height = 0;
        while (n<n_) n<<=1, height++;
        dat.assign(2*n, ti);
        laz.assign(2*n, ei);
    }

    void build(int n_) {
        init(n_);
    }

    void build(const vector<T> &v){
        int n_ = v.size();
        init(n_);
        for (int i=0;i<n_;i++) dat[n+i] = v[i];
        for (int i=n-1;i;i--)
        dat[i] = f(dat[(i<<1)|0], dat[(i<<1)|1]);
    }

    inline T reflect(int k){
        return laz[k]==ei?dat[k]:g(dat[k], laz[k]);
    }

    inline void propagate(int k){
        if (laz[k]==ei) return;
        laz[(k<<1)|0] = h(laz[(k<<1)|0], laz[k]);
        laz[(k<<1)|1] = h(laz[(k<<1)|1], laz[k]);
        dat[k] = reflect(k);
        laz[k] = ei;
    }

    inline void thrust(int k){
        for (int i=height;i;i--) propagate(k>>i);
    }

    inline void recalc(int k){
        while (k>>=1)
        dat[k] = f(reflect((k<<1)|0), reflect((k<<1)|1));
    }

    void update(int a,int b,E x){
        if (a>=b) return;
        thrust(a+=n);
        thrust(b+=n-1);
        for (int l=a,r=b+1;l<r;l>>=1,r>>=1) {
            if (l&1) laz[l] = h(laz[l], x), l++;
            if (r&1) --r, laz[r] = h(laz[r], x);
        }
        recalc(a);
        recalc(b);
    }

    void set_val(int a, T x){
        thrust(a+=n);
        dat[a] = x; laz[a] = ei;
        recalc(a);
    }

    T query(int a, int b){
        if (a>=b) return ti;
        thrust(a+=n);
        thrust(b+=n-1);
        T vl = ti, vr = ti;
        for (int l=a,r=b+1;l<r;l>>=1,r>>=1) {
            if (l&1) vl = f(vl, reflect(l++));
            if (r&1) vr = f(reflect(--r), vr);
        }
        return f(vl, vr);
    }

    template<typename C>
    int find(int st, C &check, T &acc, int k, int l, int r){
        if (l+1==r) {
            acc = f(acc, reflect(k));
            return check(acc)?k-n:-1;
        }
        propagate(k);
        int m = (l+r)>>1;
        if (m<=st) return find(st, check, acc, (k<<1)|1, m, r);
        if (st<=l&&!check(f(acc,dat[k]))) {
            acc = f(acc,dat[k]);
            return -1;
        }
        int vl = find(st, check, acc, (k<<1)|0, l, m);
        if (~vl) return vl;
        return find(st, check, acc, (k<<1)|1, m, r);
    }

    template<typename C>
    int find(int st, C &check){
        T acc = ti;
        return find(st, check, acc, 1, 0, n);
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

    ll N, Q;
    cin >> N >> Q;
    vvl nodes(N);
    vector<pll> edges(N-1);
    ll u, v, c;
    rep(i, 0, N-1) {
        cin >> u >> v;
        u--; v--;
        nodes[u].pb(v);
        nodes[v].pb(u);
        edges[i] = {u, v};
    }
    // HLDの構築
    HeavyLightDecomposition<ll, ll> hld(nodes);
    hld.build();

    // 区間和取得、区間更新
    auto f = [](ll a, ll b) -> ll { return a + b; };
    auto g = [](ll a, ll b) -> ll { return b; };
    // HLDに乗せるセグ木を準備する
    LazySegTree<ll, ll> seg(f, g, g, 0, 0);
    seg.build(N);

    rep(_, 0, Q) {
        cin >> u >> v >> c;
        u--; v--;

        // 頂点[u,v]のパスに当たる区間に対する更新
        hld.add(u, v,
            // 区間[a,b)に対する操作、これがパス[u,v]に当たる区間全てに行われる
            [&](ll a, ll b) { seg.update(a, b, c); },
            // 属性を持つのが辺ならここをtrue
            true);
    }

    for (auto [u, v] : edges) {
        // 頂点[u,v]のパスに当たる区間に対する取得
        ll ans = hld.query(u, v, 0,
            // 区間[a,b)に対する操作、これがパス[u,v]に当たる区間全てに行われる
            [&](ll a, ll b) { return seg.query(a, b); },
            // 2つの区間をマージする時の操作
            [](ll a, ll b) { return a + b; },
            // 属性を持つのが辺ならここをtrue
            true);
        print(ans);
    }
    return 0;
}
