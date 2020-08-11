/**
 * ・終了後、自力AC？(ツイートで解法ネタバレはしてた。。)
 * ・グラフに帰着、DAG、DFS、メモ化再帰
 * ・DAGだよってネタバレはしてたけど、多分これなら自分でも辿り着けたはず。
 * 　同じグラフだけど、Cよりはやりやすかった印象。時間あれば解けたかなぁ。。
 * ・基本はDAG順にやってくんだけど、負数のとこは先にやると逆に損するので、
 * 　あえて後回しにする。後回しにした中でも依存性をなくしたいので、
 * 　後回しにしたグループは逆順にしてから元のやつと繋げる。
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

ll N, ans;
vector<ll> A, B1, B2, memo;
vvl nodes;

ll dfs(ll u) {
    if (memo[u] != -1) {
        return memo[u];
    }
    ll res = 0;
    for (ll v : nodes[u]) {
        res += dfs(v);
    }
    res += A[u];
    ans += res;
    // ここのA[u]が負数かどうかで場合分け
    if (res >= 0) {
        B1.pb(u+1);
    } else {
        // 負数だったらこの先で損しないように、ここは後回しにする
        res = 0;
        B2.pb(u+1);
    }
    memo[u] = res;
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    memo.assign(N, -1);
    nodes.resize(N);
    rep(i, 0, N) cin >> A[i];
    ll b;
    rep(a, 0, N) {
        cin >> b;
        b--;
        if (b >= 0) {
            nodes[b].pb(a);
        }
    }

    ans = 0;
    rep(i, 0, N) {
        dfs(i);
    }
    // 後回しにしたグループは逆順にしておく
    reverse(B2.begin(), B2.end());
    for (ll b : B2) {
        // 元のグループの末尾に繋げる
        B1.pb(b);
    }
    print(ans);
    print(B1);
    return 0;
}
