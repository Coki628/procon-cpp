/**
 * 参考：https://ei1333.github.io/library/other/mo.cpp
 * 　　　https://ei1333.hateblo.jp/entry/2017/09/11/211011
 * ・ライブラリ整備
 * ・Mo's algorithm
 * ・お馴染みうしさんのところから。いつもありがとうございます。
 * ・区間マージがlogとかで済まなそうで、どうにもセグ木に乗せられないようなクエリに対応できる。
 * ・内部的には尺取みたいに区間を1ずつ伸縮させるようで、
 * 　区間が1変化した時の操作がO(1)とかO(log)なら乗る。
 * ・使う時には区間が伸びた時、縮んだ時、クエリに答える時にそれぞれどうするかの関数を定義。
 * 　伸縮したのが左右どちらかによって処理が違う場合は、そこもそれぞれ用意すればいいように出来てる。
 * ・Moは計算量がlogでなく√が乗るので、実装によっては数10万クラスの制約がきつかったりするみたいだが、
 * 　今回の問題は50万のNとクエリだけどしっかりAC0.93秒。さすが最適化されてるぽいー。
 */

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

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

struct Mo {
    int n;
    vector< pair< int, int > > lr;

    explicit Mo(int n) : n(n) {}

    // クエリを半開区間[l,r)で順番に追加
    void add(int l, int r) {
        lr.emplace_back(l, r);
    }

    template< typename AL, typename AR, typename EL, typename ER, typename O >
    void build(const AL &add_left, const AR &add_right, const EL &erase_left, const ER &erase_right, const O &out) {
        int q = (int) lr.size();
        int bs = n / min< int >(n, sqrt(q));
        vector< int > ord(q);
        iota(begin(ord), end(ord), 0);
        sort(begin(ord), end(ord), [&](int a, int b) {
            int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
            if(ablock != bblock) return ablock < bblock;
            return (ablock & 1) ? lr[a].second > lr[b].second : lr[a].second < lr[b].second;
        });
        int l = 0, r = 0;
        for(auto idx : ord) {
            while(l > lr[idx].first) add_left(--l);
            while(r < lr[idx].second) add_right(r++);
            while(l < lr[idx].first) erase_left(l++);
            while(r > lr[idx].second) erase_right(--r);
            out(idx);
        }
    }

    // add:   区間が伸びる時の処理(引数はmoのindex)
    // erase: 区間が縮む時の処理(引数はmoのindex)
    // out:   クエリに回答する処理(引数はクエリのindex)
    // 伸縮時に左右で処理に違いがなければadd,eraseは1つずつでOK
    template< typename A, typename E, typename O >
    void build(const A &add, const E &erase, const O &out) {
        build(add, add, erase, erase, out);
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    Mo mo(N);
    rep(_, 0, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        mo.add(l, r);
    }

    vector<ll> C(N+1), ans(Q);
    ll cnt = 0;
    // 区間が伸びる時の処理(引数はmoのindex)
    auto add = [&](int idx) {
        if (C[A[idx]] == 0) {
            cnt++;
        }
        C[A[idx]]++;
    };
    // 区間が縮む時の処理(引数はmoのindex)
    auto erase = [&](int idx) {
        C[A[idx]]--;
        if (C[A[idx]] == 0) {
            cnt--;
        }
    };
    // クエリに回答する処理(引数はクエリのindex)
    auto out = [&](int idx) {
        ans[idx] = cnt;
    };
    // 伸縮時に左右で処理に違いがなければadd,eraseは1つずつでいい
    mo.build(add, erase, out);

    for (auto a : ans) {
        print(a);
    }
    return 0;
}
