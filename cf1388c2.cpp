/**
 * ・自力AC！通せてよかったー。
 * ・グラフ、DFS、木DP
 * ・戻りがけに色々やる。
 * ・DFSで戻り値に持たせてた値を配列に詰めて木DPっぽくしてみた。
 * 　これだと戻り値にはboolを持たせられるので、NGパターンは即終了、ができる。
 * ・あとDFS2回やってたけど、1回にまとめられたのでまとめた。
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

ll N, M;
vector<ll> P, H, dp1, dp2;
vvl nodes;

// goodな人が最低限何人必要、をdp2に持ちながら戻りがけで妥当性チェック
bool dfs(ll u, ll prev) {
    for (ll v : nodes[u]) {
        if (v == prev) continue;
        if (!dfs(v, u)) {
            return false;
        }
        dp1[u] += dp1[v];
        dp2[u] += dp2[v];
    }
    // 街uを通る人数をdp1[u]に入れる
    dp1[u] += P[u];
    // badの上限 = 全体 - goodの下限
    ll bcnt1 = dp1[u] - dp2[u];
    // 装置の予測値によるbad人数
    ll bcnt2, m;
    tie(bcnt2, m) = divmod(dp1[u] - H[u], 2);
    // 予測値が整数にならない or 負数になる or bad上限より大きい
    if (m || bcnt2 < 0 || bcnt1 < bcnt2) {
        return false;
    }
    // 予測値のgood人数
    dp2[u] = dp1[u] - bcnt2;
    return true;
}

void solve() {
    P.clear();
    H.clear();
    dp1.clear();
    dp2.clear();
    nodes.clear();

    cin >> N >> M;
    P.resize(N);
    H.resize(N);
    dp1.resize(N);
    dp2.resize(N);
    nodes.resize(N);
    rep(i, 0, N) cin >> P[i];
    rep(i, 0, N) cin >> H[i];
    ll a, b;
    rep(i, 0, N-1) {
        cin >> a >> b;
        a--; b--;
        nodes[a].pb(b);
        nodes[b].pb(a);
    }

    if (dfs(0, -1)) {
        print("YES");
    } else {
        print("NO");
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
