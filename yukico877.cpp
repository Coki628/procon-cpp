/**
 * ・自力AC！
 * ・平方分割
 * ・明らかにセグ木想定の問題だけど、平方分割で殴ったら何とか通せた。
 * ・平方分割、簡単なやつしかやったことなかったからいい練習になって良かった。
 * ・計算量はやっぱ厳しめで、制約10万でもAC1.77秒。Q√Nににぶたんのlogも乗ってるからなぁ。
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
#define ALL(A) A.begin(), A.end()
constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { vector<vector<T>> res(N, vector<T>(M, init)); return res; }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { vector<vector<vector<T>>> res(N, vector<vector<T>>(M, vector<T>(L, init))); return res; }

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    ll D = ceil(sqrt(N));
    vvpll bucket(D);
    vvl sorted(D), acc(D);
    vector<ll> sm(D);
    rep(i, 0, N) {
        bucket[i/D].pb({A[i], i});
        sorted[i/D].pb(A[i]);
        acc[i/D].pb(A[i]);
    }
    rep(i, 0, D) {
        acc[i].pb(0);
        sort(ALL(sorted[i]));
        sort(ALL(acc[i]));
        ll M = acc[i].size();
        rep(j, 1, M) {
            acc[i][j] += acc[i][j-1];
        }
        sm[i] = sum(sorted[i]);
    }

    rep(_, 0, Q) {
        ll op, l, r, x;
        cin >> op >> l >> r >> x;
        l--;
        ll res = 0;
        ll ld = l / D;
        ll rd = r / D;
        // 左端と右端が同じ区間なら重複がないようにする
        if (ld == rd) {
            for (auto [a, i] : bucket[ld]) {
                if (l <= i and i < r) res += max(a-x, 0LL);
            }
        } else {
            // 左右の端は愚直に見る
            for (auto [a, i] : bucket[ld]) {
                if (l <= i) res += max(a-x, 0LL);
            }
            for (auto [a, i] : bucket[rd]) {
                if (i < r) res += max(a-x, 0LL);
            }
            // 全部を含む区間はまとめて処理
            rep(i, ld+1, rd) {
                ll M = sorted[i].size();
                ll j = lower_bound(ALL(sorted[i]), x) - sorted[i].begin();
                // 区間の総和から
                // 「x以上あるので全部(x*区間長)引ける部分 + x未満なのでその部分の区間和」
                // を引く
                res += sm[i] - (x*(M-j)+acc[i][j]);
            }
        }
        print(res);
    }
    return 0;
}
