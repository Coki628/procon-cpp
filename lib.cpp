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


// ここから関数

template<typename T>
map<T, ll> Counter(vector<T> A) {
    map<T, ll> res;
    for (T a : A) {
        res[a]++;
    }
    return res;
}

map<char, ll> Counter(string S) {
    map<char, ll> res;
    for (char c : S) {
        res[c]++;
    }
    return res;
}

// 条件を満たす最小値を見つける二分探索
ll bisearch_min(ll mn, ll mx, function<bool(ll)> func) {

    ll ok = mx;
    ll ng = mn;
    while (ng+1 < ok) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            // 下を探しに行く
            ok = mid;
        } else {
            // 上を探しに行く
            ng = mid;
        }
    }
    return ok;
}

// 条件を満たす最大値を見つける二分探索
ll bisearch_max(ll mn, ll mx, function<bool(ll)> func) {

    ll ok = mn;
    ll ng = mx;
    while (ok+1 < ng) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            // 上を探しに行く
            ok = mid;
        } else {
            // 下を探しに行く
            ng = mid;
        }
    }
    return ok;
}

// 座標圧縮
typedef map<ll, int> mli;
typedef map<int, ll> mil;
pair<mli, mil> compress(set<ll> S) {
    mli zipped;
    mil unzipped;
    vector<ll> A(S.begin(), S.end());
    sort(A.begin(), A.end());
    rep(i, 0, A.size()) {
        zipped[A[i]] = i;
        unzipped[i] = A[i];
    }
    return mkp(zipped, unzipped);
}

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


