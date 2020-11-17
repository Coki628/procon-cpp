/**
 * ・pypyTLEにつき、こっちでAC。
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

    ll H, W, N, M;
    cin >> H >> W >> N >> M;
    list2d(grid, H+2, W+2, int, 0);
    rep(i, 0, H+2) {
        grid[i][0] = -1;
        grid[i][W+1] = -1;
    }
    rep(i, 0, W+2) {
        grid[0][i] = -1;
        grid[H+1][i] = -1;
    }
    ll a, b;
    rep(_, 0, N) {
        cin >> a >> b;
        grid[a][b] = 1;
    }
    rep(_, 0, M) {
        cin >> a >> b;
        grid[a][b] = -1;
    }

    list2d(ans, H+2, W+2, bool, 0);
    rep(i, 1, H+1) {
        bool ok = false;
        rep(j, 1, W+1) {
            if (grid[i][j] == 1) {
                ok = true;
            } else if (grid[i][j] == -1) {
                ok = false;
            }
            if (ok) {
                ans[i][j] = true;
            }
        }
    }
    rep(i, 1, H+1) {
        bool ok = false;
        rrep(j, W, 0) {
            if (grid[i][j] == 1) {
                ok = true;
            } else if (grid[i][j] == -1) {
                ok = false;
            }
            if (ok) {
                ans[i][j] = true;
            }
        }
    }
    rep(i, 1, W+1) {
        bool ok = false;
        rep(j, 1, H+1) {
            if (grid[j][i] == 1) {
                ok = true;
            } else if (grid[j][i] == -1) {
                ok = false;
            }
            if (ok) {
                ans[j][i] = true;
            }
        }
    }
    rep(i, 1, W+1) {
        bool ok = false;
        rrep(j, H, 0) {
            if (grid[j][i] == 1) {
                ok = true;
            } else if (grid[j][i] == -1) {
                ok = false;
            }
            if (ok) {
                ans[j][i] = true;
            }
        }
    }

    ll cnt = 0;
    rep(i, 1, H+1) {
        rep(j, 1, W+1) {
            if (ans[i][j]) {
                cnt++;
            }
        }
    }
    print(cnt);
    return 0;
}
