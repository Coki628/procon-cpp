/**
 * ・こどふぉコース：Segment Tree
 * ・区間転倒数の取得
 * ・自力AC！やったね。
 * ・ベースになる考え方はaclpc_lでの2値転倒数でやった時と同じ感じ。
 * 　今回は値が40個あるけど、これくらいなら演算に使える。
 * ・10万にセグ木のlogと各演算の40がかかるけど、案外速くてAC0.34秒。
 * ・さっきの行列乗せるやつが0.56秒だったのに、こっちのが速いんだなー。
 * 　20万だったからか、2*2でも2次元作るコストがでかいのか、2*2*2で3重ループだからか。
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

// その区間が持つ各値の数と転倒数を管理する
struct Node {

    array<int, 41> C{};
    ll inv = 0;

    Node(array<int, 41> &C, ll inv) : C(C), inv(inv) {};

    Node(array<int, 41> &C) : C(C) {};

    Node() {};

    ll get() {
        return inv;
    }
};

ll N, Q;

Node compare(Node &a, Node &b) {
    array<int, 41> C{}, acc{};
    // 個数のマージと累積和
    rep(i, 1, 41) {
        C[i] = a.C[i] + b.C[i];
        acc[i] = acc[i-1] + b.C[i];
    }
    // 両方の転倒数を足してから、マージした時増える転倒数を数える
    ll inv = a.inv + b.inv;
    rep(i, 2, 41) {
        // bでi-1以下の数と、aの各値iがペアを組める
        inv += acc[i-1] * a.C[i];
    }
    return Node(C, inv);
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> Q;
    SegTree<Node> seg(N, compare, Node());
    int c;
    rep(i, 0, N) {
        cin >> c;
        array<int, 41> C{};
        C[c]++;
        seg.set(i, Node(C));
    }
    seg.build();

    ll op, a, b;
    rep(_, 0, Q) {
        cin >> op;
        if (op == 1) {
            cin >> a >> b;
            a--;
            ll res = seg.query(a, b).get();
            print(res);
        } else {
            cin >> a >> b;
            a--;
            array<int, 41> C{};
            C[b]++;
            seg.update(a, Node(C));
        }
    }
    return 0;
}
