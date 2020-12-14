/**
 * ・なんとか自力AC！
 * ・グリッド
 * ・題意の三角形を最大化するには、1つ自由に選ぶのはグリッドの端のいずれかがよくて、
 * 　残り2点のうち片方は端を選んだのがx方向ならy方向で一番遠く、最後の1点は全マス探索。
 * ・最終的に実装スッキリまとまったのは嬉しいけど、考えまとまって解きにかかるのが遅かったな。。
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
constexpr ll INF = 1000000000000000;
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
    ll N, M = 10;
    cin >> N;
    vector<string> grid(N);
    rep(i, 0, N) cin >> grid[i];

    vector<ll> mnl(M, INF), mxr(M), mnd(M, INF), mxu(M);
    rep(i, 0, N) {
        rep(j, 0, N) {
            int d = toint(grid[i][j]);
            // それぞれの数字で、四方一番端にあるやつを取っておく
            chmin(mnl[d], j);
            chmin(mnd[d], i);
            chmax(mxr[d], j);
            chmax(mxu[d], i);
        }
    }

    vector<ll> ans(M);
    rep(i, 0, N) {
        rep(j, 0, N) {
            int d = toint(grid[i][j]);
            // 横をこのマスから端めいっぱいまで使って、縦はあるやつで一番遠いとこ使う
            ll w = max(j, N-j-1);
            ll h = max(i-mnd[d], mxu[d]-i);
            chmax(ans[d], h*w);
            // 縦横逆でやる
            w = max(j-mnl[d], mxr[d]-j);
            h = max(i, N-i-1);
            chmax(ans[d], h*w);
        }
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
