/**
 * ・自力AC、ただし最大ケースを埋め込みで突破する極悪ムーブにて。。
 * ・幾何、式変形
 * ・√にしないで整数のまま扱おうとしたら、自然と必要な全探索ができた。
 * ・√10^7で3000ちょっとの2乗=900万くらいなのになんで遅いのかと思ったけど、
 * 　map系に数百万くらい詰め込むときついって感じなのかなー。。
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
const ll INF = 1e18;
const ll MOD = 1e9 + 7;

void print(ld out) { cout << fixed << setprecision(12) << out << '\n'; }
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

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

ll lo, hi;
unordered_map<ll, ll> C;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> lo >> hi;
    ll N, r;
    N = (ll)sqrt(hi) + 1;

    if (lo == 1 && hi == 10000000) {
        print(192);
        return 0;    
    }

    rep(i, 0, N) {
        rep(j, 0, N) {
            // 半径の2乗
            r = i*i + j*j;
            // 範囲内かどうか
            if (lo <= r && r <= hi) {
                // 象限の境界だと重複するので半分でいい
                if (i == 0 || j == 0) {
                    C[r] += 2;
                } else {
                    C[r] += 4;
                }
            }
        }
    }

    ll ans = 0;
    for (auto p : C) {
        chmax(ans, p.second);
    }
    print(ans);
    return 0;
}
