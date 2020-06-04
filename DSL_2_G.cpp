/**
 * ・遅延評価セグメント木
 * ・区間和取得・区間加算
 * ・要素Tの単位元は0、作用素Eの単位元も0
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
char tochar(int i) { return '0' + i; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

template<typename T, typename E>
struct SegmentTree {
    typedef function<T(T, T)> F;
    typedef function<T(T, E)> G;
    typedef function<E(E, E)> H;
    typedef function<E(E, int)> P;
    int n;
    F f;
    G g;
    H h;
    P p;
    T d1;
    E d0;
    vector<T> dat;
    vector<E> laz;
    SegmentTree(int n_, F f, G g, H h, T d1, E d0,
            vector<T> v=vector<T>(), P p=[](E a, int b){ return a; }):
            f(f), g(g), h(h), d1(d1), d0(d0), p(p) {
        init(n_);
        if (n_==(int)v.size()) build(n_, v);
    }
    void init(int n_) {
        n = 1;
        while (n<n_) n *= 2;
        dat.clear();
        dat.resize(2*n-1, d1);
        laz.clear();
        laz.resize(2*n-1, d0);
    }
    void build(int n_, vector<T> v) {
        for (int i=0;i<n_;i++) dat[i+n-1] = v[i];
        for (int i=n-2;i>=0;i--)
            dat[i] = f(dat[i*2+1], dat[i*2+2]);
    }
    inline void eval(int len, int k) {
        if (laz[k]==d0) return;
        if (k*2+1<n*2-1) {
            laz[k*2+1] = h(laz[k*2+1], laz[k]);
            laz[k*2+2] = h(laz[k*2+2], laz[k]);
        }
        dat[k] = g(dat[k], p(laz[k], len));
        laz[k] = d0;
    }
    T update(int a, int b, E x, int k, int l, int r) {
        eval(r-l, k);
        if (r<=a||b<=l) return dat[k];
        if (a<=l&&r<=b) {
            laz[k] = h(laz[k], x);
            return g(dat[k], p(laz[k], r-l));
        }
        return dat[k] = f(update(a, b, x, k*2+1, l, (l+r)/2),
                          update(a, b, x, k*2+2, (l+r)/2, r));
    }
    T update(int a, int b, E x) {
        return update(a, b, x, 0, 0, n);
    }
    T query(int a, int b, int k, int l, int r) {
        eval(r-l, k);
        if(r<=a||b<=l) return d1;
        if(a<=l&&r<=b) return dat[k];
        T vl = query(a, b, k*2+1, l, (l+r)/2);
        T vr = query(a, b, k*2+2, (l+r)/2, r);
        return f(vl, vr);
    }
    T query(int a, int b) {
        return query(a, b, 0, 0, n);
    }
};

ll N, Q;
// 区間和取得・区間加算
// 要素Tの単位元は0、作用素Eの単位元も0
auto f = [](ll a, ll b) -> ll { return a + b; };
auto p = [](ll a, ll b) -> ll { return a * b; };

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> Q;
    SegmentTree<ll, ll> seg(N, f, f, f, 0, 0, vector<ll>(N, 0), p);

    ll op, s, t, x;
    rep(i, 0, Q) {
        cin >> op;
        if (op == 0) {
            cin >> s >> t >> x;
            s--; t--;
            seg.update(s, t+1, x);
        } else {
            cin >> s >> t;
            s--; t--;
            print(seg.query(s, t+1));
        }
    }
    return 0;
}
