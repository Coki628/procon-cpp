/**
 * 参考：https://atcoder.jp/contests/abc160/submissions/11288025
 * ・全方位木DP、数え上げ
 * ・mintライブラリ化版
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<ll, ld> pld;
typedef pair<pii, int> ppiii;
typedef pair<pii, ll> ppiil;
typedef pair<pll, ll> pplll;
typedef pair<pli, int> pplii;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
typedef vector<vector<pll>> vvpll;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define mkp make_pair
const ll INF = 1e18;
const ll MOD = 1e9 + 7;

void print(ld out) { cout << fixed << setprecision(12) << out << '\n'; }
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
int toint(char c) { return c - '0'; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }

int popcount(ll S) { return __builtin_popcountll(S); }

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

template<int mod>
struct ModInt {
    int x;

    ModInt() : x(0) {}

    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    ModInt &operator+=(const ModInt &p) {
        if((x += p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator-=(const ModInt &p) {
        if((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator*=(const ModInt &p) {
        x = (int) (1LL * x * p.x % mod);
        return *this;
    }

    ModInt &operator/=(const ModInt &p) {
        *this *= p.inverse();
        return *this;
    }

    ModInt operator-() const { return ModInt(-x); }

    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }

    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }

    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }

    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

    bool operator==(const ModInt &p) const { return x == p.x; }

    bool operator!=(const ModInt &p) const { return x != p.x; }

    ModInt inv() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while(b > 0) {
        t = a / b;
        swap(a -= t * b, b);
        swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const {
        ModInt ret(1), mul(x);
        while(n > 0) {
        if(n & 1) ret *= mul;
        mul *= mul;
        n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const ModInt &p) {
        return os << p.x;
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        int64_t t;
        is >> t;
        a = ModInt< mod >(t);
        return (is);
    }

    static int get_mod() { return mod; }
};

using mint = ModInt<MOD>;

struct CombTools {

    int MAX;
    const int MOD;
    vector<mint> fact, inv;

    CombTools(int MOD) : MOD(MOD) {};

    void build(int mx) {
        MAX = ++mx;
        fact.resize(MAX);
        inv.resize(MAX);
        fact[0] = fact[1] = 1;
        rep(i, 2, MAX) {
            fact[i] = fact[i-1] * i;
        }
        inv[MAX-1] = fact[MAX-1].inv();
        rrep(i, MAX-2, -1) {
            inv[i] = inv[i+1] * (i+1);
        }
    }

    mint nCr(int n, int r) {
        if (n < r) return 0;
        r = min(r, n-r);
        mint num = fact[n];
        mint den = inv[r] * inv[n-r];
        return num * den;
    }
};

ll N;
CombTools ct(MOD);

pair<mint, int> f1(pair<mint, int> a, pair<mint, int> b) {
    // pair(a内での通り数 * b内での通り数 * a,b全体での並べ方, aの頂点数 + b頂点数)
    return mkp(a.first * b.first * ct.nCr(a.second + b.second, a.second), a.second + b.second);
}

pair<mint, int> f2(pair<mint, int> a, int v) {
    return mkp(a.first, a.second + 1);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    // pair(iを根とした部分木での通り数, iを根とした部分木の頂点数)
    ReRooting<pair<mint, int>, int> rr(N, f1, f2, mkp(mint(1), 0));
    ll a, b;
    rep(i, 0, N-1) {
        cin >> a >> b;
        a--; b--;
        rr.add_edge(a, b, 1);
    }
    ct.build(N);
    auto ans = rr.build();
    rep(i, 0, N) {
        print(ans[i].first);
    }
    return 0;
}
