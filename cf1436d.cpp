/**
 * ・Cを見限ってこっちに注力、がしかしACならず。。
 * ・最大x人を各区画に逃がす時、うまくやれるか、で二分探索した。
 * ・でも結局TLEで、終了後最大値調整して様子見たりしたけど、どうもWAにもなってるぽい。。
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

ll bisearch_min(ll mn, ll mx, function<bool(ll)> func) {

    ll ok = mx;
    ll ng = mn;
    while (ng+1 < ok) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

ll N;
vector<ll> A, C;
vvl nodes;

void dfs1(ll m, ll u, ll prev) {
    for (auto v : nodes[u]) {
        if (v == prev) continue;
        dfs1(m, v, u);
        if (nodes[v].size() == 0) {
            C[u] += C[v];
        } else {
            C[u] += C[v] - A[v];
        }
    }
    if (nodes[u].size() == 0) {
        C[u] = m - A[u];
    }
    return;
}

bool dfs2(ll u, ll prev, ll sm) {
    ll cap = 0;
    for (auto v : nodes[u]) {
        if (v == prev) continue;
        if (!dfs2(v, u, sm+A[v])) {
            return false;
        }
        cap += C[v];
    }
    if (nodes[u].size() == 0) {
        if (C[u] < 0) {
            return false;
        }
    } else {
        if (sm > cap) {
            return false;
        }
    }
    return true;
}

bool check(ll m) {
    C.clear();
    C.resize(N);
    dfs1(m, 0, -1);
    bool res = dfs2(0, -1, A[0]);
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    nodes.resize(N);
    ll p;
    rep(i, 0, N-1)  {
        cin >> p;
        p--;
        nodes[p].pb(i+1);
    }
    rep(i, 0, N) cin >> A[i];

    ll res = bisearch_min(0, 10000000000, check);
    print(res);
    return 0;
}
