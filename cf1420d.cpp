/**
 * ・pypyがTLギリギリだったのでこっちでリサブ。無事AC1.60秒。。
 */

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

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
#define list2d(name, N, M, type, init) vector<vector<type>> name(N, vector<type>(M, init))
const ll INF = LONG_LONG_MAX;
const ll MOD = 998244353;

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
// 数字なら'0'、アルファベットなら'a'みたいに使い分ける
// int toint(char c) { return c - '0'; }
// char tochar(int i) { return '0' + i; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

typedef unordered_map<ll, int> mli;
typedef unordered_map<int, ll> mil;
pair<mli, mil> compress(unordered_set<ll> S) {
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

ll N, K, M;
vector<pll> LR;
unordered_set<ll> S, S2;
vvl adjli1, adjli2;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    ll l, r;
    rep(i, 0, N) {
        cin >> l >> r;
        r++;
        LR.pb({l, r});
        S.insert(l);
        S.insert(r);
    }

    auto comp = compress(S);
    auto zipped = comp.first;
    M = zipped.size();
    adjli1.resize(M);
    adjli2.resize(M);
    rep(i, 0, N) {
        adjli1[zipped[LR[i].first]].pb(i);
        adjli2[zipped[LR[i].second]].pb(i);
    }

    mint ans = 0;
    auto ct = CombTools(MOD);
    ct.build(N);
    rep(i, 0, M) {
        for (ll j : adjli2[i]) {
            S2.erase(j);
        }
        for (ll j : adjli1[i]) {
            if (S2.size() >= K-1) {
                ans += ct.nCr((int)S2.size(), K-1);
            }
            S2.insert(j);
        }
    }
    print(ans);
    return 0;
}
