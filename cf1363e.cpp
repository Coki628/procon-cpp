/**
 * 参考：https://twitter.com/laycrs/status/1267132642908008450
 * ・終了後、Dよりみんな通してたのでやってみたけど自力ならず。。
 * ・木DP
 * ・これは典型の範疇だと思うし解けるべきだったな。。
 * ・親から子に送る情報と子から親に送る情報が両方出てくるので、良い練習問題だと思った。
 * 　まあ解けなかったんだけど。。。
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

ll N;
vvl nodes;
vector<ll> A, dp0, dp1;
vector<bool> B, C;

ll rec(ll u, ll prev) {
    ll res = 0;
    for (ll v : nodes[u]) {
        if (v == prev) continue;
        // 最小コストは親から子に伝播させる
        chmin(A[v], A[u]);
        res += rec(v, u);
        // スワップ対象数の管理は子から親に戻す
        dp0[u] += dp0[v];
        dp1[u] += dp1[v];
    }
    if (B[u] == 0 && C[u] == 1) {
        dp0[u]++;
    }
    if (B[u] == 1 && C[u] == 0) {
        dp1[u]++;
    }
    while (dp0[u] && dp1[u]) {
        res += A[u] * 2;
        dp0[u]--;
        dp1[u]--;
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    B.resize(N);
    C.resize(N);
    dp0.resize(N);
    dp1.resize(N);
    ll a, b;
    rep(i, 0, N) {
        cin >> A[i] >> a >> b;
        B[i] = a;
        C[i] = b;
    }
    nodes.resize(N);
    rep(i, 0, N-1) {
        cin >> a >> b;
        a--; b--;
        nodes[a].pb(b);
        nodes[b].pb(a);
    }

    ll ans = rec(0, -1);
    if (dp0[0] == dp1[0]) {
        print(ans);
    } else {
        print(-1);
    }
    return 0;
}
