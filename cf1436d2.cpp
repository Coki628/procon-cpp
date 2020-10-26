/**
 * 参考：https://twitter.com/SSRS_cp/status/1320036380525801479
 * ・自力ならず。。
 * ・木DP
 * ・ceil((部分木のaの総和)/(部分木の葉の個数))のmax、この一言で理解した。。
 * ・各部分木について、その先にその人数が均等に逃げ込んだ時に、一番大きくなってしまう場所が答え。
 * ・上位から逃げ込んでくる訳だから、親からの情報も必要な気がしてしまったけど、
 * 　それの確認は親の時にすればいいんだね。。全部自分の部分木だけチェックすればOK。
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

ll N;
// dp1[i] := iの部分木の葉の個数
// dp2[i] := iの部分木のaの総和
vector<ll> A, dp1, dp2;
vvl nodes;

ll dfs(ll u, ll prev) {
    ll res = 0;
    for (auto v : nodes[u]) {
        if (v == prev) continue;
        chmax(res, dfs(v, u));
        dp1[u] += dp1[v];
        dp2[u] += dp2[v];   
    }
    if (nodes[u].size() == 0) {
        dp1[u]++;
    }
    dp2[u] += A[u];
    chmax(res, ceil(dp2[u], dp1[u]));
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    nodes.resize(N);
    dp1.resize(N);
    dp2.resize(N);
    ll p;
    rep(i, 0, N-1)  {
        cin >> p;
        p--;
        nodes[p].pb(i+1);
    }
    rep(i, 0, N) cin >> A[i];

    ll res = dfs(0, -1);
    print(res);
    return 0;
}
