/**
 * ・蟻本演習4-3-3
 * ・自力AC！いいね。
 * ・HL分解、辺属性、BIT(区間和取得)
 * ・部分木を反転させるとあるけど、書いてみると、それで影響を受けて交互でなくなる場所は
 * 　親との辺の1箇所のみと気付く。
 * ・であれば頂点の白黒ではなく、辺のOK/NGを状態として持てば、1点の0,1が管理できれば更新クエリはOK。
 * ・パスのOK判定のクエリも、パスの区間和取得をして、1つでも1が含まれればNGと判定できる。
 * ・よってHLDに区間和が取れるもの(普通のBITでOK)を乗せればいい。
 * ・あと忘れてたけど、1点更新/取得はhld.in[u]とかで取れるんだった。
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

    T operator[](int i) {
        return get(i);
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    vvl nodes(N);
    vector<ll> P(N);
    rep(i, 1, N) {
        cin >> P[i];
        P[i]--;
        nodes[i].pb(P[i]);
        nodes[P[i]].pb(i);
    }
    vector<ll> C(N);
    rep(i, 0, N) cin >> C[i];

    HeavyLightDecomposition hld(nodes);
    hld.build();
    BIT<ll> bit(N);
    rep(i, 1, N) {
        ll p = P[i];
        if (C[i] == C[p]) {
            bit.add(hld.in[i], 1);
        }
    }

    ll Q;
    cin >> Q;
    rep(_, 0, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll u;
            cin >> u;
            u--;
            if (u) {
                if (bit[hld.in[u]]) {
                    bit.add(hld.in[u], -1);
                } else {
                    bit.add(hld.in[u], 1);
                }
            }
        } else {
            ll u, v;
            cin >> u >> v;
            u--; v--;
            ll ng = hld.query(u, v, 0LL, [&](ll a, ll b) { return bit.query(a, b); },
                    [](ll a, ll b) { return a + b; }, true);
            if (!ng) {
                YES();
            } else {
                NO();
            }
        }
    }
    return 0;
}