// ここからクラス

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

    // 集合の数
    int get_size() {
        set<int> res;
        rep(i, 0, n+1) {
            res.insert(find(i));
        }
        // グループ0の分を引いて返却
        return res.size() - 1;
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


template<typename Monoid>
struct SegmentTree {
    using F = function<Monoid(Monoid, Monoid)>;
    
    int sz;
    vector<Monoid> seg;
    
    const F f;
    const Monoid M1;
    
    SegmentTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
    }

    SegmentTree(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.resize(2 * sz, M1);
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

    // 区間[l,r]で左からx番目の値がある位置
    ll bisearch_fore(ll l, ll r, ll x) {
        ll ok = r + 1;
        ll ng = l - 1;
        while (ng+1 < ok) {
            ll mid = (ok+ng) / 2;
            if (query(l, mid+1) >= x) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != r + 1) {
            return ok;
        } else {
            return INF;
        }
    }

    // 区間[l,r]で右からx番目の値がある位置
    ll bisearch_back(ll l, ll r, ll x) {
        ll ok = l - 1;
        ll ng = r + 1;
        while (ok+1 < ng) {
            ll mid = (ok+ng) / 2;
            if (query(mid, r+1) >= x) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != l - 1) {
            return ok;
        } else {
            return -INF;
        }
    }

    // 左から見て、条件を満たす値が最初に出現する位置
    ll bisearch_left(ll l, ll r, function<bool(ll)> func) {
        ll ok = r;
        ll ng = l;
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
};


template<typename Monoid>
struct SegmentTreeIndex {
    using F = function<Monoid(Monoid, Monoid)>;
    
    int sz;
    vector<Monoid> seg;
    vector<int> index;
    
    const F f;
    const Monoid M1;
    
    SegmentTreeIndex(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
        index.assign(2 * sz, -1);
        // 1段目(最下段)の初期化
        rep(i, 0, sz) index[i+sz] = i;
        // 2段目以降の初期化(全部左の子の値に更新)
        rrep(i, sz-1, -1) index[i] = index[i*2];
    }

    SegmentTreeIndex(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
        index.assign(2 * sz, -1);
        // 1段目(最下段)の初期化
        rep(i, 0, sz) index[i+sz] = i;
        // 2段目以降の初期化(全部左の子の値に更新)
        rrep(i, sz-1, -1) index[i] = index[i*2];
    }
    
    void set(int k, const Monoid &x) {
        seg[k+sz] = x;
        index[k+sz] = k;
    }
    
    void build() {
        for(int k = sz - 1; k > 0; k--) {
            // 左の子の値を優先して更新
            if (f(seg[2*k], seg[2*k+1]) == seg[2*k]) {
                seg[k] = seg[2*k];
                index[k] = index[2*k];
            } else {
                seg[k] = seg[2*k+1];
                index[k] = index[2*k+1];
            }
            
        }
    }

    void update(int k, const Monoid &x) {
        k += sz;
        seg[k] = x;
        while(k >>= 1) {
            // 左の子の値を優先して更新
            if (f(seg[2*k], seg[2*k+1]) == seg[2*k]) {
                seg[k] = seg[2*k];
                index[k] = index[2*k];
            } else {
                seg[k] = seg[2*k+1];
                index[k] = index[2*k+1];
            }
        }
    }
 
    pair<Monoid, int> query(int a, int b) {
        pair<Monoid, int> L = mkp(M1, -1), R = mkp(M1, -1);
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if (a & 1) {
                if (f(seg[a], L.first) == seg[a]) {
                    L.first = seg[a];
                    L.second = index[a];
                }
                a++;
            }
            if (b & 1) {
                b--;
                if (f(R.first, seg[b]) != R.first) {
                    R.first = seg[b];
                    R.second = index[b];
                }
            }
        }
        // 左との一致を優先する
        if (f(L.first, R.first) == L.first) {
            return L;
        } else {
            return R;
        }
    }

    Monoid operator[](const int &k) const {
        return seg[k+sz];
    }
};


// スパーステーブル：構築にO(NlogN)、区間最小(最大)をO(1)で取得
struct SparseTable {

    const function<ll(ll, ll)> func;
    vvl dat;
    vector<ll> height;

    SparseTable(function<ll(ll, ll)> func) : func(func) {
    }

    SparseTable(vector<ll> A, function<ll(ll, ll)> func) : func(func) {
        build(A);
    }

    void build(vector<ll> A) {
        ll N = A.size();

        ll h = 0;
        while ((1<<h) < N) {
            h++;
        }
        dat.resize(h);
        rep(i, 0, h) dat[i].resize(1<<h);
        height.resize(N+1);

        rep(i, 2, N+1) {
            height[i] = height[i>>1] + 1;
        }
        rep(i, 0, N) {
            dat[0][i] = A[i];
        }
        rep(i, 1, h) {
            rep(j, 0, N) {
                dat[i][j] = func(dat[i-1][j], dat[i-1][min(j+(1<<(i-1)), N-1)]);
            }
        }
    }

    // 区間[l,r)でのmin,maxを取得
    ll get(ll l, ll r) {
        if (l >= r) throw exception();
        ll a = height[r-l];
        return func(dat[a][l], dat[a][r-(1<<a)]);
    }
};


// 区間加算BIT(区間加算・区間合計取得)
struct BIT2 {

    ll N;
    vector<ll> data0, data1;

    BIT2() {};

    BIT2(ll N) {
        resize(N);
    }

    void resize(ll n) {
        // 添字0が使えないので、内部的には全て1-indexedとして扱う
        N = ++n;
        data0.resize(N);
        data1.resize(N);
    }

    void _add(vector<ll> &data, ll k, ll x) {
        k++;
        while (k < N) {
            data[k] += x;
            k += k & -k;
        }
    }

    ll _get(vector<ll> &data, ll k) {
        k++;
        ll s = 0;
        while (k) {
            s += data[k];
            k -= k & -k;
        }
        return s;
    }

    // 区間[l,r)に値xを追加 
    void add(ll l, ll r, ll x) {
        _add(data0, l, -x*(l-1));
        _add(data0, r, x*(r-1));
        _add(data1, l, x);
        _add(data1, r, -x);
    }

    // 1点更新
    void add(ll i, ll x) {
        add(i, i+1, x);
    }

    // 区間[l,r)の和を取得
    ll query(ll l, ll r) {
        return _get(data1, r-1) * (r-1) + _get(data0, r-1) - _get(data1, l-1) * (l-1) - _get(data0, l-1);
    }

    // 1点取得
    ll get(ll i) {
        return query(i, i+1);
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


// ModInt
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
