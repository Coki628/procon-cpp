/**
 * ・なんとか自力AC！終了5分前通せた！
 * ・有向グラフ、DFS、閉路検出
 * ・末端から戻ってくる時に自分に向けて辺を張れば、依存性を守れる。
 * ・通せたから良かったけど、ちょこちょこバグらせて大変だった。。
 * ・他のみんなの見たら、トポソしてその順に従って繋いでた。確かにそっちのが楽そう。。
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
vvl nodes;
vvl nodes2;
map<pll, ll> D;
vector<ll> memo;
vector<pll> ans;

bool dfs(ll u) {
    if (memo[u] == 2) {
        return true;
    // 閉路が見つかれば一発アウト
    } else if (memo[u] == 1) {
        return false;
    }
    memo[u] = 1;
    for (ll v : nodes[u]) {
        if (!dfs(v)) {
            return false;
        }
    }
    // uより先を調べ終わったら、uに向けての辺を張る
    for (ll v : nodes2[u]) {
        if (memo[v] != 2) {
            ans[D[{v, u}]] = {v+1, u+1};
        }
    }
    memo[u] = 2;
    return true;
}

void solve() {
    cin >> N >> M;
    nodes.clear();
    nodes2.clear();
    memo.clear();
    ans.clear();
    D.clear();
    nodes.resize(N);
    nodes2.resize(N);
    memo.resize(N);
    ans.resize(M);
    ll t, a, b;
    rep(i, 0, M) {
        cin >> t >> a >> b;
        a--; b--;
        if (t) {
            nodes[a].pb(b);
            ans[i] = {a+1, b+1};
        } else {
            nodes2[a].pb(b);
            nodes2[b].pb(a);
            D[{a, b}] = i;
            D[{b, a}] = i;
        }
    }

    bool ok = 1;
    rep(i, 0, N) {
        if (!dfs(i)) {
            ok = 0;
            break;
        }
    }
    if (ok) {
        print("YES");
        for (auto a : ans) {
            print(a);
        }
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
