/**
 * 参考：https://twitter.com/eiya5498513/status/1294632185169813505
 * 　　　https://atcoder.jp/contests/abc175/submissions/15935430
 * ・ダブリングゴリ押し方針。これだとやったことある感じのダブリングだけでいける。
 * ・5000^2=2500万のループの内側でさらにlogをやる。計算量8億はやばい。
 * ・これが何とか通る。AC2.26秒。(制約3秒)
 * ・この計算量を通しに行こうと思えるC++はやっぱ有利だよなー。。
 */

// #pragma GCC optimize("Ofast")
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

ll N, K;
vector<ll> P, C, A;
const ll MAX = 32;
ll nxt[MAX][5007], score[MAX][5007];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    P.resize(N);
    C.resize(N);
    rep(i, 0, N) {
        cin >> P[i];
        P[i]--;
    }
    rep(i, 0, N) cin >> C[i];

    rep(i, 0, N) {
        nxt[0][i] = P[i];
        score[0][i] = C[P[i]];
    }
    rep(k, 1, MAX) {
        rep(i, 0, N) {
            nxt[k][i] = nxt[k-1][nxt[k-1][i]];
            score[k][i] = score[k-1][i] + score[k-1][nxt[k-1][i]];
        }
    }

    ll ans = -INF;
    ll cur, sm;
    rep(i, 0, N) {
        // 1からmin(K, N)まで見る
        rep(j, 1, min(K, N)+1) {
            cur = i;
            sm = 0;
            rrep(k, MAX-1, -1) {
                if (j >> k & 1) {
                    sm += score[k][cur];
                    cur = nxt[k][cur];
                }
            }
            chmax(ans, sm);
        }
        // K-NからKまで見る
        rep(j, max(K-N, 1LL), K+1) {
            cur = i;
            sm = 0;
            rrep(k, MAX-1, -1) {
                if (j >> k & 1) {
                    sm += score[k][cur];
                    cur = nxt[k][cur];
                }
            }
            chmax(ans, sm);
        }
    }
    print(ans);
    return 0;
}
