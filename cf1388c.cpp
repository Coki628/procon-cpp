/**
 * ・自力AC！通せてよかったー。
 * ・グラフ、DFS、木
 * ・戻りがけに色々やる。
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

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

ll N, M;
vector<ll> P, H, A;
vvl nodes;
bool ok;

// 街uを通る人数をA[u]に入れる
ll dfs1(ll u, ll prev) {
    ll res = 0;
    for (ll v : nodes[u]) {
        if (v == prev) continue;
        res += dfs1(v, u);
    }
    res += P[u];
    A[u] = res;
    return res;
}

// goodな人が最低限何人必要、を持ちながら戻りがけで妥当性チェック
ll dfs2(ll u, ll prev) {
    ll gcnt1 = 0;
    for (ll v : nodes[u]) {
        if (v == prev) continue;
        gcnt1 += dfs2(v, u);
    }
    // badの上限 = 全体 - goodの下限
    ll bcnt1 = A[u] - gcnt1;
    // 予測値が整数にならないのはおかしい
    if ((A[u] - H[u]) % 2 != 0) {
        ok = false;
    }
    // 装置の予測値によるbad人数
    ll bcnt2 = (A[u] - H[u]) / 2;
    // 予測値が負数 or bad上限より大きい
    if (bcnt2 < 0 || bcnt1 < bcnt2) {
        ok = false;
    }
    // 予測値のgood人数
    ll gcnt2 = A[u] - bcnt2;
    ll res = max(gcnt1, gcnt2);
    return res;
}

void solve() {
    P.clear();
    H.clear();
    A.clear();
    nodes.clear();
    ok = true;

    cin >> N >> M;
    P.resize(N);
    H.resize(N);
    A.resize(N);
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

    dfs1(0, -1);
    dfs2(0, -1);
    if (ok) {
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
    rep(_, 0, T) solve();

    return 0;
}
