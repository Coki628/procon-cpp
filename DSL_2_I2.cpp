/**
 * ・遅延評価セグメント木
 * ・区間和取得・区間更新
 * ・区間和を取りたい時は、要素の値と一緒に要素数を持っておくといい。
 * ・このやり方だと、区間和取得も関数Pがない非再帰セグ木の方でいける。
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
    SegmentTree(F f, G g, H h, T ti, E ei):
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

ll N, Q;
// 区間和取得・区間更新
auto f = [](pll a, pll b) -> pll { return { a.first+b.first, a.second+b.second }; };
auto g = [](pll a, ll b) -> pll { return { a.second*b, a.second }; };
auto h = [](ll a, ll b) -> ll { return b; };

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> Q;
    // P(a, b) := {値, 要素数}
    SegmentTree<pll, ll> seg(f, g, h, {0, 0}, INT_MAX);
    seg.build(vector<pll>(N, {0, 1}));

    ll op, s, t, x;
    rep(i, 0, Q) {
        cin >> op;
        if (op == 0) {
            cin >> s >> t >> x;
            seg.update(s, t+1, x);
        } else {
            cin >> s >> t;
            print(seg.query(s, t+1).first);
        }
    }
    return 0;
}
