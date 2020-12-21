/**
 * ・蟻本演習4-3-3
 * ・なんと自力AC！企業コン本戦F問題でこれは嬉しい。びっくりした。
 * ・HL分解、区間加算BIT、言い換え、二分探索
 * ・部分木に関する問題だから部分木クエリっぽく何かやるのかなーと思ったけど、
 * 　考察したらパスクエリで区間加算に帰着した。
 * ・部分木の実は全て取れる -> 実った頂点から根へのパス上の頂点は全てその実を取れる
 * 　と言い換えることができる。(多分)
 * 　これで毎回のクエリに対して、どの頂点ならいくつ実が取れる状態になるのかは、
 * 　実1つにつきlogで更新できるようになった。
 * ・さて今回欲しいのは、K個以上取れる中で深さが最大の頂点だけど、
 * 　これは実がなった頂点から根に向かって、K個以上取れる一番深い位置を二分探索するといける。
 * 　実がなった全ての頂点からやっても、実の総数で10万回なので問題ない。
 * 　実がなった頂点から根へのパス以外の場所は部分木に何もない(はず)ので、見る必要がない。
 * ・これで無事AC。にぶたん、HLD、BITそれぞれで計3つlogが10万に乗るけど、AC0.26秒。速いね。
 * ・公式解は結構方針違うっぽい。
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

// 区間加算BIT(区間加算・区間和取得)
template<typename T>
struct BIT2 {

    ll N;
    vector<T> data0, data1;

    BIT2() {};

    BIT2(int N) {
        resize(N);
    }

    void resize(int n) {
        // 添字0が使えないので、内部的には全て1-indexedとして扱う
        N = ++n;
        data0.resize(N);
        data1.resize(N);
    }

    void _add(vector<T> &data, int k, T x) {
        k++;
        while (k < N) {
            data[k] += x;
            k += k & -k;
        }
    }

    T _get(vector<T> &data, int k) {
        k++;
        T s = 0;
        while (k) {
            s += data[k];
            k -= k & -k;
        }
        return s;
    }

    // 区間[l,r)に値xを加算
    void add(int l, int r, T x) {
        _add(data0, l, -x*(l-1));
        _add(data0, r, x*(r-1));
        _add(data1, l, x);
        _add(data1, r, -x);
    }

    // 1点加算
    void add(int i, T x) {
        add(i, i+1, x);
    }

    // 区間[l,r)の和を取得
    T query(int l, int r) {
        return _get(data1, r-1) * (r-1) + _get(data0, r-1) - _get(data1, l-1) * (l-1) - _get(data0, l-1);
    }

    // 1点取得
    T get(int i) {
        return query(i, i+1);
    }

    // 1点更新
    void update(int i, T x) {
        add(i, i+1, x - get(i));
    }

    T operator[](int i) {
        return get(i);
    }
};

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

    ll N;
    cin >> N;
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
    BIT2<ll> bit(N);

    ll Q;
    cin >> Q;
    rep(_, 0, Q) {
        ll M, K;
        cin >> M >> K;
        vector<ll> A(M);
        rep(i, 0, M) {
            cin >> A[i];
            A[i]--;
            // 部分木の実は全て取れる -> 実った頂点から根へのパス上の頂点は全てその実を取れる
            hld.add(0, A[i], [&](ll a, ll b) { bit.add(a, b, 1); });
        }
        ll ans = 0;
        for (ll v : A) {
            ll depth = hld.dist(0, v);
            // vから根まで遡って、K個以上取れる一番深い位置を二分探索する
            ll mx = bisearch_max(0, depth+1, [&](ll m) {
                ll la = hld.la(v, depth-m);
                return bit[hld.in[la]] >= K;
            });
            // 今回実った全ての頂点でやった最大が答え
            chmax(ans, mx);
        }
        print(ans);
        for (ll v : A) {
            // 状態を元に戻す
            hld.add(0, v, [&](ll a, ll b) { bit.add(a, b, -1); });
        }
    }
    return 0;
}
