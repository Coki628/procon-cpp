/**
 * ・なんとか自力AC。
 * ・確率、余事象、累積積
 * ・とりあえず、ソート済になる確率 → 1回でもソートされる確率で、こう見ると余事象の定番で、
 * 　1 - 1回もソートされない確率、となって、こっちでやった方が求めやすいのでこの方針にする。
 * ・最初を100%として、クエリ毎に掛け算していくんだけど、これを愚直にやったらTLE。。
 * 　誤差めちゃ怖いけどいもすっぽく累積積して、まとめて掛けれるようにした。
 * 　やっぱりWAになったので、ダメ元でC++のlong doubleを信じてこっちで投げたら通った。。
 * ・ちょっと色々整理した版。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    // P[i] := i番目がソートされていない確率
    vector<ld> P(N, 1);
    rep(i, 0, N) {
        if (A[i] == i+1) {
            P[i] = 0;
        }
    }

    // 累積積は0が入ると壊れるので、0の場所を管理するやつと両方用意
    vector<ld> acc(N+1, 1);
    vector<int> done(N+1);
    rep(i, 0, M) {
        ll r;
        ld p;
        cin >> r >> p;
        if (1-p == 0) {
            done[0]++;
            done[r]--;
        } else {
            acc[0] *= 1 - p;
            acc[r] /= 1 - p;
        }
    }
    rep(i, 0, N) {
        acc[i+1] *= acc[i];
        done[i+1] += done[i];
    }

    rep(i, 0, N) {
        if (done[i]) {
            P[i] = 0;
        } else {
            P[i] *= acc[i];
        }
    }

    ld ans = 1;
    for (auto p : P) {
        ans = min(ans, 1-p);
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
