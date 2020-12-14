/**
 * 参考：https://twitter.com/noimi_kyopro/status/1333453998787969033
 * ・自力ならず。。
 * ・N^3のDP
 * ・制約的に500^3=1億2500万はきつめだから高速化して想定N^2logNくらいで何とかするんかなー、
 * 　とか考えちゃったけどそんなことない。C++は通る。億超えも想定解。
 * ・なんとなく、操作が自由にできるから、本当に前から1回ずつ、スワップするかしないかを見るだけで
 * 　最適になるのかが全然確証持てなくて、この方針を詰めに行けなかったんだけど、
 * 　これ書いて通せてしまうと、なんかこの方法が自明にOKな気がしてしまうから不思議。
 * 　考察力が足りません。。。
 * ・普通に領域全部取ったらメモリが512Mギリギリっぽかったので、配列節約した。
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
constexpr int INF = 1000000000;
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

constexpr ll MX = 500;

void solve() {
    ll N, x;
    cin >> N >> x;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    // dp[i][j][k] := 前からi個目まで見て、ひとつ前がj、今のxがkの時の最小コスト
    auto dp = list3d(2, MX+1, MX+1, INF);
    dp[0][0][x] = 0;
    rep(i, 0, N) {
        rep(j, 0, MX+1) {
            rep(x, 0, MX+1) {
                // ここでxをスワップしない
                if (j <= A[i]) {
                    chmin(dp[(i+1)&1][A[i]][x], dp[i&1][j][x]);
                }
                // ここでxをスワップする
                if (x < A[i] and j <= x) {
                    chmin(dp[(i+1)&1][x][A[i]], dp[i&1][j][x] + 1);
                }
            }
        }
        dp[i&1] = list2d(MX+1, MX+1, INF);
    }
    int ans = INF;
    rep(j, 0, MX+1) {
        rep(k, 0, MX+1) {
            chmin(ans, dp[N&1][j][k]);
        }
    }
    if (ans == INF) {
        print(-1);
    } else {
        print(ans);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
