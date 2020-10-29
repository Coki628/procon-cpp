/**
 * 参考：https://codeforces.com/edu/course/2/lesson/4/2
 * ・こどふぉコース：Segment Tree
 * ・1点更新、最大区間和取得
 * ・難しかった。でもすごく勉強になっていい感じ。
 * ・区間同士のマージで、左右をよく意識する必要がある。
 * ・値を4つ、区間和、全体の最大区間和、左最大区間和、右最大区間和を持つ。
 * 　マージをどうするかはソース内コメント参照。
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
#define list2d(name, N, M, type, init) vector<vector<type>> name(N, vector<type>(M, init))
const ll INF = LONG_LONG_MAX;
const ll MOD = 1000000007;

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

struct Node {
    ll mx, prefmx, sufmx, sm;
    ll get() {
        return mx;
    }
};

Node compare(Node a, Node b) {
    Node res;
    res.sm = a.sm + b.sm;
    // max(左全部+右前半, 左前半のみ)
    res.prefmx = max({a.sm+b.prefmx, a.prefmx, 0LL});
    // max(左後半+右全部, 右後半のみ)
    res.sufmx = max({a.sufmx+b.sm, b.sufmx, 0LL});
    // max(左最大, 右最大, 左後半+右前半)
    res.mx = max({a.mx, b.mx, a.sufmx+b.prefmx, 0LL});
    return res;
}

ll N, Q;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> Q;
    SegTree<Node> seg(N, compare, {0, 0, 0, 0});
    ll x;
    rep(i, 0, N) {
        cin >> x;
        seg.set(i, {max(x, 0LL), max(x, 0LL), max(x, 0LL), x});
    }
    seg.build();

    print(seg.all().get());
    ll a, b;
    rep(i, 0, Q) {
        cin >> a >> b;
        seg.update(a, {max(b, 0LL), max(b, 0LL), max(b, 0LL), b});
        print(seg.all().get());
    }
    return 0;
}
