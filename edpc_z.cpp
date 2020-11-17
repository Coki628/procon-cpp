/**
 * 参考：https://kyopro-friends.hatenablog.com/entry/2019/01/12/231106
 * ・ライブラリ整備：Li Chao Tree
 * ・いよいよ本題。
 * ・遷移の式変形は、遷移元が絡む部分をax+bに織り込んで、
 * 　そうでない固定値Cと遷移先に関わる部分は定数として後から足す。
 * ・具体的には、-2H[j]H[i]がaxになって、H[j]^2+dp[j]がbになって、これを直線の式として追加。
 * 　C+H[i]は遷移元jに関係しないのでqueryの時に別途足す感じにする。
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

template<typename T>
struct DynamicLiChaoTree {

    const ll x_low;
    const ll x_high;
    const T id;
    
    struct Line {
        T a, b;

        Line(T a, T b) : a(a), b(b) {}

        inline T get(ll x) const { return a * x + b; }
    };

    struct Node {
        Line x;
        Node *l, *r;

        Node(const Line &x) : x{x}, l{nullptr}, r{nullptr} {}
    };

    Node *root;

    DynamicLiChaoTree(ll x_low, ll x_high, T id) : root{nullptr}, x_low(x_low), x_high(x_high), id(id) {}

    Node *add_line(Node *t, Line &x, const ll &l, const ll &r, const T &x_l, const T &x_r) {
        if(!t) return new Node(x);

        T t_l = t->x.get(l), t_r = t->x.get(r);

        if(t_l <= x_l && t_r <= x_r) {
            return t;
        } else if(t_l >= x_l && t_r >= x_r) {
        t->x = x;
            return t;
        } else {
            ll m = (l + r) / 2;
            if(m == r) --m;
            T t_m = t->x.get(m), x_m = x.get(m);
            if(t_m > x_m) {
                swap(t->x, x);
                if(x_l >= t_l) t->l = add_line(t->l, x, l, m, t_l, t_m);
                else t->r = add_line(t->r, x, m + 1, r, t_m + x.a, t_r);
            } else {
                if(t_l >= x_l) t->l = add_line(t->l, x, l, m, x_l, x_m);
                else t->r = add_line(t->r, x, m + 1, r, x_m + x.a, x_r);
            }
            return t;
        }
    }

    void add_line(const T &a, const T &b) {
        Line x(a, b);
        root = add_line(root, x, x_low, x_high, x.get(x_low), x.get(x_high));
    }

    Node *add_segment(Node *t, Line &x, const ll &a, const ll &b, const ll &l, const ll &r, const T &x_l, const T &x_r) {
        if(r < a || b < l) return t;
        if(a <= l && r <= b) {
            Line y{x};
            return add_line(t, y, l, r, x_l, x_r);
        }
        if(t) {
            T t_l = t->x.get(l), t_r = t->x.get(r);
            if(t_l <= x_l && t_r <= x_r) return t;
        } else {
            t = new Node(Line(0, id));
        }
        ll m = (l + r) / 2;
        if(m == r) --m;
        T x_m = x.get(m);
        t->l = add_segment(t->l, x, a, b, l, m, x_l, x_m);
        t->r = add_segment(t->r, x, a, b, m + 1, r, x_m + x.a, x_r);
        return t;
    }

    void add_segment(const ll &l, const ll &r, const T &a, const T &b) {
        Line x(a, b);
        root = add_segment(root, x, l, r - 1, x_low, x_high, x.get(x_low), x.get(x_high));
    }

    T query(const Node *t, const ll &l, const ll &r, const T &x) const {
        if(!t) return id;
        if(l == r) return t->x.get(x);
        ll m = (l + r) / 2;
        if(m == r) --m;
        if(x <= m) return min(t->x.get(x), query(t->l, l, m, x));
        else return min(t->x.get(x), query(t->r, m + 1, r, x));
    }

    T query(const T &x) const {
        return query(root, x_low, x_high, x);
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, C;
    cin >> N >> C;
    vector<ll> H(N);
    rep(i, 0, N) cin >> H[i];
    DynamicLiChaoTree<ll> lct(0, 10000000, INF);
    vector<ll> dp(N);
    dp[0] = 0;
    lct.add_line(-2*H[0], H[0]*H[0]);

    rep(i, 1, N) {
        dp[i] = lct.query(H[i]) + C + H[i]*H[i];
        lct.add_line(-2*H[i], H[i]*H[i]+dp[i]);
    }
    ll ans = dp[N-1];
    print(ans);
    return 0;
}
