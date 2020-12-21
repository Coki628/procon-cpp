/**
 * ・個数制限付き部分和DP、平均を総和にするテク、MOD累積和
 * ・pythonから移植して、MOD取りとか調整してWAをなくす。
 * ・とりあえず一般的な処置として配列節約もやる。ここからさらに色々高速化を考える。
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
// constexpr ll MOD = 1000000007;

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

ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

template<typename T> T sum(vector<T> A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(vector<T> A) { return *max_element(ALL(A)); }
template<typename T> T min(vector<T> A) { return *min_element(ALL(A)); }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }
int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }

ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, K, MOD;
    cin >> N >> K >> MOD;

    rep(x, 1, N+1) {
        vector<ll> A(N);
        rep(i, 0, N) A[i] = i + 1 - x;

        ll MX = N*N*K*2;
        vector<ll> dp(MX+1), nxt(MX+1);
        vector<int> acc(MX+1);
        dp[MX/2] = 1;
        rep(i, 0, N) {
            if (A[i] == 0) {
                rep(j, 0, MX+1) {
                    nxt[j] = dp[j]*(K+1);
                    nxt[j] %= MOD;
                }
            } else if (A[i] > 0) {
                acc.assign(MX+1, 0);
                ll m = A[i];
                rep(j, 0, MX+1) {
                    if (0 <= j-m) {
                        acc[j] = acc[j-m] + dp[j];
                        acc[j] %= MOD;
                    }
                }
                rep(j, 0, MX+1) {
                    ll k = max(j-m*(K+1), j%m);
                    nxt[j] = acc[j] - acc[k] + MOD;
                    nxt[j] %= MOD;
                }
            } else {
                acc.assign(MX+1, 0);
                ll m = -A[i];
                rrep(j, MX, -1) {
                    if (j+m <= MX) {
                        acc[j] = acc[j+m] + dp[j];
                        acc[j] %= MOD;
                    }
                }
                rep(j, 0, MX+1) {
                    ll k = min(j+m*(K+1), MX/m*m);
                    nxt[j] = acc[j] - acc[k] + MOD;
                    nxt[j] %= MOD;
                }
            }
            swap(nxt, dp);
            nxt.assign(MX+1, 0);
        }
        ll ans = (dp[MX/2]-1+MOD) % MOD;
        print(ans);
    }
    return 0;
}
