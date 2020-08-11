/**
 * ・pypyTLEにてこっちでAC。
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
int toint(char c) { return c - '0'; }
char tochar(int i) { return '0' + i; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

template<typename T>
void transpose(vector<vector<T>> &grid) {
    int H = grid.size();
    int W = grid[0].size();
    list2d(res, W, H, T, 0);
    rep(i, 0, H) {
        rep(j, 0, W) {
            res[j][i] = grid[i][j];
        }
    }
    swap(res, grid);
}

ll H, W;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> H >> W;
    list2d(grid, H, W, bool, 0);
    string row;
    rep(i, 0, H) {
        cin >> row;
        rep(j, 0, W) {
            grid[i][j] = toint(row[j]);
        }
    }

    if (H >= 4 && W >= 4) {
        print(-1);
        return 0;
    }
    if (H == 1 || W == 1) {
        print(0);
        return 0;
    }

    if (W > H) {
        transpose(grid);
        swap(H, W);
    }

    ll cur = 0, k;
    rep(j, 0, W) {
        k = W - j - 1;
        if (grid[0][j]) {
            cur += 1LL << k;
        }
    }
    if (W == 2) {
        list2d(dp, H, 4, ll, INF);
        rep(nxt, 0, 4)  {
            dp[0][nxt] = popcount(cur ^ nxt);
        }
        rep(i, 1, H) {
            cur = 0;
            rep(j, 0, W) {
                k = W - j - 1;
                if (grid[i][j]) {
                    cur += 1LL << k;
                }
            }
            rep(k, 0, 4) {
                if (k == 1 || k == 2) {
                    chmin(dp[i][0], dp[i-1][k] + popcount(cur ^ 0));
                    chmin(dp[i][3], dp[i-1][k] + popcount(cur ^ 3));
                } else {
                    chmin(dp[i][2], dp[i-1][k] + popcount(cur ^ 2));
                    chmin(dp[i][1], dp[i-1][k] + popcount(cur ^ 1));
                }
            }
        }
        ll ans = min(dp[H-1]);
        print(ans);
    } else {
        list2d(dp, H, 8, ll, INF);
        rep(nxt, 0, 8) {
            dp[0][nxt] = popcount(cur ^ nxt);
        }
        rep(i, 1, H) {
            cur = 0;
            rep(j, 0, W) {
                k = W - j - 1;
                if (grid[i][j]) {
                    cur += 1LL << k;
                }
            }
            // to 000
            chmin(dp[i][0], dp[i-1][5] + popcount(cur ^ 0));
            chmin(dp[i][0], dp[i-1][2] + popcount(cur ^ 0));
            // to 001
            chmin(dp[i][1], dp[i-1][3] + popcount(cur ^ 1));
            chmin(dp[i][1], dp[i-1][4] + popcount(cur ^ 1));
            // to 010
            chmin(dp[i][2], dp[i-1][7] + popcount(cur ^ 2));
            chmin(dp[i][2], dp[i-1][0] + popcount(cur ^ 2));
            // to 011
            chmin(dp[i][3], dp[i-1][6] + popcount(cur ^ 3));
            chmin(dp[i][3], dp[i-1][1] + popcount(cur ^ 3));
            // to 100
            chmin(dp[i][4], dp[i-1][1] + popcount(cur ^ 4));
            chmin(dp[i][4], dp[i-1][6] + popcount(cur ^ 4));
            // to 101
            chmin(dp[i][5], dp[i-1][7] + popcount(cur ^ 5));
            chmin(dp[i][5], dp[i-1][0] + popcount(cur ^ 5));
            // to 110
            chmin(dp[i][6], dp[i-1][4] + popcount(cur ^ 6));
            chmin(dp[i][6], dp[i-1][3] + popcount(cur ^ 6));
            // to 111
            chmin(dp[i][7], dp[i-1][5] + popcount(cur ^ 7));
            chmin(dp[i][7], dp[i-1][2] + popcount(cur ^ 7));
        }
        ll ans = min(dp[H-1]);
        print(ans);
    }
    return 0;
}
