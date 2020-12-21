/**
 * 参考：http://www.kupc.jp/static/media/J.41d67783.pdf
 * ・蟻本演習4-3-3
 * ・木上クエリ、パスクエリ、区間mod、HL分解、木上のセグ木二分探索、modの性質
 * ・modの重要な性質、1つは自分より大きい値でmod取っても変化なし。(これは考えた)
 * 　そしてもう1つ、減る時は絶対半分以下まで減る。これは考えなかった。
 * 　確かに試してみるとそうだし、整数除算は一番小さい割る2でも半分になる訳だから、
 * 　余りは絶対半分以下ってのは直感的にもそんな感じするね。
 * ・で、これが分かると、値が小さくなる回数は高々log回くらいだなってのも分かる。
 * 　すると、uからvへのパス上で、一番近い方から値を小さくする場所を探索して、
 * 　そこで値を小さくして次の場所へ、って繰り返すと、
 * 　vに到達するまでにやるこの探索回数は高々log回で済む。
 * ・各探索の操作は、セグ木にぶたん的なやつを木上でHLDに乗せたセグ木にやらせればOK。
 * ・もう1つ注意点として、探索で進む方向がlcaまでとlcaから先で逆になるので、
 * 　lcaを境に処理を分ける。これと似たようなことは前にHLDに乗せたセグ木で
 * 　マージする時の左右を気にしないといけないやつでやったね。
 * ・計算量が、探索の一連の操作をlog回、その探索内でセグ木にぶたん的なlogと、
 * 　HLDのlogと、乗せてるセグ木のmin取得のlogで、10万に計4つlogが乗るんだと思うんだけど、
 * 　さすがC++速くて、AC0.69秒。これ1秒かからないんだなー。。
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
#define ALL(A) A.begin(), A.end()
constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { vector<vector<T>> res(N, vector<T>(M, init)); return res; }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { vector<vector<vector<T>>> res(N, vector<vector<T>>(M, vector<T>(L, init))); return res; }

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

template<typename T> T sum(vector<T> A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(vector<T> A) { return *max_element(ALL(A)); }
template<typename T> T min(vector<T> A) { return *min_element(ALL(A)); }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }
int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }

ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

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

// 条件を満たす最小値を見つける二分探索
template<typename F>
ll bisearch_min(ll mn, ll mx, const F &func) {

    ll ok = mx;
    ll ng = mn;
    while (ng+1 < ok) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}


// 条件を満たす最大値を見つける二分探索
template<typename F>
ll bisearch_max(ll mn, ll mx, const F &func) {

    ll ok = mn;
    ll ng = mx;
    while (ok+1 < ng) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];
    vvl nodes(N);
    rep(i, 0, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].pb(v);
        nodes[v].pb(u);
    }
    HeavyLightDecomposition hld(nodes);
    hld.build();
    SegTree<ll> seg(N, [](ll a, ll b) { return min(a, b); }, INF);
    rep(i, 0, N) {
        hld.add(i, i, [&](ll a, ll b) { seg.update(a, A[i]); });
    }
    seg.build();

    rep(i, 0, Q) {
        ll x, u, v;
        cin >> x >> u >> v;
        u--; v--;

        x %= A[u];
        ll lca = hld.lca(u, v);
        auto dist = hld.dist(u, lca);
        while (u != lca) {
            // uからlcaに向かってk世代前より下にx以下があるか、の最小値
            ll nxt = bisearch_min(0, dist, [&](ll m) {
                ll la = hld.la(u, m);
                ll mn = hld.query(u, la, INF, [&](ll a, ll b) { return seg.query(a, b); },
                        [](ll a, ll b) { return min(a, b); });
                return mn <= x;
            });
            // uを更新してlcaに近づけていく
            u = hld.la(u, nxt);
            dist = hld.dist(u, lca);
            x %= A[u];
        }
        dist = hld.dist(lca, v);
        while (lca != v) {
            // vからlcaに向かってk世代前より上にx以下があるか、の最大値
            ll nxt = bisearch_max(0, dist, [&](ll m) {
                ll la = hld.la(v, m);
                ll mn = hld.query(lca, la, INF, [&](ll a, ll b) { return seg.query(a, b); },
                        [](ll a, ll b) { return min(a, b); });
                return mn <= x;
            });
            // lcaを更新してvに近づけていく
            lca = hld.la(v, nxt);
            dist = hld.dist(lca, v);
            x %= A[lca];
        }
        print(x);
    }
    return 0;
}
