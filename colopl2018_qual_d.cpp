/**
 * ・ライブラリ整備：Li Chao Tree
 * ・これ思い出したからやってみた。やっぱりこういうi-jみたいな値を含む遷移には結構使えるぽい。
 * ・今回は最大値なので、-a,-b,-query(x) ってやってる。
 * ・式変形は、min(T[j]-T[k], X) をどう処理するかで、これはある位置まではXまで上がり続けて、
 * 　そこからはずっと変わらない、みたいな形なので、上がる直線と変化なしの直線の2つを追加してる。
 * 　a = 1, b = -T[j]+dp[i][j] と、a = 0, b = X+dp[i][j] の2つ。
 * ・方針は合ってると思うんだけど、5000^2にlog乗るとつらくてTLE。。
 * 　てかメモリも余裕でオーバーしてるしね。。配列節約したいけど、構造体のうまいコピーができなかった。。
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

    ll N, X;
    cin >> N >> X;
    vector<ll> T(N);
    rep(i, 0, N) cin >> T[i];
    T.insert(T.begin(), -10000000000);
    // dp[i][j] := i回使って、最後に使ったのがj回目
    list2d(dp, N+1, N+1, ll, 0);
    dp[0][0] = 0;
    // rep(i, 0, N) {
    //     rep(j, i, N+1) {
    //         rep(k, 0, j) {
    //             chmax(dp[i+1][j], dp[i][k] + min(T[j]-T[k], X));
    //         }
    //     }
    // }
    // rep(i, 1, N+1) {
    //     print(max(dp[i]));
    // }

    vector<DynamicLiChaoTree<ll>> lct(N+1, DynamicLiChaoTree<ll>(0, 10000000000, INF));
    lct[0].add_line(0, 0);
    rep(i, 0, N) {
        rep(j, i, N+1) {
            dp[i][j] = -lct[i].query(T[j]);
            lct[i+1].add_segment(T[j], T[j]+X, -1, -(-T[j]+dp[i][j]));
            lct[i+1].add_segment(T[j]+X, 10000000000, 0, -(X+dp[i][j]));
        }
    }
    dp[N][N] = -lct[N].query(T[N]);
    rep(i, 1, N+1) {
        print(max(dp[i]));
    }
    return 0;
}
