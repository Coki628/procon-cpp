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
unordered_map<T, ll> Counter(vector<T> &A) {
    unordered_map<T, ll> res;
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


template<typename T>
vector<T> accumulate(vector<T> &A) {
    int N = A.size();
    if (!N) return {};
    vector<T> res(N);
    res[0] = A[0];
    rep(i, 1, N) res[i] = res[i-1] + A[i];
    return res;
}


template<typename T, typename F>
vector<T> accumulate(vector<T> &A, const F &func) {
    int N = A.size();
    if (!N) return {};
    vector<T> res(N);
    res[0] = A[0];
    rep(i, 1, N) res[i] = func(res[i-1], A[i]);
    return res;
}
// accumulate<ll>(A, [](ll a, ll b) { return min(a, b); });


// 条件を満たす最小値を見つける二分探索
template<typename F>
ll bisearch_min(ll mn, ll mx, const F &func) {

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
template<typename F>
ll bisearch_max(ll mn, ll mx, const F &func) {

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
typedef unordered_map<ll, int> mli;
typedef unordered_map<int, ll> mil;
pair<mli, mil> compress(vector<ll> A) {
    mli zipped;
    mil unzipped;
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    rep(i, 0, A.size()) {
        zipped[A[i]] = i;
        unzipped[i] = A[i];
    }
    return {zipped, unzipped};
}


// 素因数分解
template<typename T> 
map<T, int> factorize(T x) {
    map<T, int> res;
    for (T i = 2; i*i <= x; i++) {
        while (x%i == 0) {
            x /= i;
            res[i]++;
        }
        if (x == 1) break;
    }
    if (x != 1) res[x]++;
    return res;
}


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

    ModInt inverse() const {
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


// Mod数え上げnCr
struct ModTools {

    int MAX;
    const int MOD;
    vector<mint> fact, inv;

    ModTools(int MOD) : MOD(MOD) {};

    void build(int mx) {
        MAX = ++mx;
        fact.resize(MAX);
        inv.resize(MAX);
        fact[0] = fact[1] = 1;
        rep(i, 2, MAX) {
            fact[i] = fact[i-1] * i;
        }
        inv[MAX-1] = fact[MAX-1].inverse();
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


// なんかこれ速いhashmapらしい
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct custom_hash {
    // https://codeforces.com/blog/entry/62393
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
// gp_hash_table<ll,ll,custom_hash> mp;


// 行列累乗
struct MatPow {

    vvl mat_dot(vvl A, vvl B) {
        ll n1 = A.size();
        ll n2 = A[0].size();
        ll m2 = B[0].size();
        vvl res(n1, vector<ll>(m2, 0));
        rep(i, 0, n1) {
            rep(j, 0, m2) {
                rep(k, 0, n2) {
                    res[i][j] = (res[i][j] + (A[i][k] * B[k][j]) % MOD) % MOD;
                }
            }
        }
        return res;
    }
    
    vvl mat_pow(vvl mat, ll k) {
        ll n = mat.size();
        vvl res(n, vector<ll>(n, 0));
        rep(i, 0, n) {
            res[i][i] = 1;
        }
        while (k > 0) {
            if (k & 1) {
                res = mat_dot(res, mat);
            }
            mat = mat_dot(mat, mat);
            k >>= 1;
        }
        return res;
    }

    vector<ll> solve(vvl mat, vvl init, ll K) {
        auto res = mat_pow(mat, K);
        res = mat_dot(res, init);
        ll n = mat.size();
        vector<ll> ret(n, 0);
        rep(i, 0, n) {
            ret[i] = res[i][0];
        }
    return ret;
    }
};
