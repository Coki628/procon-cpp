/**
 * 参考：https://twitter.com/laycrs/status/1273667288701390848
 * ・グラフ、DAG、メモ化再帰
 * ・誤読。パスの数が2以上を潰すのかと思ったらパスの長さが2以上を潰すだった。
 * 　問題文にもlengthって入れて欲しかったな。。(投げてWAでテストの判定のとこで分かった)
 * ・普通にそのままやると、依存性があるので下から確定したいけど、長さが確定するのは2個戻ってからなので、
 * 　その頂点じゃなくて孫を潰したい状況になる。(問題文より、流入は無制限だけど流出は2以下
 * 　とあるので、なるべく下の方から潰した方が正解に近づく。孫の代わりにじいちゃんを潰そうとすると、
 * 　流入がたくさんだった時はたくさん潰さないといかなくなる。)
 * ・で、依存性を保証した上で孫から消すためには、逆辺を張ったDAGで下から上に辿る感じにするといい。
 * 　これだとトポソしないでも普通にDFSやればOK、ってなる。
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

ll T, N, M;
vvl nodes;
vector<ll> memo;
vector<bool> removed;

ll dfs(ll u) {
    if (memo[u] != -1) {
        return memo[u];
    }
    ll res = 0;
    for (ll v : nodes[u]) {
        chmax(res, dfs(v));
    }
    // 長さ2になったらこの頂点は削除
    if (res == 2) {
        removed[u] = true;
        res = 0;
    } else {
        res++;
    }
    memo[u] = res;
    return res;
}

void solve() {
    cin >> N >> M;
    nodes.clear();
    nodes.resize(N);
    memo.clear();
    memo.resize(N, -1);
    removed.clear();
    removed.resize(N);
    ll a, b;
    rep(i, 0, M) {
        cin >> a >> b;
        a--; b--;
        // 逆辺にして張る
        nodes[b].pb(a);
    }

    rep(i, 0, N) {
        dfs(i);
    }
    vector<ll> ans;
    rep(i, 0, N) {
        if (removed[i]) {
            ans.pb(i+1);
        }
    }
    print(ans.size());
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> T;
    rep(_, 0, T) solve();

    return 0;
}
