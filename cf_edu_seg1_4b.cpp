/**
 * 参考：https://twitter.com/ningenMe/status/1255411378996891649
 * ・こどふぉコース：Segment Tree
 * ・行列積、セグ木に行列を乗せる
 * ・大変だった。。方針はだいたい合ってたのにTLEが取れず。。
 * ・色々調べた結果、vectorじゃなくてarrayを使う、をやると爆速になった。AC0.56秒。
 * ・引数参照渡しにしたりllをintにしたり他にも色々試したけどそんなに変わらなくて、決定打はarrayだった。
 * 　あんま使ったことなかったけど、ちゃんと使い方覚えておこう。
 * 　特性はだいたい配列と同じで、引数や戻り値に使えるようになった感じ。(vectorみたく便利ではない)
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
    using F = function<Monoid(Monoid&, Monoid&)>;
    
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
    // 2次元arrayの初期化は{}をひとつ多く括る
    array<array<int, 2>, 2> mat{{
        {1, 0}, 
        {0, 1},
    }};

    Node(array<array<int, 2>, 2> &mat) : mat(mat) {};

    Node() {}
};

ll R, N, Q;

Node compare(Node &a, Node &b) {
    // グローバルでないarrayは初期化されないので{}で初期化(0埋め)する
    array<array<int, 2>, 2> mat{};
    rep(i, 0, 2) {
        rep(j, 0, 2) {
            rep(k, 0, 2) {
                mat[i][j] += a.mat[i][k] * b.mat[k][j];
                mat[i][j] %= R;
            }
        }
    }
    return Node(mat);
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    cin >> R >> N >> Q;
    SegTree<Node> seg(N, compare, Node());
    Node v;
    rep(i, 0, N) {
        cin >> v.mat[0][0] >> v.mat[0][1] >> v.mat[1][0] >> v.mat[1][1];
        seg.set(i, v);
    }
    seg.build();

    ll l, r;
    rep(_, 0, Q) {
        cin >> l >> r;
        l--;
        auto res = seg.query(l, r);
        cout << res.mat[0][0] << ' ' << res.mat[0][1] << '\n';
        cout << res.mat[1][0] << ' ' << res.mat[1][1] << '\n';
        print("");
    }
    return 0;
}
